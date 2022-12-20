// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#ifndef INC_281SQL_TABLEOBJECT_H
#define INC_281SQL_TABLEOBJECT_H
#include <vector>
#include <TableEntry.h>
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

inline bool cmp_pairS2ZU(const columnMatch& l, const columnMatch& h){
        return l.second > h.second;
}
// predicates for a whole row
inline bool less_entry(const rowType& dest, const TableEntry& pivot, size_t idx){
    return dest[idx] < pivot;
}
inline bool greater_entry(const rowType & dest, const TableEntry& pivot, size_t idx){
    return dest[idx] > pivot;
}
inline bool equal_entry(const rowType& dest, const TableEntry& pivot, size_t idx){
    return dest[idx] == pivot;
}
class Table{
public:
    explicit Table(const string& name_):name{name_}{;}
    void printTableAll(const vector<size_t>&) const;
    void printTableInfo();
    void init(const vector<EntryType>&, const vector<string>&);
    void insert(const size_t&);
    void hash_gen(const size_t&, const string&);
    void bst_gen(const size_t&, const string&);
    void deleteCol(const string&);
    void update(const string&, const char&);
    size_t join_non_quiet(const Table&, const vector<pair<size_t,uint8_t>>&, const string&, const string&);
    size_t join_quiet(const Table&, const string&, const string&);
    size_t printCondRows_non_quiet(const string&, const vector<size_t>&);
    size_t printCondRows_quiet(const string&);
    TableEntry entry_gen(const EntryType&);
    const unordered_map<string,size_t>& getColumnIdx() const;
    size_t getTableSize() const;
    const string& getTableName() const;
    idxInUse getIdxType() const;
    string getIndexedCol() const;


private:
    // data segment
    vector<vector<TableEntry>> table;       // table consists a vector of rows
    unordered_map<string,size_t> columnIdx; // column name -> column index  ( in a row )
    vector<EntryType> columnType;
    unordered_map<TableEntry,vector<size_t>> hash_map; // map table entry to row indices
    map<TableEntry,vector<size_t>> bst_map;
    string name;
    string idxed_col;
    idxInUse hashOrBst = idxInUse::NONE;
    // helper
    EntryType addType(const char& tp);
};




#endif //INC_281SQL_TABLEOBJECT_H
