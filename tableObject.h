// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#ifndef INC_281SQL_TABLEOBJECT_H
#define INC_281SQL_TABLEOBJECT_H
#include <vector>
#include "TableEntry.h"
#include <unordered_map>
#include <map>
#include <iostream>
#include <algorithm>
using std::unordered_map;
using std::map;
using std::vector;
using namespace std;
using columnMatch = pair<string,size_t>;
using rowType = vector<TableEntry>;
const string fourTypes[4] = {"string", "double", "int", "bool"};
enum class idxInUse : uint8_t { HASH, BST, NONE };

bool cmp_pairS2ZU(const columnMatch& l, const columnMatch& h){
        return l.second > h.second;
}
// predicates for a whole row
bool less_entry(const rowType& dest, const TableEntry& pivot, size_t idx){
    return dest[idx] < pivot;
}
bool greater_entry(const rowType & dest, const TableEntry& pivot, size_t idx){
    return dest[idx] > pivot;
}
bool equal_entry(const rowType& dest, const TableEntry& pivot, size_t idx){
    return dest[idx] == pivot;
}
struct Table{
    explicit Table(string name_):name{name_}{;}
    void printTable() const;
    void printTableInfo();
    void init(const vector<EntryType>&, const vector<string>&);
    void hash_gen(const size_t&);
    void bst_gen(const size_t&);
    void deleteCol(const string&); // return number of rows deleted
    TableEntry entry_gen(const EntryType&);

    // data segment
    vector<vector<TableEntry>> table;       // table consists a vector of rows
    unordered_map<string,size_t> columnIdx; // column name -> column index  ( in a row )
    vector<EntryType> columnType;
    unordered_map<TableEntry,vector<size_t>> hash_map;
    map<TableEntry,vector<size_t>> bst_map;
    string name;
    string idxed_col;
    idxInUse hashOrBst = idxInUse::NONE;
};
TableEntry Table::entry_gen(const EntryType& entry_type){
    switch (entry_type) {
        case EntryType::String:{
            string val;
            cin >> val;
            TableEntry entry(val);
            return entry;
        }
        case EntryType::Double:{
            double val;
            cin >> val;
            TableEntry entry(val);
            return entry;
        }
        case EntryType::Int:{
            int val;
            cin >> val;
            TableEntry entry(val);
            return entry;
        }
        case EntryType::Bool:{
            bool val;
            cin >> val;
            TableEntry entry(val);
            return entry;
        }
        default:{
            cerr << "Wrong type during entry_gen!\n";
            exit(6);
        }
    }

}

void Table::hash_gen(const size_t& idx){
    hash_map.clear();
    hash_map.reserve(table.size());
    for(size_t i = 0; i < table.size(); i ++){
        hash_map[table[i][idx]].push_back(i);
    }
    hashOrBst = idxInUse::HASH;
}

void Table::bst_gen(const size_t &idx) {
    bst_map.clear();
    // bst_map.reserve()
    for(size_t i = 0; i < table.size(); i ++){
        bst_map[table[i][idx]].push_back(i);
    }
    hashOrBst = idxInUse::BST;
}

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
    vector<pair<string,size_t>> seq(columnIdx.begin(),columnIdx.end());
    sort(seq.begin(),seq.end(),cmp_pairS2ZU);
    for(const auto &e:seq){
        printf("%s\tType: %s\n",e.first.c_str(),fourTypes[(int)(columnType[e.second])].c_str());
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

void Table::deleteCol(const string& colName2D){
    size_t col_idx = columnIdx[colName2D];
    EntryType entry_type = columnType[col_idx];
    char op;
    cin >> op;
    TableEntry pivot = entry_gen(entry_type); // equivalent to cin >> cmp_subject
    size_t init_size = table.size();
    size_t de_size;
    /// room for index!!!
    if (hashOrBst != idxInUse::NONE){
        ;
    }
    else{
        switch (op) {
            case '>':{
                auto pd = remove_if(table.begin(),table.end(), [&col_idx, &pivot](const rowType& r){return r[col_idx] > pivot;});
                table = vector<rowType>(table.begin(),pd);
                break;
            }
            case '=':{
                auto pd = remove_if(table.begin(),table.end(),[&col_idx,&pivot](const rowType& r){return r[col_idx] == pivot;});
                table = vector<rowType>(table.begin(),pd);
                break;
            }
            case '<':{
                auto pd = remove_if(table.begin(),table.end(),[&col_idx,&pivot](const rowType& r){return r[col_idx] < pivot;});
                table = vector<rowType>(table.begin(),pd);
                break;
            }
            default:{
                cerr << "Wrong binary operator given to DELETE!\n";
                exit(6);
            }
        }
        de_size = table.size();
    }
    cout << "Deleted " << init_size - de_size << " rows from " << name << '\n';
}


#endif //INC_281SQL_TABLEOBJECT_H
