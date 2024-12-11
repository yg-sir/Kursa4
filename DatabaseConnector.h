/** @file
 * @brief Объявление класса Connector_to_base для взаимодействия с базой данных.
 * @author Селуков Е.В.
 * @version 1.0
 * @date 11.12.2024
 * @copyright ИБСТ ПГУ
 * @warning Это учебный пример
 */
#pragma once
#include <map>
#include <string>

/// @class Connector_to_base
/// @brief Класс для взаимодействия с базой данных.
class Connector_to_base {
private:
    std::map<std::string, std::string> data_base; ///< Хранит данные базы в формате ключ-значение.

public:
    /// @brief Устанавливает соединение с базой данных, читая из файла конфигурации.
    /// @param base_file Путь к файлу конфигурации базы данных. По умолчанию "/etc/vcalc.conf".
    /// @return Код состояния операции соединения.
    int connect_to_base(std::string base_file = "/etc/vcalc.conf");

    /// @brief Возвращает данные базы.
    /// @return Карту данных базы в формате ключ-значение.
    std::map<std::string, std::string> get_data() {
        return data_base;
    }
};
