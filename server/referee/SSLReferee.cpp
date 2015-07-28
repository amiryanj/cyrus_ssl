/*
 * SSLReferee.cpp
 *
 *  Created on: Aug 16, 2013
 *      Author: mostafa
 */

#include "SSLReferee.h"
#include <iostream>
#include "../ai/SSLWorldModel.h"
#include "../definition/SSLBall.h"
#include "paramater-manager/parametermanager.h"

SSLReferee::SSLReferee(int port, string address) : SSLListener()
{
//    qudp_socket.bind(port);

   // simple_socket.open(port, true, true);
    simple_socket.bind(QHostAddress::AnyIPv4, port, QUdpSocket::ShareAddress);
//    Address multi_, interface_;
//    multi_.setHost(address.c_str(), port);
//    interface_.setAny();
//    simple_socket.addMulticast(multi_, interface_);
    simple_socket.joinMulticastGroup(QHostAddress(QString(address.c_str())));
    previous_command = SSL_Referee_Command_HALT;
    last_command = SSL_Referee_Command_HALT;
}

SSLReferee::~SSLReferee()
{
}

void SSLReferee::check()
{

    //    while(qudp_socket.hasPendingDatagrams())

    Address sender_adress;
    while(simple_socket.hasPendingDatagrams())
    {
        m_temp_packet.length = simple_socket.readDatagram(m_temp_packet.buffer, MAX_BUFFER_SIZE);//, sender_adress);
        cout << "Referee-Packet received. Packet Lenght: [" << m_temp_packet.length << "]" << endl;

//        m_temp_packet.length = qudp_socket.pendingDatagramSize();
//        qudp_socket.readDatagram(m_temp_packet.buffer, m_temp_packet.length);
//        m_temp_packet.length = this->recv(m_temp_packet.buffer, MAX_BUFFER_SIZE, sender_adress);

        SSL_Referee_Command new_command;
        if(m_temp_packet.length < 6)
            return;
        if(m_temp_packet.length > 6) {
            SSL_Referee referee_packet;
            referee_packet.Clear();
            referee_packet.ParseFromArray(m_temp_packet.buffer, m_temp_packet.length);
            packet_time_stamp = referee_packet.packet_timestamp();
            if(referee_packet.has_stage()) {
                stage = referee_packet.stage();
                stage_time_left = referee_packet.stage_time_left();
            }
            if(referee_packet.has_command()) {
                new_command = referee_packet.command();
                command_counter = referee_packet.command_counter();
                command_timestamp = referee_packet.command_timestamp();
            }
            if(referee_packet.has_yellow())
                yellow_info = referee_packet.yellow();

            if(referee_packet.has_blue())
                blue_info = referee_packet.blue();
        }

        else {
            switch (m_temp_packet.buffer[0]) {
            case 'H':
                new_command = SSL_Referee_Command_HALT;
                break;
            case 'S':
                new_command = SSL_Referee_Command_STOP;
                break;
            case '\n':
                new_command = SSL_Referee_Command_NORMAL_START;
                break;
            case 's':
                new_command = SSL_Referee_Command_FORCE_START;
                break;
            case 'k':
                new_command = SSL_Referee_Command_PREPARE_KICKOFF_YELLOW;
                break;
            case 'K':
                new_command = SSL_Referee_Command_PREPARE_KICKOFF_BLUE;
                break;
            case 'p':
                new_command = SSL_Referee_Command_PREPARE_PENALTY_YELLOW;
                break;
            case 'P':
                new_command = SSL_Referee_Command_PREPARE_PENALTY_BLUE;
                break;
            case 'i':
                new_command = SSL_Referee_Command_INDIRECT_FREE_YELLOW;
                break;
            case 'I':
                new_command = SSL_Referee_Command_INDIRECT_FREE_BLUE;
                break;
            case 'f':
                new_command = SSL_Referee_Command_DIRECT_FREE_YELLOW;
                break;
            case 'F':
                new_command = SSL_Referee_Command_DIRECT_FREE_BLUE;
                break;
            case 'h':
                stage = SSL_Referee_Stage_NORMAL_HALF_TIME;
                break;
            case '1':
                stage = SSL_Referee_Stage_NORMAL_FIRST_HALF;
                break;
            case '2':
                stage = SSL_Referee_Stage_NORMAL_SECOND_HALF;
                break; // return PlayGameState.Time_SecondHalf;
            case 'o':
                stage = SSL_Referee_Stage_EXTRA_FIRST_HALF;
                break; // return PlayGameState.Time_OverTime1;
            case 'O':
                stage = SSL_Referee_Stage_EXTRA_SECOND_HALF;
                break; // return PlayGameState.Time_OverTime2;
            case 'a':
                stage = SSL_Referee_Stage_PENALTY_SHOOTOUT;
                break; // return PlayGameState.Time_Penalty;
            default:
                 new_command = SSL_Referee_Command_FORCE_START;
                break;
            }
        }

        if(new_command != last_command) {
            previous_command = last_command;
            last_command = new_command;
            updateState();
        }

        cout << "Referee-Packet received. Lenght: [" << this->m_temp_packet.length << "]"
             << " command: "<< new_command << endl;

    }
}

void SSLReferee::updateState()
{
    if(last_command == SSL_Referee_Command_HALT)
        lastState = Halt;
    else if(last_command == SSL_Referee_Command_STOP)
        lastState = Stop;
    else if(last_command == SSL_Referee_Command_FORCE_START)
        lastState = ForceStart;

    else if(last_command == SSL_Referee_Command_PREPARE_KICKOFF_BLUE)
        lastState = BlueKickOffPosition;
    else if(last_command == SSL_Referee_Command_PREPARE_KICKOFF_YELLOW)
        lastState = YellowKickOffPosition;
    else if(last_command == SSL_Referee_Command_PREPARE_PENALTY_BLUE)
        lastState = BluePenaltyPosition;
    else if(last_command == SSL_Referee_Command_PREPARE_PENALTY_YELLOW)
        lastState = YellowPenaltyPosition;

    else if(last_command == SSL_Referee_Command_DIRECT_FREE_BLUE)
        lastState = BlueDirectKick;
    else if(last_command == SSL_Referee_Command_DIRECT_FREE_YELLOW)
        lastState = YellowDirectKick;
    else if(last_command == SSL_Referee_Command_INDIRECT_FREE_BLUE)
        lastState = BlueIndirectKick;
    else if(last_command == SSL_Referee_Command_INDIRECT_FREE_YELLOW)
        lastState = YellowIndirectKick;

    else if (last_command == SSL_Referee_Command_NORMAL_START && previous_command == SSL_Referee_Command_PREPARE_KICKOFF_BLUE)
        lastState = BlueKickOffKick;
    else if (last_command == SSL_Referee_Command_NORMAL_START && previous_command == SSL_Referee_Command_PREPARE_KICKOFF_YELLOW)
        lastState = YellowKickOffKick;
    else if (last_command == SSL_Referee_Command_NORMAL_START && previous_command == SSL_Referee_Command_PREPARE_PENALTY_BLUE)
        lastState = BluePenaltyKick;
    else if (last_command == SSL_Referee_Command_NORMAL_START && previous_command == SSL_Referee_Command_PREPARE_PENALTY_YELLOW)
        lastState = YellowPenaltyKick;

//    else lastState = Unknown; // logically impossible state
    SSLWorldModel::getInstance()->m_refereeState = lastState;
    SSLWorldModel::getInstance()->mainBall()->setStopped(true);

}
