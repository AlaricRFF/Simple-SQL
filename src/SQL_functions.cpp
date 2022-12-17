#include <SQL_functions.h>
#include "../inc/tableObject.h"

bool tableNotExist(const TAB::iterator& idx, const TAB& DataBase, const string& cmd, const string& tableName){
    string garbage;
    if (idx == DataBase.end()){
        cout << "Error during " << cmd << ": " << tableName << " does not name a table in the database\n";
        getline(cin,garbage); // tableName here is treated as garbage collector
        return true;
    }
    return false;
}

bool columnNotExist(Table* targetTable, const string& colName, const string& cmd){
    string garbage;
    auto idx = targetTable->getColumnIdx().find(colName);
    if (idx == targetTable->getColumnIdx().end()){
        cout << "Error during " << cmd << ": " << colName << " does not name a column in " << targetTable->getTableName() << '\n';
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
        cout << "Error during CREATE: Cannot create already existing table " << tableName << '\n';
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
    cout << "New table " << tableName << " with column(s) ";
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
        cout << "Error during REMOVE: " << tableName << " does not name a table in the database\n";
        // getline(cin,tableName); // tableName here is treated as garbage collector
        return;
    }
    /// ERROR HANDLING
    cout << "Table " << (*idx).first << " deleted\n";
    delete (*idx).second;
    DataBase.erase(idx);

}

void INSERT(unordered_map<string,Table*>& DataBase){
    string tableName, garbage;
    cin >> tableName >> tableName;
    auto idx = DataBase.find(tableName);
    /// ERROR HANDLING
    if (idx == DataBase.end()){
        cout << "Error during INSERT: " << tableName << " does not name a table in the database\n";
        getline(cin,tableName); // tableName here is treated as garbage collector
        return;
    }
    /// ERROR HANDLING
    size_t N;
    cin >> N >> garbage;
    idx->second->insert(N);
}

void PRINT(unordered_map<string,Table*>& DataBase, bool quiet){
    string tableName;
    cin >> tableName >> tableName;
    auto idx = DataBase.find(tableName);
    /// ERROR HANDLING
    if (idx == DataBase.end()){
        cout << "Error during PRINT: " << tableName << " does not name a table in the database\n";
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
        auto fdt = targetTable->getColumnIdx().find(print_colName);
        col_idx_print[i] = fdt->second;
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
            for(auto & i : col_name_all)
                cout << i << ' ';
            cout << '\n';
            targetTable->printTableAll(col_idx_print);
        }
        cout << "Printed "<< targetTable->getTableSize() << " matching rows from " << tableName <<"\n";
    }
    else{
        size_t num_rows = 0;
        string pivotColName;
        cin >> pivotColName;
        if (!quiet){
            /// ERROR HANDLING
            if (columnNotExist(targetTable,pivotColName,"PRINT"))
                return;
            /// ERROR HANDLING
            for(auto & i : col_name_all)
                cout << i << ' ';
            cout << '\n';
            num_rows = targetTable->printCondRows_non_quiet(pivotColName, col_idx_print);
            cout << "Printed "<< num_rows << " matching rows from " << tableName <<"\n";
        }
        else {
            num_rows = targetTable->printCondRows_quiet(pivotColName);
            cout << "Printed " << num_rows << " matching rows from " << tableName << "\n";
        }
    }

}

// GENERATE should not worry about the influence from the change of data of on map or unordered_map
// instead, INSERT and DELETE should keep the thing in the index_col data structure up to date
void GENERATE(TAB& DataBase){
    string tableName;
    cin >> tableName >> tableName;
    auto idx = DataBase.find(tableName);
    /// Error handling
    if (tableNotExist(idx,DataBase,"GENERATE",tableName))
        return;
    /// Error handling
    string idxType, colName;
    cin >> idxType;
    cin >> colName >> colName >> colName;
    Table* targetTable = idx->second;
    auto columnFind = targetTable->getColumnIdx().find(colName);
    /// Error handling
    if (columnFind == targetTable->getColumnIdx().end()){
        cout << "Error during GENERATE: " << colName << " does not name a column in " << targetTable->getTableName() << '\n';
        return;
    }
    /// Error handling
    idxInUse jd = (idxType[0] == 'h' ? idxInUse::HASH : idxInUse::BST);
    /// Has already generated the index for this column
    if (colName == targetTable->getIndexedCol() && targetTable->getIdxType() == jd){
            cout << "Created " <<idxType << " index for table " << targetTable->getTableName() << " on column " << colName << '\n';
            return;
     }
    if (jd == idxInUse::HASH){
        size_t col_idx = columnFind->second;
        targetTable->hash_gen(col_idx,colName);
    }
    else{
        size_t col_idx = columnFind->second;
        targetTable->bst_gen(col_idx,colName);
    }
    cout << "Created " <<idxType << " index for table " << targetTable->getTableName() << " on column " << colName << '\n';
}

