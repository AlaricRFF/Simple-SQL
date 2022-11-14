// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#ifndef INC_281SQL_SQL_FUNCTIONS_H
#define INC_281SQL_SQL_FUNCTIONS_H
#include <tableObject.h>
#include <iostream>
#include <string>
#include <unordered_map>

using TAB = unordered_map<string,Table*>;
void CREATE(TAB&);
void REMOVE(TAB&);
void INSERT(TAB &);
void PRINT(TAB&, bool);
void DELETE(TAB&);
void GENERATE(TAB&);
void JOIN(TAB&,bool);
/// Error Handling
bool tableNotExist(const TAB::iterator&, const TAB&, const string&, const string&);
bool columnNotExist(Table*, const string&, const string&);




#endif //INC_281SQL_SQL_FUNCTIONS_H
