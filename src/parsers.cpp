#include "parsers.h"

namespace Parsers {
    std::map<std::string, ParserFn> parsers = {};

    void loadParsers() {
        // register all of our parsers
        registerParser("ls_parser", Parsers::Ls::parseLs);

        std::cout << "Loaded parsers" << std::endl;
    }

    bool registerParser(std::string parser_name, ParserFn fn) {
        if (!parsers.empty() && parsers.find(parser_name) == parsers.end()) {
            std::cerr << "Parser " << parser_name << " is already registered!" << std::endl;
            return false;
        }

        parsers[parser_name] = fn;
        return true;
    }

    std::optional<ParserFn> resolveParser(std::string parser_name) {
        auto parser = parsers.find(parser_name);
        if (parser == parsers.end()) {
            std::cerr << "Could not find parser " << parser_name << "!" << std::endl;
            return std::nullopt;
        }

        return parser->second;
    }
}
