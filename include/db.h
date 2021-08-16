#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <any>
#include <map>

namespace DB {
    class Table
    {
    public:
        typedef std::map<std::string, std::string> Row;
        Table(std::string name, std::vector<std::string> column_names);
        void push_back(Row row);
        std::string toString();
        void print();
    private:
        std::string name;
        std::vector<std::string> column_names;
        std::vector<Row> rows;
    };

}
