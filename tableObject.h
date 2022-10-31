// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#ifndef INC_281SQL_TABLEOBJECT_H
#define INC_281SQL_TABLEOBJECT_H
#include <vector>
#include "TableEntry.h"
#include <unordered_map>
using std::unordered_map;
using std::vector;
using namespace std;
using columnInfo = pair<EntryType,size_t>; // EntryType -> column data type; size_t -> column index
const string fourTypes[4] = {"string", "double", "int", "bool"};

class Table{
public:
    explicit Table(string name_):name{name_}{;}
    string getName() const;
    void printRow() const;
    void printTableInfo();
    void init(const vector<EntryType>&, const vector<string>&);
private:
    vector<vector<TableEntry>> table;       // table consists a vector of rows
    unordered_map<string,columnInfo> columnIdx; // column name -> column index  ( in a row )
    string name;

};

string Table::getName() const {
    return name;
}
void Table::printRow() const{
    return;
}

void Table::printTableInfo() {
    for(auto iter = columnIdx.begin(); iter != columnIdx.end(); iter ++){
        cout << (*iter).first << ": " << fourTypes[(size_t)((*iter).second.first)] <<
        ", idx: " << (*iter).second.second << '\n';
    }
}
void Table::init(const vector<EntryType>& column_data_type, const vector<string>& column_name){
    if (column_name.size() != column_data_type.size()){
        cerr << "Unequal length of column data type and column name in INIT!\n";
        exit(6);
    }
    for (size_t i = 0; i < column_data_type.size(); ++i) {
        columnIdx.insert({column_name[i], make_pair(column_data_type[i],i)});
    }

}

#endif //INC_281SQL_TABLEOBJECT_H
