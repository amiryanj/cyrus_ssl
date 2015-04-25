/*
 * SSLReferee.h
 *
 *  Created on: Aug 16, 2013
 *      Author: mostafa
 */

#ifndef SSLREFEREE_H_
#define SSLREFEREE_H_

#include "../../shared/proto/referee/cpp/referee.pb.h"
#include "../../shared/tools/socket/netraw.h"
#include "../../shared/tools/socket/ippacket.h"
#include "../../shared/tools/ssllistener.h"
//#include <QtNetwork/QUdpSocket>

using namespace Net;

class SSLReferee : public SSLListener
{
    friend class TestReferee;
private:
    IPPacket m_temp_packet;
    void updateState();

public:    
    enum RefereeState{ Unknown, Halt, Stop, ForceStart,
                       BlueKickOffPosition, YellowKickOffPosition,
                       BlueKickOffKick,     YellowKickOffKick,
                       BluePenaltyPosition, YellowPenaltyPosition,
                       BluePenaltyKick,     YellowPenaltyKick,
                       BlueDirectKick,      YellowDirectKick,
                       BlueIndirectKick,    YellowIndirectKick
                     } lastState;

    SSLReferee(int port, string address);
	virtual ~SSLReferee();
    void check();
    UDP simple_socket;
//    QUdpSocket qudp_socket;

    long packet_time_stamp;

    SSL_Referee_Stage stage;
    long stage_time_left;

    SSL_Referee_Command previous_command;
    SSL_Referee_Command last_command;
    long command_counter;
    long command_timestamp;

    SSL_Referee_TeamInfo yellow_info;
    SSL_Referee_TeamInfo blue_info;


};

#endif /* SSLREFEREE_H_ */
