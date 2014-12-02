/*
 * SSLException.h
 *
 *  Created on: Aug 16, 2013
 *      Author: mostafa
 */

#ifndef SSLEXCEPTION_H_
#define SSLEXCEPTION_H_

#include <exception>
#include <string>
using namespace std;

class SSLException : public exception{
public:
	 /**
	   *   Construct a SocketException with a explanatory message.
	   *   @param message explanatory message
	   *   @param incSysMsg true if system message (from strerror(errno))
	   *   should be postfixed to the user provided message
	   */
	SSLException(const string &message, bool inclSysMsg = false) throw();
	virtual ~SSLException() throw();

	  /**
	   *   Get the exception message
	   *   @return exception message
	   */
	const char *what() const throw();

private:
	string userMessage;  // Exception message
};

#endif /* SSLEXCEPTION_H_ */
