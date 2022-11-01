// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#ifndef INC_281SQL_SQL_FUNCTIONS_H
#define INC_281SQL_SQL_FUNCTIONS_H
#include "tableObject.h"
#include <iostream>
#include <string>
#include <unordered_map>

void CREATE(unordered_map<string,Table*>&);
void REMOVE(unordered_map<string,Table*>&);
void INSERT(unordered_map<string,Table*>&);

void CREATE(unordered_map<string,Table*>& DataBase){
    string tableName;
    cin >> tableName;
    /// ERROR HANDLING
    auto idx = DataBase.find(tableName);
    if (idx == DataBase.end()){
        printf("Error during CREATE: Cannot create already existing table %s\n",tableName.c_str());
        getline(cin,tableName); // tableName here is treated as garbage collector
        return;
    }
    /// ERROR HANDLING
    Table* newTable = new Table(tableName);
    DataBase.insert({tableName,newTable});
    // initialize table
    size_t N;
    cin >> N;
    vector<EntryType> column_data_type;
    column_data_type.resize(N);
    for (size_t i = 0; i < N; ++i) {
        string temp;
        cin >> temp;
        switch (temp[0]) {
            case 'b':{
                column_data_type[i] = EntryType::Bool;
                break;
            }
            case 'd':{
                column_data_type[i] = EntryType::Double;
                break;
            }
            case 's':{
                column_data_type[i] = EntryType::String;
                break;
            }
            case 'i':{
                column_data_type[i] = EntryType::Int;
                break;
            }
            default:{
                cerr << "Incompatible Data Type in CREATE!\n";
                exit(6);
                break;
            }
        }
    }
    vector<string> column_name;
    column_name.resize(N);
    for(size_t i = 0; i < N; i ++){
        string temp;
        cin >> temp;
        column_name[i] = temp;
    }
    newTable->init(column_data_type,column_name);
    printf("New table %s with column(s) ",tableName.c_str());
    for (size_t i = 0; i < column_name.size(); ++i) {
        cout << column_name[i] << ' ';
    }
    cout << "created\n";
}

void REMOVE(unordered_map<string,Table*>& DataBase){
    string tableName;
    cin >> tableName;
    /// ERROR HANDLING
    auto idx = DataBase.find(tableName);
    if (idx == DataBase.end()){
        printf("Error during REMOVE: %s does not name a table in the database\n",tableName.c_str());
        getline(cin,tableName); // tableName here is treated as garbage collector
        return;
    }
    /// ERROR HANDLING
    printf("Table %s deleted\n",(*idx).first.c_str());
    delete (*idx).second;
}

void INSERT(unordered_map<string,Table*>& DataBase){
    string tableName, garbage;
    cin >> tableName >> tableName;
    auto idx = DataBase.find(tableName);
    /// ERROR HANDLING
    if (idx == DataBase.end()){
        printf("Error during INSERT: %s does not name a table in the database\n",tableName.c_str());
        getline(cin,tableName); // tableName here is treated as garbage collector
        return;
    }
    /// ERROR HANDLING
    Table* targetTable = (*idx).second;
    size_t N;
    cin >> N;
    getline(cin,garbage);
    // resize table
    vector<vector<TableEntry>>& tableData = targetTable->table;
    targetTable->table.reserve(targetTable->table.size() + N);
    size_t column_num = targetTable->columnIdx.size();
    for (int i = 0; i < N; ++i) {
        vector<TableEntry> row(column_num);
        auto iter = targetTable->columnIdx.begin();
        for (int j = 0; j < column_num; ++j, ++ iter) {
            switch ( (*iter).second.first) {
                case EntryType::Bool:{

                }

                case EntryType::String:
                    break;
                case EntryType::Double:
                    break;
                case EntryType::Int:
                    break;
            }
        }
    }
}


#endif //INC_281SQL_SQL_FUNCTIONS_H
