#pragma once

#include <string>
#include <array>
#include <vector>

namespace IO {
    const unsigned int STDIN = 0;
    const unsigned int STDOUT = 1;
    const unsigned int STDERR = 2;

    typedef std::array<int, 3> FdSet;
}