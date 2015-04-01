#include "parametermanager.h"
#include <boost/filesystem.hpp>
using namespace boost::filesystem;
const string ParameterManager::path = "../../cyrus2014/settings";

ParameterManager* ParameterManager::instance = NULL;

ParameterManager::ParameterManager()
{

    mtx_.lock();
    boost::property_tree::ptree temp;


    directory_iterator end_itr;
    for ( directory_iterator itr( path );
            itr != end_itr;
            ++itr )
    {
        if ( !is_directory(itr->status()) )
        {
         //   read_json(itr->path().string(), temp);
            string filename = itr->path().leaf().string();
            if(filename.find("json") == -1) {
                continue;
            }
            string justname = filename.substr(0,filename.size()-5);
            read_json(itr->path().string(),pts[justname]);
            //cout << justname << endl;
        }

    }
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
