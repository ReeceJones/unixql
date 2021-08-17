#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <any>
#include <algorithm>

namespace DB {
    class Table
    {
    public:
        typedef std::map<std::string, std::string> Row;
        Table(std::string name, std::vector<std::string> column_names);
        Table(std::string name, std::vector<std::string> column_names, std::vector<Row> rows);
        void push_back(Row row);
        
        Table select(std::vector<std::string> columns);
        Table where(std::function<bool( Row )> filter);

        std::string toString();
        void print();
    private:
        std::string name;
        std::vector<std::string> column_names;
        std::vector<Row> rows;
    };

}
