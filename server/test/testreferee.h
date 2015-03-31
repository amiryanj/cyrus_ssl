#ifndef _TESTREFEREE_H
#define _TESTREFEREE_H

#include "../../common/tools/SSLListener.h"

class TestReferee : public SSLListener
{
public:
    TestReferee();

    void check();

};

#endif // _TESTREFEREE_H
