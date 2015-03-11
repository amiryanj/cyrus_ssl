#include "parametermanager.h"
#include <string>
#include <locale>

const string ParameterManager::filename = "Setting.json";

ParameterManager* ParameterManager::instance = NULL;

ParameterManager::ParameterManager()
{
    mtx_.lock();
    read_json(filename, pt);
    mtx_.unlock();
}

ParameterManager *ParameterManager::getInstance()
{
    if(instance == NULL)
        instance = new ParameterManager();
    return instance;
}

void ParameterManager::beginGroup(string group)
{
    groups.push_back(group);
}

void ParameterManager::endGroup()
{

    groups.pop_back();
}
