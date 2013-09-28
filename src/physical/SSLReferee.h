/*
 * SSLReferee.h
 *
 *  Created on: Aug 16, 2013
 *      Author: mostafa
 */

#ifndef SSLREFEREE_H_
#define SSLREFEREE_H_

#include "../thirdparty/referee/cpp/referee.pb.h"
#include "thirdparty/socket/netraw.h"
#include "tools/SSLListener.h"
#include "thirdparty/socket/IPPacket.h"

using namespace Net;

class SSLReferee : public SSLListener, public UDP
{
private:
	SSL_Referee referee;
public:
	SSLReferee(string address, int port);
	virtual ~SSLReferee();
	void parse(IPPacket &packet);
    void updateWorldModel();
};

#endif /* SSLREFEREE_H_ */
