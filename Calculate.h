/** @file
 * @brief Объявление класса Calculator для выполнения вычислений с вектором.
 * @author Селуков Е.В.
 * @version 1.0
 * @date 11.12.2024
 * @copyright ИБСТ ПГУ
 * @warning Это учебный пример
 */
#pragma once
#include <vector>
#include <limits>
#include <boost/numeric/conversion/cast.hpp>

/// @class Calculator
/// @brief Класс для выполнения вычислений с вектором чисел типа uint16_t.
class Calculator {
    uint16_t results; ///< Хранит результат вычислений.

public:
    /// @brief Конструктор, инициализирующий объект Calculator с входными данными.
    /// @param input_data Вектор чисел типа uint16_t для обработки.
    Calculator(std::vector<uint16_t> input_data);

    /// @brief Возвращает результат вычислений.
    /// @return Число типа uint16_t, представляющее результат.
    uint16_t send_res();
};
