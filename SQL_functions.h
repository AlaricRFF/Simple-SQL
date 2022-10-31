// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#ifndef INC_281SQL_SQL_FUNCTIONS_H
#define INC_281SQL_SQL_FUNCTIONS_H
#include "tableObject.h"
#include <iostream>
#include <string>
#include <unordered_map>

void CREATE(unordered_map<string,Table*>&);


void CREATE(unordered_map<string,Table*>& DataBase){
    string tableName;
    cin >> tableName;
    Table* newTable = new Table(tableName);
    DataBase.insert({tableName,newTable});
}
#endif //INC_281SQL_SQL_FUNCTIONS_H
