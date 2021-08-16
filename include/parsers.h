#pragma once

#include <string>
#include <map>
#include <optional>
#include <iostream>

#include "parsers/ls.h"

namespace Parsers {
    typedef std::shared_ptr<DB::Table> (*ParserFn)(std::string input);
    extern std::map<std::string, ParserFn> parsers;

    void loadParsers();
    bool registerParser(std::string parser_name, ParserFn fn);
    std::optional<ParserFn> resolveParser(std::string parser_name);
}
