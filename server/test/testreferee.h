#ifndef _TESTREFEREE_H
#define _TESTREFEREE_H

#include "../../shared/tools/ssllistener.h"

class TestReferee : public SSLListener
{
public:
    TestReferee();

    void check();

};

#endif // _TESTREFEREE_H
