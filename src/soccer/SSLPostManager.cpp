#include "SSLPostManager.h"

SSLPostManager* SSLPostManager::manager = NULL;
SSLPostManager::SSLPostManager()
{

}

SSLPostManager *SSLPostManager::getInstance()
{
    if(manager == NULL)
        manager = new SSLPostManager();
    return manager;
}

void SSLPostManager::assignPost(const SSLStrategy &desired_strategy, std::vector<SSLAgent*> agents)
{

    std::list<SSLPost> tst;
    std::vector<SSLPost> post_list = desired_strategy.postList;

    double dist[agents.size()][post_list.size()];

    for(int i =0; i< agents.size(); ++i)
    {
        for(int j = 0; j<post_list.size(); ++j)
        {
            SSLAgent* agent = (agents.at(i));
            if(agent != NULL)
                break;
            SSLPost _p = (post_list.at(j)) ;
            dist[i][j] = Vector2D(_p.centerOfAction - agent->robot->Position().to2D()).lenght();

        }
    }

}
