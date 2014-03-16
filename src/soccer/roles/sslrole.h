#ifndef SSLROLE_H
#define SSLROLE_H

class SSLAgent;


class SSLRole
{
public:
    enum Type{KeepGoal, Block, Defender, Position, PlayMaker, Active, WaitPass, Support, Press, Stop};

    SSLRole();
    virtual void run() = 0;

    Type m_type;
    SSLAgent* m_agent;

private:
};

#endif // SSLROLE_H
