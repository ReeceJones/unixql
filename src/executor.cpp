#include "executor.h"

namespace Executor {
    void executeProgram(std::vector<std::string> columns, std::string table) {
        std::vector<std::string> args { table };
        execute(args);
    }

    void execute(std::vector<std::string> args) {
        pid_t f = fork();
        if (f == 0) { // child process
            // initialize argv
            auto argv_size = sizeof(char*) * (args.size() + 1);
            char** argv = (char**)malloc(argv_size);
            memset(argv, 0, argv_size);
            char** itr = argv;
            for (auto arg : args) {
                *(itr++) = strdup(arg.c_str());
            }

            // execute subprocess
            execvp(argv[0], (char* const*)argv);

            std::cerr << "Failed to load process" << std::endl;
            exit(1);
        }
        else { // parent process
            // wait for child process to finish
            int code;
            waitpid(f, &code, 0);
            std::cout << "Process " << f << " finished with code " << code << std::endl;
        }
    }
}