// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#ifndef INC_281SQL_TABLEOBJECT_H
#define INC_281SQL_TABLEOBJECT_H
#include <vector>
#include "TableEntry.h"
#include <unordered_map>
using std::unordered_map;
using std::vector;
using namespace std;

class Table{
public:
    explicit Table(string name_):name{name_}{;}
    string getName() const;
private:
    vector<vector<TableEntry>> table;
    string name;
};

string Table::getName() const {
    return name;
}
#endif //INC_281SQL_TABLEOBJECT_H
