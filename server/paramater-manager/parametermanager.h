#ifndef PARAMETERMANAGER_H
#define PARAMETERMANAGER_H
#include <iostream>
#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/signals2/mutex.hpp>
#include <locale>
#include <sstream>
#include <iostream>


using namespace std;
class ParameterManager
{
private:
    static const string filename;
    //IniParser parser;
    boost::signals2::mutex mtx_;
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
