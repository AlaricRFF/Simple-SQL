// Project Identifier: C0F4DFE8B340D81183C208F70F9D2D797908754D
#include <iostream>
#include <unordered_map>
#include "SQL_functions.h"
using namespace std;
using std::unordered_map;
using std::string;

int main() {
    ios_base::sync_with_stdio(false); // you should already have this
    cin >> std::boolalpha;  // add these two lines
    cout << std::boolalpha; // add these two lines
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