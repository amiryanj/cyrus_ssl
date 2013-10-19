#ifndef SSLROLE_H
#define SSLROLE_H

enum ActiveT{Active, NonActive};

class SSLRole
{
public:
//    SSLRole();
    virtual void run() = 0;

    ActiveT activeType;
};

#endif // SSLROLE_H
