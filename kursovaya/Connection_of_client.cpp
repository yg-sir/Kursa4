#include "Connection_of_client.h"
#include "Logger.h"
#include "Errors.h"
#include "Calculate.h"
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

std::string Client_Communicate::sha224(const std::string& input_str) {
    using namespace CryptoPP;
    SHA224 hash;
    std::string new_hash;
    StringSource(input_str, true, new HashFilter(hash, new HexEncoder(new StringSink(new_hash))));
    return new_hash;
}

int Client_Communicate::connection(int port, std::map<std::string, std::string> database, Logger* l1) {
    try {
        int queue_len = 100;
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        inet_aton("127.0.0.1", &addr.sin_addr);
        int s = socket(AF_INET, SOCK_STREAM, 0);
        if (s <= 0) { throw crit_err("Ошибка создания сокета"); }
        l1->writelog("Listen socket created");

        auto rc = bind(s, (const sockaddr*)&addr, sizeof(sockaddr_in));
        if (rc < 0) { throw crit_err("Ошибка связывания сокетов"); }
        rc = listen(s, queue_len);
        if (rc < 0) { throw crit_err("Ошибка прослушивания сокета"); }

        while (true) {
            sockaddr_in client_addr;
            socklen_t len = sizeof(sockaddr_in);
            int work_sock = accept(s, (sockaddr*)&client_addr, &len);

            if (work_sock <= 0) {
                l1->writelog("Ошибка сокета клиента");
                continue;
            }

            // Инициализация буфера
            char buff[1024];
            ssize_t rc = recv(work_sock, buff, sizeof(buff) - 1, 0);

            if (rc <= 0) { close(work_sock); continue; }
            buff[rc] = '\0';

            // Проверка длины buff перед разбором
            if (rc < 72) { // 16 (логин) + 16 (соль) + 40 (SHA-224 hex encoded hash)
                send(work_sock, "ERR", 3, 0);
                close(work_sock);
                continue;
            }

            std::string login(buff, 16);
            std::string salt(buff + 16, 16);
            std::string hash_received(buff + 32, 56); 

            // Логирование для отладки
            l1->writelog("Login: " + login);
            l1->writelog("Salt: " + salt);
            l1->writelog("Received hash: " + hash_received);

            // Проверка аутентификации
            auto it = database.find(login);
            if (it == database.end()) {
                send(work_sock, "ERR", 3, 0);
                close(work_sock);
                continue;
            }

            std::string expected_hash = sha224(salt + it->second);
            
            if (expected_hash != hash_received) {
                send(work_sock, "ERR", 3, 0);
            } else {
                send(work_sock, "OK", 2, 0);
                l1->writelog("Authentication successful for user: " + login);
                // Process further vector operations...
            }

            close(work_sock);
        }
    } catch (crit_err& e) {
        l1->writelog(e.what());
        return -1;
    }

    return 0;
}
