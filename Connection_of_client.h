/** @file
 * @brief Объявление класса Client_Communicate для управления сетевым взаимодействием клиента.
 * @author Селуков Е.В.
 * @version 1.0
 * @date 11.12.2024
 * @copyright ИБСТ ПГУ
 * @warning Это учебный пример
 */
#pragma once
#include <string>
#include <vector>
#include <map>

#include "Logger.h"

/// @class Client_Communicate
/// @brief Класс для управления сетевым взаимодействием клиента.
class Client_Communicate {
public:
    /// @brief Устанавливает соединение с заданным портом.
    /// @param port Номер порта для подключения.
    /// @param database Карта данных (ключ-значение) для использования в коммуникации.
    /// @param l1 Указатель на объект логгера для отслеживания событий.
    /// @return Код состояния операции.
    int connection(int port, std::map<std::string, std::string> database, Logger* l1);

    /// @brief Вычисляет SHA-224 хеш строки.
    /// @param input_str Входная строка для хеширования.
    /// @return Хешированная строка в виде SHA-224.
    static std::string sha224(const std::string& input_str);
};
