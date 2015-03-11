#ifndef PARAMETERMANAGER_H
#define PARAMETERMANAGER_H
#include <iostream>
#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <locale>
#include <sstream>
#include <iostream>

//const char* ::filename = "Setting.xml";
const string ParameterManager::filename = "Setting.json";
using namespace boost::property_tree::xml_parser;

using namespace std;
class ParameterManager
{
private:
    const string filename ;
    //IniParser parser;

    boost::property_tree::ptree pt;

    static ParameterManager* instance;
    vector<string> groups;
    ParameterManager();
    std::string toLower(std::string str)
    {
        std::string out;
        std::locale loc;
        for (unsigned int i=0; i<str.length(); ++i)
            out += std::tolower(str[i],loc);
       // std::cout << out << std::endl;
        return out;
    }
public :
    static ParameterManager *getInstance();
    void beginGroup(string group);
    void endGroup();
    template <typename T> T get ( std::string key) {
        string global_key;
        for(int i = 0 ; i < groups.size() ;  i++)
            global_key+=toLower(groups[i])+".";
        global_key+=toLower(key);
        return pt.get<T>(global_key);
    }

};

#endif // PARAMETERMANAGER_H
