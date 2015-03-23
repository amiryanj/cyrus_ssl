#include "parametermanager.h"

const string ParameterManager::filename = "../../cyrus2014/cyrus_settings.json";

ParameterManager* ParameterManager::instance = NULL;

ParameterManager::ParameterManager()
{
    mtx_.lock();
    read_json(filename, pt);
    mtx_.unlock();
}

ParameterManager *ParameterManager::getInstance()
{
    if(instance == NULL) {
        cout << "Parameter Manager initiated" <<endl;
        instance = new ParameterManager();
    }
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
