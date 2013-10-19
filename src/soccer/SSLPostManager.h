#ifndef SSLPOSTMANAGER_H
#define SSLPOSTMANAGER_H

#include "definition/SSLPost.h"
#include "definition/sslagent.h"
#include "sslstrategymanager.h"

#include "general.h"

class SSLPostManager
{
    SSLPostManager();
    static SSLPostManager* manager;

public:
    static SSLPostManager* getInstance();

    void assignPost(const SSLStrategy &desired_strategy, std::vector<SSLAgent*> agents);

    std::vector<SSLPost> availablePosts;

};

#endif // SSLPOSTMANAGER_H
