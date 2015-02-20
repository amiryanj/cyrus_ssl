#include "parametermanager.h"
#include <string>
#include <locale>
using namespace std;

ParameterManager::ParameterManager()
{
    parser.readFile(file);
}
ParameterManager* ParameterManager::instance = NULL;
const string ParameterManager::file = "Setting.ini";
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
