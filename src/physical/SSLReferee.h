/*
 * SSLReferee.h
 *
 *  Created on: Aug 16, 2013
 *      Author: mostafa
 */

#ifndef SSLREFEREE_H_
#define SSLREFEREE_H_

#include "../thirdparty/referee/cpp/referee.pb.h"
#include "../tools/MulticastListener.h"

class SSLReferee : public MulticastListener{
private:
	SSL_Referee referee;
public:
	SSLReferee(string address, int port);
	virtual ~SSLReferee();
	void parse(IPPacket &packet);
	void updateWorldModel(void* data);
};

#endif /* SSLREFEREE_H_ */
