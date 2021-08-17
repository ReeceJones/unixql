#include "db.h"

namespace DB {
    Table::Table(std::string name, std::vector<std::string> column_names) {
        this->name = name;
        this->column_names = column_names;
        this->rows = {};
    }

    Table::Table(std::string name, std::vector<std::string> column_names, std::vector<Row> rows) {
        this->name = name;
        this->column_names = column_names;
        this->rows = rows;
    }

    void Table::push_back(Row row) {
        // validate row
        for (auto itr : row) {
            if (std::find(this->column_names.begin(), this->column_names.end(), itr.first) == this->column_names.end()
                && this->column_names.size() > 0) {
                std::cerr << "Column " << itr.first << " does not exist in table" << std::endl;
                return;
            }
        }

        this->rows.push_back(row);
    }

    Table Table::select() {
        return Table(this->name, this->column_names, this->rows);
    }

    Table Table::where(std::function<bool( Row )> filter) {
        std::vector<Row> selected_rows;
        for (auto row : this->rows) {
            if (filter(row)) {
                selected_rows.push_back(row);
            }
        }

        return Table(this->name, this->column_names, selected_rows);
    }

    std::string Table::toString() {
        // first compute padding widths
        std::map<std::string, int> column_widths;
        for (auto elem : this->column_names) {
            auto len = elem.size();
            if (column_widths.find(elem) == column_widths.end()) {
                column_widths[elem] = (int)len;
            }
            else if (len > column_widths[elem]) {
                column_widths[elem] = (int)len;
            }
        }
        for (auto row : this->rows) {
            for (auto elem : row) {
                auto len = elem.second.size();
                if (len > column_widths[elem.first]) {
                    column_widths[elem.first] = (int)len;
                }
            }
        }


        // now we can build string
        std::stringstream ss;
        // do the headers
        std::vector<std::string> headers = this->column_names;
        std::sort(headers.begin(), headers.end());
        ss << "+";
        for (auto header : headers) {
            ss << "-";
            for (int i = 0; i < column_widths[header]; i++) {
                ss << "-";
            }
            ss << "-+";
        }
        ss << std::endl;
        ss << "|";
        for (auto header : headers) {
            ss << " " << header;
            for (int i = 0; i < column_widths[header] - (int)header.size(); i++) {
                ss << " ";
            }
            ss << " |";
        }
        ss << std::endl;
        ss << "+";
        for (auto header : headers) {
            ss << "-";
            for (int i = 0; i < column_widths[header]; i++) {
                ss << "-";
            }
            ss << "-+";
        }
        ss << std::endl;

        // do the body
        int ctr = 0;
        for (auto row : this->rows) {
            ss << "|";
            for (auto elem : row) {
                ss << " " << elem.second;
                for (int i = 0; i < column_widths[elem.first] - elem.second.size(); i++) {
                    ss << " ";
                }
                ss << " |";
            }
            ss << std::endl;
            if (++ctr > 50) {
                ss << "... rows hidden" << std::endl;
            }
        }

        // do the footer
        ss << "+";
        for (auto header : headers) {
            ss << "-";
            for (int i = 0; i < column_widths[header]; i++) {
                ss << "-";
            }
            ss << "-+";
        }
        ss << std::endl;

        return ss.str();
    }

    void Table::print() {
        std::cout << this->toString() << std::endl;
    }
}
