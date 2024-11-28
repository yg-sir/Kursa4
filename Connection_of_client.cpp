#include "Calculate.h"
#include "Connection_of_client.h"
#include "Errors.h"
#include "Logger.h"

#include <arpa/inet.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
std::string Client_Communicate::sha224(const std::string& input_str)
{
    using namespace CryptoPP;
    SHA224 hash;
    std::string new_hash;
    StringSource(input_str, true, new HashFilter(hash, new HexEncoder(new StringSink(new_hash))));
    return new_hash;
}

int Client_Communicate::connection(int port, std::map<std::string, std::string> database, Logger* l1)
{
    try {
        int queue_len = 100;
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        inet_aton("127.0.0.1", &addr.sin_addr);
        int s = socket(AF_INET, SOCK_STREAM, 0);
        if(s <= 0) {
            throw crit_err("Ошибка создания сокета");
        }
        l1->writelog("Listen socket created");

        auto rc = bind(s, (const sockaddr*)&addr, sizeof(sockaddr_in));
        if(rc < 0) {
            throw crit_err("Ошибка связывания сокетов");
        }
        rc = listen(s, queue_len);
        if(rc < 0) {
            throw crit_err("Ошибка прослушивания сокета");
        }

        while(true) {
            sockaddr_in client_addr;
            socklen_t len = sizeof(sockaddr_in);
            int work_sock = accept(s, (sockaddr*)&client_addr, &len);

            if(work_sock <= 0) {
                l1->writelog("Ошибка сокета клиента");
                continue;
            }

            char buff[1024] = {};
            ssize_t rc = recv(work_sock, buff, sizeof(buff) - 1, 0);
            if(rc <= 0) {
                close(work_sock);
                continue;
            }
            if(rc < 72) {
                send(work_sock, "ERR", 3, 0);
                close(work_sock);
                continue;
            }
            std::string hash_received(buff + rc - 56, 56);
            std::string salt(buff + rc - 72, 16);
            std::string login(buff, rc - 72);

            // Логирование для отладки
            l1->writelog("Login: " + login);
            l1->writelog("Salt: " + salt);
            l1->writelog("Received hash: " + hash_received);

            // Проверка аутентификации
            auto it = database.find(login);
            if(it == database.end()) {
                send(work_sock, "ERR", 3, 0);
                close(work_sock);
                continue;
            }

            std::string expected_hash = sha224(salt + it->second);

            if(expected_hash != hash_received) {
                send(work_sock, "ERR", 3, 0);
            } else {
                send(work_sock, "OK", 2, 0);
                l1->writelog("Authentication successful for user: " + login);
            }

            uint32_t number_of_vectors;
            uint32_t vector_size;
            uint16_t sum = 0;

            if(recv(work_sock, &number_of_vectors, sizeof(number_of_vectors), 0) <= 0) {
                close(work_sock);
            }

            for(uint32_t i = 0; i < number_of_vectors; i++) {
                if(recv(work_sock, &vector_size, sizeof(vector_size), 0) <= 0) {
                    close(work_sock);
                }

                std::vector<uint16_t> vector_values(vector_size);

                for(uint32_t j = 0; j < vector_size; j++) {
                    uint16_t vector_value;
                    if(recv(work_sock, &vector_value, sizeof(vector_value), 0) <= 0) {
                        close(work_sock);
                    }
                    vector_values[j] = vector_value;
                }

                Calculator calculator(vector_values);

                sum = calculator.send_res();
                send(work_sock, &sum, sizeof(sum), 0);
            }

            close(work_sock);
        }
    } catch(crit_err& e) {
        l1->writelog(e.what());
        return -1;
    }

    return 0;
}
