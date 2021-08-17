#include "executor.h"

namespace Executor {
    void executeProgram(std::vector<std::string> columns, std::string table, std::vector<std::pair<std::string,std::string>> conditions) {
        auto intercept = Interceptor::interceptTable(table);
        std::optional<std::vector<std::string>> args;
        std::optional<Parsers::ParserFn> parser;
        std::tie(args, parser) = intercept;

        std::string output;
        auto start = std::chrono::system_clock::now();
        if (args.has_value()) {
            output = execute(args.value());
        }
        else {
            std::vector targs { table };
            output = execute(targs);
        }

        // parse the output
        if (parser.has_value()) {
            auto table = parser.value()(output);
            // subset table
            for (auto condition : conditions) {
                auto filter = [=](DB::Table::Row row) {
                    auto elem = row.find(condition.first);
                    if (elem != row.end()) {
                        return condition.second.compare(elem->second) == 0;
                    }
                    else {
                        std::cerr << "Table has no column " << condition.first << std::endl;
                    }
                    return false;
                };
                table = table.where(filter);
            }
            table.print();
        }

        auto end = std::chrono::system_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Query took " << (double)diff.count() / 1000.0 << "ms" << std::endl;
    }

    std::string execute(std::vector<std::string> args) {
        // save original fds
        IO::FdSet fds{
            dup(IO::STDIN),
            dup(IO::STDOUT),
            dup(IO::STDERR)
        };

        // redirect output
        int pout[2];
        pipe(pout);
        dup2(pout[1], IO::STDOUT);
        close(pout[1]);

        pid_t f = fork();
        if (f == 0) { // child process
            close(pout[0]);
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
            // restore original fds
            dup2(fds[0], IO::STDIN);
            dup2(fds[1], IO::STDOUT);
            dup2(fds[2], IO::STDERR);
            close(fds[0]);
            close(fds[1]);
            close(fds[2]);

            // read output into string
            std::string output;
            char c;
            while (read(pout[0], &c, 1) > 0) {
                output.push_back(c); // not fast, but easy
            }
            // unredirect output
            close(pout[0]);

            // wait for child process to finish
            int code;
            waitpid(f, &code, 0);

            std::cerr << "Process " << f << " finished with code " << code << std::endl;

            return output;
        }
    }
}