#include <tableObject.h>

string Table::getIndexedCol() const{
    return idxed_col;
}

idxInUse Table::getIdxType() const {
    return hashOrBst;
}

size_t Table::getTableSize() const{
    return table.size();
}
const string& Table::getTableName() const{
    return name;
}
const unordered_map<string,size_t>& Table::getColumnIdx() const{
    return columnIdx;
}
void Table::printTableAll(const vector<size_t>& col_idx_print) const{
    for (const rowType& row : this->table) {
        for (size_t col_idx : col_idx_print)
            cout << row[col_idx] << ' ';
        cout << '\n';
    }
}


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

void Table::hash_gen(const size_t& idx, const string& colName){
    hash_map.clear();
    hash_map.reserve(table.size());
    for(size_t i = 0; i < table.size(); i ++){
        hash_map[table[i][idx]].push_back(i);
    }
    hashOrBst = idxInUse::HASH;
    idxed_col = colName;
}

void Table::bst_gen(const size_t &idx, const string& colName) {
    bst_map.clear();
    // bst_map.reserve()
    for(size_t i = 0; i < table.size(); i ++){
        bst_map[table[i][idx]].push_back(i);
    }
    hashOrBst = idxInUse::BST;
    idxed_col = colName;
}
void Table::insert(const size_t& N){
    size_t startIdx = table.size(),
            endIdx = table.size() + N - 1;
    table.reserve(startIdx + N);
    size_t column_num = columnIdx.size();
    /// consideration of possible generated INDEX
    size_t INDEXED_col_idx = 0;
    bool has_GEN_INDEX = false;
    if (hashOrBst != idxInUse::NONE){
        INDEXED_col_idx = columnIdx[idxed_col];
        has_GEN_INDEX = true;
    }
    for (size_t i = 0; i < N; ++i) {
        rowType row;
        row.reserve(column_num);
        for(const auto& type : columnType){
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
        if (has_GEN_INDEX){
            switch (hashOrBst) {
                case idxInUse::HASH :{
                    hash_map[row[INDEXED_col_idx]].push_back(i + startIdx);
                    break;
                }
                case idxInUse::BST :{
                    bst_map[row[INDEXED_col_idx]].push_back(i + startIdx);
                    break;
                }
                default :{
                    cerr << "Wrong index type in INSERT!\n";
                    exit(6);
                }
            }
        }
        table.emplace_back(row);
    }
    cout << "Added " << N << " rows to " << name << " from position " << startIdx << " to " << endIdx << '\n';
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
    size_t de_size = 0;
    /// room for index!!!
//    if (idxed_col == colName2D && hashOrBst != idxInUse::NONE){
//        if ( hashOrBst == idxInUse::HASH && op == '='){
//            ;
//        }
//    }

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

    /// update GENERATED index, if there is any
    if (hashOrBst == idxInUse::BST)
        bst_gen(columnIdx[idxed_col],idxed_col);
    if (hashOrBst == idxInUse::HASH)
        hash_gen(columnIdx[idxed_col],idxed_col);
    cout << "Deleted " << init_size - de_size << " rows from " << name << '\n';
}

size_t Table::printCondRows_non_quiet(const string& pivotColName, const vector<size_t>& col_idx_print){
    size_t pivot_idx = columnIdx[pivotColName];
    EntryType entry_type = columnType[pivot_idx];
    char op;
    cin >> op;
    TableEntry pivot = entry_gen(entry_type); // equivalent to cin >> cmp_subject
    /// indexed version
    if (hashOrBst != idxInUse::NONE && pivotColName == idxed_col){
        if (hashOrBst == idxInUse::BST){
            vector<size_t> row_idx_print; // all satisfied row indexes
            row_idx_print.reserve(table.size());
            switch (op) {
                case '>':{
                    auto lb = bst_map.upper_bound(pivot);
                    for(;lb != bst_map.end(); lb++){
                        row_idx_print.insert(row_idx_print.end(),((*lb).second).begin(),((*lb).second).end());
                    }
                    break;
                }
                case '<':{
                    auto up = bst_map.lower_bound(pivot);
                    for(auto iter = bst_map.begin(); iter != up; iter ++){
                        row_idx_print.insert(row_idx_print.end(),(*iter).second.begin(),(*iter).second.end());
                    }
                    break;
                }
                case '=':{
                    auto eq = bst_map.equal_range(pivot);
                    if (eq.first == eq.second){
                        /// BUG HERE !!!
                        /// nothing is found
                        return 0;
                    }
                    row_idx_print = eq.first->second;
                    break;
                }
                default:{
                    cerr << "Wrong binary operation in PRINT bst_map!\n";
                    exit(6);
                }
            }
            for(const auto& row_idx : row_idx_print){
                rowType row = table[row_idx];
                for(const auto& col_idx:col_idx_print)
                    cout << row[col_idx] << ' ';
                cout << '\n';
            }
            return row_idx_print.size();
        }
        else if(op == '=' && hashOrBst == idxInUse::HASH){
            auto find_ = hash_map.find(pivot);
            if(find_ != hash_map.end()){
                // find it!
                vector<size_t> row_idx_print(find_->second);
                for(const auto& row_idx : row_idx_print){
                    rowType row = table[row_idx];
                    for(const auto& col_idx:col_idx_print)
                        cout << row[col_idx] << ' ';
                    cout << '\n';
                }
                return row_idx_print.size();
            }
        }
        else{;}
    }
    /// no use on index
    vector<size_t> row_idx_print;
    row_idx_print.reserve(table.size());
    bool (*pred_ptr)(const rowType&, const TableEntry&, size_t);
    switch (op) {
        case '>':{
            pred_ptr = &greater_entry;
            break;
        }
        case '=':{
            pred_ptr = &equal_entry;
            break;
        }
        case '<':{
            pred_ptr = &less_entry;
            break;
        }
        default:{
            cerr << "Wrong binary operator in PRINT!\n";
            exit(6);
        }
    }
    size_t row_num = 0;
    for(const auto& row : table){
        if ( (*pred_ptr)(row,pivot,pivot_idx)){
            // print the row
            row_num ++;
            for(const auto& col_idx : col_idx_print)
                cout << row[col_idx] << ' ';
            cout << '\n';
        }
    }
    return row_num;

}

size_t Table::join_non_quiet(const Table& tab2, const vector<pair<size_t,uint8_t>>& printCol_spec,
          const string& pivotCol1, const string& pivotCol2){
    size_t pivotCol_idx_1 = columnIdx[pivotCol1];
    auto i2 = tab2.columnIdx.find(pivotCol2);
    size_t pivotCol_idx_2 = i2->second;
    /// check whether tab2 has hash index, if not, generate one
    unordered_map<TableEntry,vector<size_t>> hash_tab2;
    if ( !(tab2.hashOrBst == idxInUse::HASH && tab2.idxed_col == pivotCol2) ){
        hash_tab2.reserve(tab2.table.size());
        size_t i = 0;
        for(const auto& row : tab2.table){
            hash_tab2[row[pivotCol_idx_2]].push_back(i);
            i++;
        }
        size_t printed_num = 0;
        for (const auto& row_tab1 : this->table){
            auto match_vec = hash_tab2.find(row_tab1[pivotCol_idx_1]); // find matches
            if (match_vec != hash_tab2.end()){ // found match
                const vector<size_t>& mc = match_vec->second; /// check if this is necessary!
                for (const auto& row_2 : mc){
                    const rowType& row_tab2 = tab2.table[row_2];
                    for (const auto& ps : printCol_spec){
                        if (ps.second == '1')
                            cout << row_tab1[ps.first] << ' ';
                        else
                            cout << row_tab2[ps.first] << ' ';
                    }
                    cout << '\n';
                    printed_num ++; // increment match number of rows
                }
            }
        }
        return printed_num;
    }
    /// BUG HERE!!!!!!
    else{
        size_t printed_num = 0;
        for (const auto& row_tab1 : this->table){
            auto match_vec = tab2.hash_map.find(row_tab1[pivotCol_idx_1]); // find matches
            if (match_vec != tab2.hash_map.end()){ // found match
                const vector<size_t>& mc = match_vec->second; /// check if this is necessary!
                for (const auto& row_2 : mc){
                    const rowType& row_tab2 = tab2.table[row_2];
                    for (const auto& ps : printCol_spec){
                        if (ps.second == '1')
                            cout << row_tab1[ps.first] << ' ';
                        else
                            cout << row_tab2[ps.first] << ' ';
                    }
                    cout << '\n';
                    printed_num ++; // increment match number of rows
                }
            }
        }
        return printed_num;
    }

}

size_t Table::join_quiet(const Table& tab2, const string& pivotCol1, const string& pivotCol2){
    size_t pivotCol_idx_1 = columnIdx[pivotCol1];
    auto i2 = tab2.columnIdx.find(pivotCol2);
    size_t pivotCol_idx_2 = i2->second;
    // check whether tab2 has hash index, if not, generate one
    unordered_map<TableEntry,vector<size_t>> hash_tab2;
    if ( !(tab2.hashOrBst == idxInUse::HASH && tab2.idxed_col == pivotCol2) ){
        hash_tab2.reserve(tab2.table.size());
        size_t i = 0;
        for(const auto& row : tab2.table){
            hash_tab2[row[pivotCol_idx_2]].push_back(i);
            i++;
        }
        size_t printed_num = 0;
        for (const auto& row_tab1 : table){
            auto match_vec = hash_tab2.find(row_tab1[pivotCol_idx_1]);
            if (match_vec != hash_tab2.end()){ // found match
                printed_num += match_vec->second.size();
            }
        }
        return printed_num;
    }
    else{
        size_t printed_num = 0;
        for (const auto& row_tab1 : table){
            auto match_vec = tab2.hash_map.find(row_tab1[pivotCol_idx_1]);
            if (match_vec != tab2.hash_map.end()){ // found match
                printed_num += match_vec->second.size();
            }
        }
        return printed_num;
    }

}

size_t Table::printCondRows_quiet(const string& pivotColName){
    size_t pivot_idx = columnIdx[pivotColName];
    EntryType entry_type = columnType[pivot_idx];
    char op;
    cin >> op;
    TableEntry pivot = entry_gen(entry_type); // equivalent to cin >> cmp_subject
    /// indexed version
    if (hashOrBst != idxInUse::NONE && pivotColName == idxed_col){
        if (hashOrBst == idxInUse::BST){
            size_t print_row_num = 0;
            switch (op) {
                case '>':{
                    auto lb = bst_map.upper_bound(pivot);
                    for(;lb != bst_map.end(); lb++){
                        /// BUG HERE !!!!!!
                        print_row_num += lb->second.size();
                    }
                    break;
                }
                case '<':{
                    auto up = bst_map.lower_bound(pivot);
                    for(auto iter = bst_map.begin(); iter != up; iter ++){
                        /// BUG HERE !!!!!!
                        print_row_num += iter->second.size();
                    }
                    break;
                }
                case '=':{
                    auto eq = bst_map.equal_range(pivot);
                    if (eq.first == eq.second)
                        /// BUG HERE !!!!!!
                        return 0;
                    print_row_num = eq.first->second.size();
                    break;
                }
                default:{
                    cerr << "Wrong binary operation in PRINT bst_map!\n";
                    exit(6);
                }
            }
//            for(const auto& row_idx : row_idx_print){
//                rowType row = table[row_idx];
//                for(const auto& col_idx:col_idx_print)
//                    cout << row[col_idx] << ' ';
//                cout << '\n';
//            }
            return print_row_num;
        }
        else if(op == '=' && hashOrBst == idxInUse::HASH){
            auto find_ = hash_map.find(pivot);
            if(find_ != hash_map.end()){
                // find it!
                return find_->second.size();
            }
            else
                return 0;
        }
        else{;}
    }
    /// no use on index
    vector<size_t> row_idx_print;
    row_idx_print.reserve(table.size());
    bool (*pred_ptr)(const rowType&, const TableEntry&, size_t);
    switch (op) {
        case '>':{
            pred_ptr = &greater_entry;
            break;
        }
        case '=':{
            pred_ptr = &equal_entry;
            break;
        }
        case '<':{
            pred_ptr = &less_entry;
            break;
        }
        default:{
            cerr << "Wrong binary operator in PRINT!\n";
            exit(6);
        }
    }
    size_t row_num = 0;
    for(const auto& row : table){
        if ( (*pred_ptr)(row,pivot,pivot_idx)){
            // print the row
            row_num ++;
        }
    }
    return row_num;

}