void DELETE(TAB& DataBase){
    string tableName;
    cin >> tableName >> tableName;
    auto idx = DataBase.find(tableName);
    /// Error handling
    if (tableNotExist(idx,DataBase,"DELETE",tableName))
        return;
    /// Error handling
    Table* targetTable = (*idx).second;
    string colName;
    cin >> colName >> colName;
    /// Error handling
    if (columnNotExist(targetTable,colName,"DELETE"))
        return;
    /// Error handling
    targetTable->deleteCol(colName);
}

void JOIN(TAB& DataBase, bool quiet){
    string tableName1, tableName2, pivotCol1, pivotCol2, garbage;
    cin >> tableName1 >> tableName2 >> tableName2 >> pivotCol1 >> pivotCol1 >> pivotCol2 >> pivotCol2;
    auto t1 = DataBase.find(tableName1);
    auto t2 = DataBase.find(tableName2);
    /// Error handling
    if ( tableNotExist(t1,DataBase,"JOIN",tableName1) )
        return;
    if ( tableNotExist(t2,DataBase,"JOIN",tableName2) )
        return;
    /// Error handling
    Table *targetTable1 = t1->second, *targetTable2 = t2->second;
    /// Error handling
    if (columnNotExist(targetTable1,pivotCol1,"JOIN"))
        return;
    if (columnNotExist(targetTable2,pivotCol2,"JOIN"))
        return;
    /// Error handling
    size_t N_col;
    vector<pair<size_t, uint8_t>> printCol_spec; // < column index , table num >
    vector<string> col_name_holder;
    cin >> garbage >> garbage >> N_col;
    printCol_spec.reserve(N_col);
    col_name_holder.reserve(N_col);
    for (size_t i = 0; i < N_col; ++i) {
        string temp;
        uint8_t num;
        size_t col_idx;
        cin >> temp >> num;
        /// Error handling
        /// Error handling
        if (num == '1'){
            if (columnNotExist(targetTable1,temp,"JOIN"))
                return;
            auto fdt = targetTable1->getColumnIdx().find(temp);
            col_idx = fdt->second;
        }
        else{
            if (columnNotExist(targetTable2,temp,"JOIN"))
                return;
            auto fdt = targetTable2->getColumnIdx().find(temp);
            col_idx = fdt->second;
        }
        printCol_spec.emplace_back(col_idx,num);
        col_name_holder.push_back(temp);
    }
    // make
    size_t matched_rows = 0;
    if (!quiet){
        for(const auto& col_name : col_name_holder)
            cout << col_name << ' ';
        cout << '\n';
        matched_rows = targetTable1->join_non_quiet(*targetTable2,printCol_spec,pivotCol1,pivotCol2);
        cout << "Printed " << matched_rows << " rows from joining " << targetTable1->getTableName() << " to " << targetTable2->getTableName() << '\n';
    }
    else{
        matched_rows = targetTable1->join_quiet(*targetTable2,pivotCol1,pivotCol2);
        cout << "Printed " << matched_rows << " rows from joining " << targetTable1->getTableName() << " to " << targetTable2->getTableName() << '\n';
    }
}

void UPDATE(TAB& Database){
    string tableName, col_2change, update_type;
    cin >> tableName >> col_2change >> col_2change >> update_type >> update_type;
    auto tbl = Database.find(tableName);
    // error checking
    if (tableNotExist(tbl,Database,"UPDATE",tableName) )
        return;
    // error checking
    Table* targetTable = (*tbl).second;
    if (update_type[0] == 'D')
    {
        // find if column exists
        if (targetTable->getColumnIdx().find(col_2change) == targetTable->getColumnIdx().end()){
            cout << "column " << col_2change << " doesn't exist in table " << tableName << '\n';
            return;
        }
        
    }
    
}