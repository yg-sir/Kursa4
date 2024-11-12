#include "Calculate.h"
Calculator::Calculator(std::vector<uint16_t> input_data) {
    try {
        uint16_t temp_res = 0;
        for (auto elem : input_data) {
            temp_res = boost::numeric_cast<uint16_t>(temp_res + elem);
        }
        results = temp_res;
    } catch (boost::numeric::negative_overflow& e) {
        results = std::numeric_limits<uint16_t>::lowest();
    } catch (boost::numeric::positive_overflow& e) {
        results = std::numeric_limits<uint16_t>::max();
    }
}

uint16_t Calculator::send_res() { return results; }
