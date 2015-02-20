#ifndef PARAMETERMANAGER_H
#define PARAMETERMANAGER_H
#include <iostream>
#include <string>
#include <vector>
#include "iniparser.h"
using namespace std;
class ParameterManager
{
private:
    static const string file ;
    IniParser parser;
    static ParameterManager* instance;
    vector<string> groups;
    ParameterManager();
public :
    static ParameterManager *getInstance();
    void beginGroup(string group);
    void endGroup();
    template <typename T> T get ( std::string key , bool * isOk = NULL)
    {
        string global_key;
        for(int i = 0 ; i < groups.size() ;  i++)
            global_key+=groups[i]+".";
        global_key+=key;
        return parser.getValue<T>(global_key , isOk);

    }

};

#endif // PARAMETERMANAGER_H
