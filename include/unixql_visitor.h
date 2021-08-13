#pragma once

#include <string>
#include <vector>

#include "executor.h"
#include "UnixqlParser.h"
#include "antlr4-runtime.h"

class  UnixQLVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:
    antlrcpp::Any visitProgram(UnixqlParser::ProgramContext *context);
    antlrcpp::Any visitColumns(UnixqlParser::ColumnsContext* context);
    antlrcpp::Any visitTable(UnixqlParser::TableContext* context);
};
