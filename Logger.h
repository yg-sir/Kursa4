/** @file
 * @brief Объявление класса Logger для ведения логирования в файл.
 * @author Селуков Е.В.
 * @version 1.0
 * @date 11.12.2024
 * @copyright ИБСТ ПГУ
 * @warning Это учебный пример
 */
#pragma once
#include <string>
/// @class Logger
/// @brief Класс для ведения логирования в файл.
class Logger {
    /// @brief Возвращает текущую дату и время как строку.
    /// @param s Формат отображения даты и времени.
    /// @return Строка с текущей датой и временем.
    static std::string getCurrentDateTime(std::string s);

    std::string path_to_logfile; ///< Путь к файлу лога.

public:
    /// @brief Записывает сообщение в лог-файл.
    /// @param s Сообщение для записи.
    /// @return Код состояния операции записи.
    int writelog(std::string s);

    /// @brief Устанавливает путь к лог-файлу.
    /// @param path_file Путь к файлу лога.
    /// @return Код состояния операции установки пути.
    int set_path(std::string path_file);

    /// @brief Конструктор по умолчанию.
    Logger() { path_to_logfile = " "; };

    /// @brief Конструктор с заданным путем к лог-файлу.
    /// @param s Путь к файлу лога.
    Logger(std::string s) { path_to_logfile = s; };
};
