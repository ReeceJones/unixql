#include "unixql_visitor.h"

antlrcpp::Any UnixQLVisitor::visitProgram(UnixqlParser::ProgramContext* context) {
    // extract columns and tables
    std::vector<std::string> columns = visitColumns(context->columns()).as<std::vector<std::string>>();
    std::string table = visitTable(context->table()).as<std::string>();

    std::vector<std::pair<std::string,std::string>> conditions;
    if (context->where()) {
        conditions.push_back(visitWhere(context->where()).as<std::pair<std::string,std::string>>());
    }

    // execute the command now
    Executor::executeProgram(columns, table, conditions);

    return "";
}

antlrcpp::Any UnixQLVisitor::visitColumns(UnixqlParser::ColumnsContext* context) {
    if (context->ALL()) {
        return std::vector<std::string>{};
    }

    std::vector<std::string> columns;
    for (auto column : context->column_selection) {
        columns.push_back(column->VARIABLE()->getText());
    }
    return columns;
}

antlrcpp::Any UnixQLVisitor::visitTable(UnixqlParser::TableContext* context) {
    return context->VARIABLE()->getText();
}


antlrcpp::Any UnixQLVisitor::visitWhere(UnixqlParser::WhereContext* context) {
    std::string column = context->condition()->VARIABLE()->getText();
    std::string match = context->condition()->STRING()->getText();
    match = match.substr(1, match.size() - 2);
    return std::make_pair(column, match);
}