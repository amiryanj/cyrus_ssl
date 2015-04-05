#ifndef _LOGGER_H
#define _LOGGER_H

#include <iostream>
#include <string>
#include <vector>
#include <boost/signals2/mutex.hpp>
#include <locale>
#include <sstream>
#include <iostream>
#include <map>
#include <fstream>


class Logger
{
    boost::signals2::mutex mtx_;
    static Logger* instance;
    static const std::string path;
    std::map < int , std::ofstream* > files;
    Logger();
    ~Logger();

public:
    static Logger* getInstance();
    std::ofstream &operator[](int i);

};

#endif // LOGGER_H
