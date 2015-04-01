#include <iostream>
#include <string>
#include <vector>
#include <boost/signals2/mutex.hpp>
#include <locale>
#include <sstream>
#include <iostream>
#include <map>
#include <fstream>

#ifndef LOGGER_H
#define LOGGER_H

class logger
{
    boost::signals2::mutex mtx_;
    static logger* instance;
    static const std::string path;
    std::map < int , std::ofstream* > files;
    logger();
    ~logger();
public:
    static logger* getInstance();
    std::ofstream &operator[](int i);

};

#endif // LOGGER_H
