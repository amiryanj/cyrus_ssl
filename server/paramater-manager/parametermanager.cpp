#include "parametermanager.h"
#include <string>
#include <locale>
using namespace std;

ParameterManager::ParameterManager()
{
    read_json(filename, pt);

}
ParameterManager* ParameterManager::instance = NULL;
const string ParameterManager::filename = "Setting.json";
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
