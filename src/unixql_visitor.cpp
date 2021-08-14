#include "unixql_visitor.h"

antlrcpp::Any UnixQLVisitor::visitProgram(UnixqlParser::ProgramContext* context) {
    // extract columns and tables
    std::vector<std::string> columns = visitColumns(context->columns()).as<std::vector<std::string>>();
    std::string table = visitTable(context->table()).as<std::string>();

    // execute the command now
    Executor::executeProgram(columns, table);

    return "";
}

antlrcpp::Any UnixQLVisitor::visitColumns(UnixqlParser::ColumnsContext* context) {
    std::vector<std::string> columns;
    for (auto column : context->column_selection) {
        columns.push_back(column->VARIABLE()->getText());
    }
    return columns;
}

antlrcpp::Any UnixQLVisitor::visitTable(UnixqlParser::TableContext* context) {
    return context->VARIABLE()->getText();
}