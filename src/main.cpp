#include <iostream>
#include <fstream>
#include <string>
#include "antlr4-runtime.h"
#include "UnixqlLexer.h"
#include "unixql_visitor.h"

int main(int argc, char* argv[]) {
    // std::ifstream test;
    // test.open(argv[1], std::ifstream::in);
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