/** @file
 * @brief Объявление класса Interface для управления интерфейсом связи.
 * @author Селуков Е.В.
 * @version 1.0
 * @date 11.12.2024
 * @copyright ИБСТ ПГУ
 * @warning Это учебный пример
 */
#pragma once
#include "Logger.h"
#include <string>
/// @class Interface
/// @brief Класс для управления интерфейсом связи.
class Interface {
    int PORT; ///< Номер порта для подключения.
public:
    /// @brief Конструктор по умолчанию.
    Interface() {}
    /// @brief Обрабатывает командную строку для установления связи.
    /// @param argc Количество аргументов.
    /// @param argv Массив аргументов командной строки.
    /// @return Код состояния операции.
    int comm_proc(int argc, const char** argv);
};
