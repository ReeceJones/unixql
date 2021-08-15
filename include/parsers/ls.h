#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <any>
#include "OutputParser.h"
#include "OutputLexer.h"
#include "antlr4-runtime.h"

namespace Parsers::Ls {
    typedef std::tuple<std::string, std::any> Column;
    typedef std::vector<Column> Columns;

    class  LsParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
    public:
        antlrcpp::Any visitOutput(OutputParser::LsContext *context) {
            std::vector<Columns> lines;

            for (auto line : context->entries) {
                lines.push_back(visitLine(line).as<Columns>());
            }

            return lines;
        }

        antlrcpp::Any visitLine(OutputParser::LineContext* context) {
            std::string path;
            for (auto p : context->path) {
                path += p->getText() + " ";
            }
            path.pop_back();
            Columns columns = {
                Column("mode", context->file_mode()->getText()),
                Column("number_links", context->number_links()->getText()),
                Column("user", context->user()->getText()),
                Column("group", context->group()->getText()),
                Column("size", context->size()->getText()),
                Column("month", context->month()->getText()),
                Column("time", context->time()->getText()),
                Column("path", path)
            };
            return columns;
        }
    };

    inline void parseLs(std::string output) {
        antlr4::ANTLRInputStream input(output);
        OutputLexer lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);
        OutputParser parser(&tokens);

        OutputParser::LsContext* tree = parser.ls();
        LsParserVisitor visitor;
        visitor.visitOutput(tree);
    }
}