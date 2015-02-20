#ifndef INIPARSER_H
#define INIPARSER_H
#include <string>
#include <map>
#include <locale>
#include <sstream>
#include <iostream>
class IniParser
{

public:    
    IniParser();
    IniParser(std::string file);
    bool readFile(std::string file);
    bool readFile();
    bool writeFile(std::string file);
    bool writeFile();
    template <typename T> void setValue (std::string key ,  T value )
    {
        std::ostringstream ss;
        ss << value;
        data[toLower(key)]=ss.str();
    }



    template <typename T> T getValue ( std::string key , bool * isOk )
    {
        T result;
        if(isOk != NULL)
            *isOk = true;
        if(data.find(toLower(key)) == data.end())
        {
            if(isOk != NULL)
                *isOk = false;
            return result;
        }
            //std::cerr << key << std::endl;
        std::istringstream ss(data[toLower(key)]);
        ss >> result;
        return result;
    }

private:
    std::map< std::string , std::string > data;
    std::string file;
    std::string toLower(std::string str)
    {
        std::string out;
        std::locale loc;
        for (unsigned int i=0; i<str.length(); ++i)
            out += std::tolower(str[i],loc);
       // std::cout << out << std::endl;
        return out;
    }

};

#endif // INIPARSER_H
