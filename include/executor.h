#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <chrono>
#include <unistd.h>

#include "interceptor.h"
#include "io.h"

namespace Executor {
    void executeProgram(std::vector<std::string> columns, std::string table, std::vector<std::pair<std::string,std::string>> conditions);
    std::string execute(std::vector<std::string> args);
}