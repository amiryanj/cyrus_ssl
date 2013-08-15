//============================================================================
// Name        : Cyrus2014.cpp
// Author      : Cyrus AI Department
// Version     :
// Copyright   : copyright(c) 2010-2014 by Cyrus Team, all rights reserved.
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "general.h"
#include "physical/SerialConnection.h"
#include "physical/SSLVision.h"

int main() {
	std::cout << "Cyrus 2014 Application Main function Launched." << std::endl;
	//test of serial connection
	SerialConnection conn(__SERIAL_PORT,__SERIAL_BAUD);
	SSLRobotPacket packet;
	conn.sendRobotData(1,packet);
	//end of serial connection test
	SSLVision vision;
	std::cout << "End of Application"<< std::endl;
}
