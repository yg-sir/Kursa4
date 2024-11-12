#pragma once
#include <vector>
#include <limits>
#include <boost/numeric/conversion/cast.hpp>

class Calculator {
    uint16_t results;
public:
    Calculator(std::vector<uint16_t> input_data);
    uint16_t send_res();
};
