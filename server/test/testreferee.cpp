#include "testreferee.h"
#include "../paramater-manager/parametermanager.h"
#include "../referee/SSLReferee.h"
#include "../../common/protoc/referee/cpp/referee.pb.h"
#include "../ai/SSLWorldModel.h"
#include <string>

TestReferee::TestReferee()
{
}

void TestReferee::check()
{
    ParameterManager* pm = ParameterManager::getInstance();
    string command_str = pm->get<string>("referee_test.command");
    SSLReferee::RefereeState state_;

//      Unknown, Halt, Stop, ForceStart,
//       BlueKickOffPosition, YellowKickOffPosition,
//       BlueKickOffKick,     YellowKickOffKick,
//       BluePenaltyPosition, YellowPenaltyPosition,
//       BluePenaltyKick,     YellowPenaltyKick,
//       BlueDirectKick,      YellowDirectKick,
//       BlueIndirectKick,    YellowIndirectKick

    if(command_str.find("halt") != -1 )
        state_ =  SSLReferee::Halt;

    else if(command_str.find("stop") != -1 )
        state_ =  SSLReferee::Stop;

    else if(command_str.find("force") != -1 )
        state_ =  SSLReferee::ForceStart;

    else if( (command_str.find("blue") != -1 )
             && (command_str.find("kickoff") != -1)
             && (command_str.find("position") != -1) )
        state_ =  SSLReferee::BlueKickOffPosition;

    else if( (command_str.find("yellow") != -1 )
             && (command_str.find("kickoff") != -1)
             && (command_str.find("position") != -1) )
        state_ =  SSLReferee::YellowKickOffPosition;

    else if( (command_str.find("blue") != -1 )
             && (command_str.find("kickoff") != -1)
             && (command_str.find("kick") != -1) )
        state_ =  SSLReferee::BlueKickOffKick;

    else if( (command_str.find("yellow") != -1 )
             && (command_str.find("kickoff") != -1)
             && (command_str.find("kcik") != -1) )
        state_ =  SSLReferee::YellowKickOffKick;

    else if( (command_str.find("blue") != -1 )
             && (command_str.find("indirect") != -1) )
        state_ =  SSLReferee::BlueIndirectKick;

    else if( (command_str.find("yellow") != -1 )
             && (command_str.find("indirect") != -1) )
        state_ =  SSLReferee::YellowIndirectKick;

    else if( (command_str.find("blue") != -1 )
             && (command_str.find("direct") != -1) )
        state_ =  SSLReferee::BlueDirectKick;

    else if( (command_str.find("yellow") != -1 )
             && (command_str.find("direct") != -1) )
        state_ =  SSLReferee::YellowDirectKick;

    else if( (command_str.find("blue") != -1 )
             && (command_str.find("penalty") != -1)
             && (command_str.find("position") != -1) )
        state_ =  SSLReferee::BluePenaltyPosition;

    else if( (command_str.find("yellow") != -1 )
             && (command_str.find("penalty") != -1)
             && (command_str.find("position") != -1) )
        state_ =  SSLReferee::YellowPenaltyPosition;

    else if( (command_str.find("blue") != -1 )
             && (command_str.find("penalty") != -1)
             && (command_str.find("kick") != -1) )
        state_ =  SSLReferee::BluePenaltyKick;

    else if( (command_str.find("yellow") != -1 )
             && (command_str.find("penalty") != -1)
             && (command_str.find("kick") != -1) )
        state_ =  SSLReferee::YellowPenaltyKick;

    else  // NULL
        return;

    SSLWorldModel::getInstance()->m_refereeState = state_;
}
