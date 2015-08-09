#include "lookuptableloader.h"
#include <cstdlib>
#include <iostream>

using namespace std;

LookupTableLoader::LookupTableLoader()
{
    x_scale = 1;
    y_scale = 1;
}

void LookupTableLoader::load()
{
    ifstream in_file;
    in_file.open(file_name.c_str());

    std::string line;
    int index_a = 0;
    DoublePair p;
    while(std::getline(in_file, line))
    {
        std::stringstream  lineStream(line);
        std::string        cell;
        int index_b = 0;
        while(std::getline(lineStream, cell, ','))
        {
            // You have a cell!!!!
            double d = atof(cell.c_str());
            if(index_b == 0)
                p.first = d;
            else
                p.second = d;
            index_b ++;
        }
        data.push_back(p);
        if(index_a == 0)
            x_0 = p.first;
        if(index_a == 1)
            x_step = p.first - x_0;
        index_a ++;
    }
    x_end = p.first;

    // add an extra pair
    p.first = p.first + x_step;
    data.push_back(p);

    for (int i=0; i<data.size(); i++) {
        cout << "[" << i << "]: " << data[i].first << endl;
    }
}

void LookupTableLoader::setScale(double x_, double y_)
{
    x_scale = x_;
    y_scale = y_;
    for (uint i=0; i<data.size(); i++) {
        data[i].first *= x_scale;
        data[i].second *= y_scale;
    }
    x_0 *= x_scale;
    x_step *= x_scale;
    x_end *= x_scale;
}

double LookupTableLoader::getValue(double x)
{
    int index_i = (x-x_0)/x_step;
    if(index_i < 0)
        return 0;
    if(index_i>data.size()-2)
        return 0;
    double x_a = data[index_i].first;
    double x_b = data[index_i+1].first;
    double alpha = (x - x_a) / (x_b - x_a);
    double y = data[index_i].second * (1-alpha) + data[index_i+1].second * alpha;
    return y;
}
