#pragma once

#include <string>
#include <vector>
#include "LsParser.h"
#include "antlr4-runtime.h"

namespace Parsers::Ls {
    inline void parseLs(std::string input) {

    }

    class  LsParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
    public:
        antlrcpp::Any visitOutput(LsParser::OutputContext *context) {
            std::cout << "parsing output" << std::endl;

            return "";
        }
    };
}