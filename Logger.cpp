#include "Logger.h"
#include <chrono>
#include <string>
#include <time.h>
#include <fstream>
#include <iostream>  
#include "Errors.h"

using namespace std;

int Logger::set_path(std::string path_file) {
    if(path_file.find('.') == std::string::npos) {
        throw std::invalid_argument("file without extension");
    }
    std::ofstream filelog;
    filelog.open(path_file, std::ios_base::out | std::ios_base::app);
    if(filelog.is_open()) {
        path_to_logfile = path_file;
        return 0;
    } else if (path_file == "/var/log/vcalc.log") {
        path_to_logfile = "/tmp/log/vcalc.log";
        filelog.open(path_to_logfile, std::ios_base::out | std::ios_base::app);
        if (filelog.is_open()) {
            return 0;
        }
    }
    throw crit_err("path to log not exist");
}

string Logger::getCurrentDateTime(string s) {
    time_t now = time(0);
    struct tm  tstruct;
    char  buf[80];
    tstruct = *localtime(&now);
    if(s == "now")
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    else if(s == "date")
        strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    return string(buf);
}

int Logger::writelog(std::string s) {
    std::ofstream filelog(path_to_logfile, std::ios_base::out | std::ios_base::app);

    if (!filelog.is_open()) {
        std::cerr << "Ошибка: не удалось создать лог в " << path_to_logfile
                  << ". Переключение на /tmp/log/vcalc.log" << std::endl;
        path_to_logfile = "/tmp/log/vcalc.log";
        filelog.open(path_to_logfile, std::ios_base::out | std::ios_base::app);

        if (!filelog.is_open()) {
            throw crit_err("Не удалось создать лог-файл: " + path_to_logfile);
        }
    }

    std::string time = getCurrentDateTime("now");
    filelog << time << ' ' << s << std::endl;
    return 0;
}
