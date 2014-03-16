/*
 * File:   AreaPlayMaker.cpp
 * Author: mahdi
 * 
 * Created on February 19, 2014, 1:04 PM
 */

#include "playmakerrole.h"

PlayMakerRole::PlayMakerRole(SSLAgent *agent)
{
    this->m_agent = agent;
    this->m_type = SSLRole::PlayMaker;
}

void PlayMakerRole::run(){
    
}
