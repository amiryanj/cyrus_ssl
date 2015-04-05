#include "logger.h"
#include <map>
#include <string>
#include <fstream>
#include <cstdio>
const std::string Logger::path = "../../logs/";Logger* Logger::instance = NULL;
Logger::Logger()
{
}

Logger::~Logger()
{
    for(std::map<int , std::ofstream* >::iterator it = files.begin() ; it != files.end() ; ++it)
    {
        (*(it->second)).close();
    }
}

Logger *Logger::getInstance()
{
    if(instance == NULL)
    {
        instance = new Logger;
//        return new logger;
    }
    return instance;

}

std::ofstream &Logger::operator[](int i)
{
    mtx_.lock();
    if(files.find(i) == files.end())
    {
        char s[100];
        std::sprintf(s,"%s%d.log",path.c_str(),i);

        files[i]=new std::ofstream(s);
    }
    mtx_.unlock();
    return *files[i];
}
