/*
 * SSLException.cpp
 *
 *  Created on: Aug 16, 2013
 *      Author: mostafa
 */

#include "SSLException.h"
#include <errno.h>
#include <string.h>

SSLException::SSLException(const string &message, bool inclSysMsg)
	throw() : userMessage(message) {
	if (inclSysMsg) {
	  userMessage.append(": ");
	  userMessage.append(strerror(errno));
	}
}


SSLException::~SSLException() throw(){

}

const char * SSLException::what() const throw() {
  return userMessage.c_str();
}
