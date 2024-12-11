/** @file
 * @brief Объявление класса crit_err для представления критических ошибок.
 * @author Селуков Е.В.
 * @version 1.0
 * @date 11.12.2024
 * @copyright ИБСТ ПГУ
 * @warning Это учебный пример
 */
#pragma once
#include <system_error>
#include <stdexcept>
#include <string>

/// @class crit_err
/// @brief Класс для представления критических ошибок.
/// Наследует от std::runtime_error.
class crit_err : public std::runtime_error {
public:
    /// @brief Конструктор, инициализирующий критическую ошибку с сообщением.
    /// @param s Сообщение об ошибке.
    crit_err(const std::string& s) : std::runtime_error(s) {}
};

/// @class no_crit_err
/// @brief Класс для представления некритических ошибок.
/// Наследует от std::runtime_error.
class no_crit_err : public std::runtime_error {
public:
    /// @brief Конструктор, инициализирующий некритическую ошибку с сообщением.
    /// @param s Сообщение об ошибке.
    no_crit_err(const std::string s) : std::runtime_error(s) {}
};
