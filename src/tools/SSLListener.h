/*
 * SSLListener.h
 *
 *  Created on: Aug 16, 2013
 *      Author: mostafa
 */

#ifndef SSLLISTENER_H_
#define SSLLISTENER_H_

class SSLListener {
public:
    virtual void check() = 0;
	virtual ~SSLListener();

protected:


};

#endif /* SSLLISTENER_H_ */
