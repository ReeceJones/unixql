#include "interceptor.h"


namespace Interceptor {
    json commands = {};

    void loadCommands(std::string file_path) {
        std::ifstream commands_file;
        commands_file.open(file_path, std::ifstream::in);
        commands = json::parse(commands_file);
        commands_file.close();
        std::cout << "Loaded commands file: " << file_path << std::endl;
    }

    std::optional<std::vector<std::string>> interceptTable(std::string table) {
        if (commands.empty()) {
            std::cerr << "Commands json file not loaded! Cannot execute command until this is fixed." << std::endl;
            return std::nullopt;
        }

        // iterate through command objects to file math
        for (auto& obj : commands.items()) {
            // build regex pattern
            std::regex pattern(obj.key());
            if (std::regex_match(table, pattern)) {
                // load attributes
                std::vector<std::string> args;
                for (auto arg : obj.value()["expanded"]) {
                    args.push_back(arg.get<std::string>());
                }
                return args;
            }
        }

        return std::nullopt;
    }
}