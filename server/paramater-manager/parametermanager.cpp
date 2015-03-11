#include "parametermanager.h"
#include <string>
#include <locale>
using namespace std;

ParameterManager* ParameterManager::instance = NULL;
ParameterManager::ParameterManager()
{
    read_xml(filename, pt);
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
