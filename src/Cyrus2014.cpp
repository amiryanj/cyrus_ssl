//============================================================================
// Name        : Cyrus2014.cpp
// Author      : Cyrus AI Department
// Version     :
// Copyright   : copyright(c) 2010-2014 by Cyrus Team, all rights reserved.
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "general.h"
#include "physical/RobotSerialConnection.h"
#include "physical/SSLVision.h"
#include "physical/SSLReferee.h"
#include <exception>
using namespace std;

int main() {
	try{
		std::cout << "Cyrus 2014 Application Main function Launched." << std::endl;
		//test of serial connection
		RobotSerialConnection conn(__SERIAL_PORT,__SERIAL_BAUD);
		SSLRobotPacket packet;
		conn.sendRobotData(1,packet);
		//end of serial connection test
		SSLVision vision(__SSL_VISION_ADDRESS,__SSL_VISION_PORT);
		SSLReferee referee(__SSL_REFEREE_ADDRESS, __SSL_REFEREE_PORT);
		std::cout << "End of Application"<< std::endl;
	} catch (exception& e) {
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}
