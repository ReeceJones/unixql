#pragma once

#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include <iostream>
#include <optional>
#include <tuple>

#include <nlohmann/json.hpp>

#include "parsers.h"

using json = nlohmann::json;

namespace Interceptor {
    extern json commands;
    void loadCommands(std::string file_path);
    std::tuple<std::optional<std::vector<std::string>>, std::optional<Parsers::ParserFn>> interceptTable(std::string table);
}