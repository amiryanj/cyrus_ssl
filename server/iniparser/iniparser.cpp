#include "iniparser.h"
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
IniParser::IniParser()
{
}

IniParser::IniParser(std::string file)
{
   //std::cout << file<< std::endl;
    this->file=file;
    readFile();
}

bool IniParser::readFile(std::string file)
{
    std::ifstream fin(file.c_str());
    if(!fin.is_open())
        return false;
    std::string key , value , tmp;
    while(!fin.eof())
    {
        fin >> key >> tmp >> value;
        //std::cout << key << tmp << value<<std::endl;
        data[toLower(key)] = value;
    }
    fin.close();
    return true;
}

bool IniParser::writeFile(std::string file)
{
    std::ofstream fout(file.c_str());
    if(!fout.is_open())
        return false;
    for(std::map<std::string , std::string >::iterator it = data.begin() ; it != data.end() ; ++it)
    {
        fout << it->first << " = " << it->second << std::endl;
    }
    fout.close();
    return true;
}

bool IniParser::readFile()
{
    return readFile(file);

}

bool IniParser::writeFile()
{
    return writeFile(file);

}

/*template <typename T> void IniParser::setValue(std::string key, T value)
{
    std::ostringstream ss;
    ss << value;
    data[key]=ss.str();
}*/


/*template<typename T> T IniParser::getValue(std::string key)
{
    if(data.find(key) != data.end())
        throw "No Such Key";
    std::istringstream ss(data[key]);
    T result;
    if(!(ss >> result))
        result = 0;
    return result;
}*/
