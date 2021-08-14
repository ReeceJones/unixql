#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <any>
#include "LsParser.h"
#include "antlr4-runtime.h"

namespace Parsers::Ls {
    typedef std::tuple<std::string, std::any> Column;
    typedef std::vector<Column> Columns;

    inline void parseLs(std::string input) {
        std::cout << "ls parser received input: "<< input << std::endl;
    }

    class  LsParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
    public:
        antlrcpp::Any visitOutput(LsParser::OutputContext *context) {
            std::vector<Columns> lines;

            for (auto line : context->entries) {
                lines.push_back(visitLine(line).as<Columns>());
            }

            return lines;
        }

        antlrcpp::Any visitLine(LsParser::LineContext* context) {
            Columns columns = {
                Column("mode", context->file_mode()->getText()),
                Column("number_links", context->number_links()->getText()),
                Column("user", context->user()->getText()),
                Column("group", context->group()->getText()),
                Column("size", context->size()->getText()),
                Column("month", context->month()->getText()),
                Column("time", context->time()->getText()),
                Column("path", context->path()->getText())
            };
            return columns;
        }
    };
}