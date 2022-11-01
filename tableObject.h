// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#ifndef INC_281SQL_TABLEOBJECT_H
#define INC_281SQL_TABLEOBJECT_H
#include <vector>
#include "TableEntry.h"
#include <unordered_map>
#include <map>
#include <iostream>
using std::unordered_map;
using std::map;
using std::vector;
using namespace std;
const string fourTypes[4] = {"string", "double", "int", "bool"};

struct Table{
    explicit Table(string name_):name{name_}{;}
    void printTable() const;
    void printTableInfo();
    void init(const vector<EntryType>&, const vector<string>&);

    // data segment
    vector<vector<TableEntry>> table;       // table consists a vector of rows
    unordered_map<string,size_t> columnIdx; // column name -> column index  ( in a row )
    vector<EntryType> columnType;
    string name;

};

void Table::printTable() const{
    printf("Table: %s:\n",name.c_str());
    for(size_t i = 0; i < table.size(); i++){
        printf("Row %zu:",i);
        for(size_t j = 0; j < columnIdx.size(); j ++){
            cout << " " << table[i][j];
        }
        cout << '\n';
    }
}

void Table::printTableInfo() {
    for(auto iter = columnIdx.begin(); iter != columnIdx.end(); iter ++){
        std::cout << (*iter).first << ": " << fourTypes[(size_t)columnType[(*iter).second]] << '\n';
    }
}
void Table::init(const vector<EntryType>& column_data_type, const vector<string>& column_name){
    if (column_name.size() != column_data_type.size()){
        cerr << "Unequal length of column data type and column name in INIT!\n";
        exit(6);
    }
    columnIdx.reserve(column_data_type.size());
    columnType.reserve(column_data_type.size());
    for (size_t i = 0; i < column_data_type.size(); ++i) {
        columnIdx[column_name[i]] = i;
        columnType.push_back(column_data_type[i]);
    }

}

#endif //INC_281SQL_TABLEOBJECT_H
