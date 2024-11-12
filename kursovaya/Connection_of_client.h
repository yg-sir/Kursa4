#pragma once
#include <string>
#include <vector>
#include <map>

#include "Logger.h"

class Client_Communicate {
public:
    int connection(int port, std::map<std::string, std::string> database, Logger* l1);
    static std::string sha224(const std::string& input_str);
};
