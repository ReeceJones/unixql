#pragma once

#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include <iostream>
#include <optional>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace Interceptor {
    extern json commands;
    void loadCommands(std::string file_path);
    std::optional<std::vector<std::string>> interceptTable(std::string table);
}