#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <any>
#include <memory>
#include "OutputParser.h"
#include "OutputLexer.h"
#include "antlr4-runtime.h"
#include "db.h"

namespace Parsers::Ls {
    class  LsParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
    public:
        antlrcpp::Any visitOutput(OutputParser::LsContext *context) {
            // Modern c++ has cool features, too bad c++20 support sucks
            std::vector<std::string> column_names{
                "mode",
                "number_links",
                "user",
                "group",
                "size",
                "month",
                "day",
                "time",
                "path"
            };
            auto table = DB::Table("ls", column_names);

            for (auto line : context->entries) {
                table.push_back(visitLine(line).as<DB::Table::Row>());
            }

            return table;
        }

        antlrcpp::Any visitLine(OutputParser::LineContext* context) {
            std::string path;
            for (auto p : context->path) {
                path += p->getText() + " ";
            }
            path.pop_back();
            DB::Table::Row row = {
                {"mode", context->file_mode()->getText()},
                {"number_links", context->number_links()->getText()},
                {"user", context->user()->getText()},
                {"group", context->group()->getText()},
                {"size", context->size()->getText()},
                {"month", context->month()->getText()},
                {"day", context->day()->getText()},
                {"time", context->time()->getText()},
                {"path", path}
            };
            return row;
        }
    };

    inline DB::Table parseLs(std::string output) {
        antlr4::ANTLRInputStream input(output);
        OutputLexer lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);
        OutputParser parser(&tokens);

        OutputParser::LsContext* tree = parser.ls();
        LsParserVisitor visitor;
        return visitor.visitOutput(tree).as<DB::Table>();
    }
}