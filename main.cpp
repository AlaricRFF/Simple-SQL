// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#include <iostream>
#include <unordered_map>
#include "SQL_functions.h"
#include "getopt.h"
using namespace std;
using std::unordered_map;
using std::string;

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(false); // you should already have this
    cin >> std::boolalpha;  // add these two lines
    cout << std::boolalpha; // add these two lines
    bool quiet = false;
    int gotopt;
    int optCnt = 0;
    int optionIdx = 0;
    option long_opts[] = {
            {"help",  no_argument,nullptr, 'h'},
            {"quiet", no_argument,nullptr, 'q'},
            {nullptr,0,nullptr, '\0'}
    };
    while ((gotopt = getopt_long(argc, argv, "qh", long_opts, &optionIdx)) != -1){
        switch (gotopt) {
            case 'q':{
                quiet = true;
                break;
            }
            case 'h':{
                printf("Silly SQL: A Simplified SQL Implementation which supports:\n"
                       "CREATE: make new table inside the database\n"
                       "REMOVE: remove existed table inside the database\n"
                       "INSERT: add data rows to existed tables inside the database\n"
                       "PRINT: print out data in table form of an existed table inside the database\n"
                       "DELETE: delete fragments of data rows using a predicate in a table existed inside the database\n"
                       "JOIN: print specialized data from two existed tables using predicates inside the database\n"
                       "GENERATE: generate a BST/HASH index of a column in an existed table inside the database\n"
                       "QUIT: quit the program\n"
                       "Thank you for being silly! ^_^\n");
                exit(0);
                break;
            }
        }
    }
    unordered_map<string,Table*> DataBase;
    string command;
    do{
        string garbage;
        cout << "% ";
        cin >> command;
        switch (command[0]) {
            case 'Q':{
                getline(cin,garbage);
                break;
            }
            case  'C':{
                CREATE(DataBase);
                break;
            }
            case 'R':{
                REMOVE(DataBase);
                break;
            }
            case 'I':{
                INSERT(DataBase);
                break;
            }
            case 'P':{

                break;
            }
            case 'D':{

                break;
            }
            case 'J':{

                break;
            }
            case 'G':{

                break;
            }
            case '#':{
                getline(cin,garbage);
                break;
            }
            default:{
                getline(cin,garbage);
                printf("Error: unrecognized command\n");
                break;
            }
        }
    }
    while (command[0] != 'Q');

    for(auto iter = DataBase.begin();iter!=DataBase.end();iter++){
        cout << (*iter).second->name << '\n';
        (*iter).second->printTableInfo();
        delete (*iter).second;
    }
    return 0;
}
/*
     for(auto iter = DataBase.begin();iter!=DataBase.end();iter++){
        cout << (*iter).second->getName() << '\n';
        delete (*iter).second;
    }
 */