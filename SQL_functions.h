// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#ifndef INC_281SQL_SQL_FUNCTIONS_H
#define INC_281SQL_SQL_FUNCTIONS_H
#include "tableObject.h"
#include <iostream>
#include <string>
#include <unordered_map>

using TAB = unordered_map<string,Table*>;
void CREATE(TAB&);
void REMOVE(TAB&);
void INSERT(TAB &);
void PRINT(TAB&, bool);
/// Error Handling
bool tableNotExist(const TAB::iterator&, const TAB&, const string&, const string&);
bool columnNotExist(Table*, const string&, const string&);


bool tableNotExist(const TAB::iterator& idx, const TAB& DataBase, const string& cmd, const string& tableName){
    string garbage;
    if (idx == DataBase.end()){
        printf("Error during %s: %s does not name a table in the database\n", cmd.c_str(), tableName.c_str());
        getline(cin,garbage); // tableName here is treated as garbage collector
        return true;
    }
    return false;
}

bool columnNotExist(Table* targetTable, const string& colName, const string& cmd){
    string garbage;
    auto idx = targetTable->columnIdx.find(colName);
    if (idx == targetTable->columnIdx.end()){
        printf("Error during %s: %s does not name a column in %s\n",cmd.c_str(),colName.c_str(),targetTable->name.c_str());
        getline(cin,garbage);
        return true;
    }
    return false;
}





void CREATE(unordered_map<string,Table*>& DataBase){
    string tableName;
    cin >> tableName;
    /// ERROR HANDLING
    auto idx = DataBase.find(tableName);
    if (idx != DataBase.end()){
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
    for (auto & i : column_name) {
        cout << i << ' ';
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
    DataBase.erase(idx);

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
    size_t startIdx = tableData.size(),
           endIdx = tableData.size() + N - 1;
    tableData.reserve(targetTable->table.size() + N);
    size_t column_num = targetTable->columnIdx.size();
    for (size_t i = 0; i < N; ++i) {
        vector<TableEntry> row;
        row.reserve(column_num);
        for(const auto& type : targetTable->columnType){
            switch ( type ) {
                case EntryType::Bool:{
                    bool data;
                    cin >> data;
                    row.emplace_back(data);
                    break;
                }
                case EntryType::String: {
                    string data;
                    cin >> data;
                    row.emplace_back(data);
                    break;
                }
                case EntryType::Double:{
                    double data;
                    cin >> data;
                    row.emplace_back(data);
                    break;
                }
                case EntryType::Int:{
                    int data;
                    cin >> data;
                    row.emplace_back(data);
                    break;
                }
                default:{
                    cerr << "Wrong Data Type in Insert!\n";
                    exit(6);
                }
            }
        }
        tableData.emplace_back(row);
    }
    printf("Added %zu rows to %s from position %zu to %zu\n", N, tableName.c_str(), startIdx, endIdx);
}

void PRINT(unordered_map<string,Table*>& DataBase, bool quiet){
    string tableName;
    cin >> tableName >> tableName;
    auto idx = DataBase.find(tableName);
    /// ERROR HANDLING
    if (idx == DataBase.end()){
        printf("Error during PRINT: %s does not name a table in the database\n",tableName.c_str());
        getline(cin,tableName); // tableName here is treated as garbage collector
        return;
    }
    /// ERROR HANDLING
    Table* targetTable = (*idx).second;
    size_t numCol;
    cin >> numCol;
    vector<size_t> col_idx_print(numCol); // store idx in table w.r.t print_Col_Name
    vector<string> col_name_all(numCol); // store <print_colname1> <print_colname2> ... <print_colnameN>
    for (size_t i = 0; i < numCol; ++i) {
        string print_colName;
        cin >> print_colName;
        /// ERROR HANDLING
        if (columnNotExist(targetTable,print_colName,"PRINT"))
            return;
        /// ERROR HANDLING
        col_idx_print[i] = targetTable->columnIdx[print_colName];
        col_name_all[i] = print_colName;
    }
    bool printAll = false;
    string pred;
    cin >> pred;
    if (pred[0] == 'A')
        printAll = true;
    else
        printAll = false;
    if (printAll){
        if (!quiet){
            for(size_t i = 0; i < col_name_all.size() - 1; i++)
                cout << col_name_all[i] << ' ';
            cout << col_name_all.back() << '\n';
            for (size_t row = 0; row < targetTable->table.size(); ++row) {
                    for (size_t col_idx = 0; col_idx < col_idx_print.size() - 1; col_idx++)
                        cout << targetTable->table[row][col_idx_print[col_idx]] << ' ';
                    cout << targetTable->table[row][col_idx_print.back()] << '\n';
            }
        }
        printf("Printed %zu matching rows from %s\n",targetTable->table.size(),tableName.c_str());
    }
    else{
        if (!quiet){

        }
    }

}
#endif //INC_281SQL_SQL_FUNCTIONS_H
