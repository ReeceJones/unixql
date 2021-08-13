#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include <unistd.h>

namespace Executor {
    void executeProgram(std::vector<std::string> columns, std::string table);
    void execute(std::vector<std::string> args);
}