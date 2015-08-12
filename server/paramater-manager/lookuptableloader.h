#ifndef LOOKUPTABLELOADER_H
#define LOOKUPTABLELOADER_H

#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

typedef std::pair<double, double> DoublePair;

class LookupTableLoader
{
    std::string file_name;
    std::vector<DoublePair> data;
    double x_0;
    double x_step;
    double x_end;

    double x_scale;
    double y_scale;

public:
    LookupTableLoader();
    void setFileName(std::string n) {
        file_name = n;
    }
    void load();
    void setScale(double x_ = 1, double y_ = 1) ;

    double getValue(double x);
};

#endif // LOOKUPTABLELOADER_H
