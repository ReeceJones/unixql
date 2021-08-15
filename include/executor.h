#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include <unistd.h>

#include "interceptor.h"
#include "io.h"

namespace Executor {
    void executeProgram(std::vector<std::string> columns, std::string table);
    std::string execute(std::vector<std::string> args);
}