/*
 * SSLListener.h
 *
 *  Created on: Aug 16, 2013
 *      Author: mostafa
 */

#ifndef _SSLLISTENER_H_
#define _SSLLISTENER_H_

class SSLListener {
public:
    virtual void check() = 0;
    virtual ~SSLListener() {}

protected:


};

#endif /* _SSLLISTENER_H_ */
