#include <iostream>
#include <fstream>
#include <string>
#include "antlr4-runtime.h"
#include "UnixqlLexer.h"
#include "unixql_visitor.h"
#include "interceptor.h"
#include "parsers.h"

int main(int argc, char* argv[]) {
    // load our commands.json file
    Interceptor::loadCommands("commands.json");
    // load our parsers
    Parsers::loadParsers();

    std::string test;
    getline(std::cin, test);
    antlr4::ANTLRInputStream input(test);
    UnixqlLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    UnixqlParser parser(&tokens);

    UnixqlParser::ProgramContext* tree = parser.program();
    UnixQLVisitor visitor;
    visitor.visitProgram(tree);

    return 0;
}