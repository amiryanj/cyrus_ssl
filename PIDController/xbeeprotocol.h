#ifndef XBEEPROTOCOL_H
#define XBEEPROTOCOL_H
#include <vector>
class XBeeProtocol
{
public:
    XBeeProtocol();
    const int PacketSize = 9;
    //Queue<byte> IncomingQueue= new Queue<byte>();
    bool isMakingPacket = false;
   // int packet[] = new int[PacketSize];
    //int Packet[];
    int packetIndex = 0;
    char* MakePacket(int input[]);
};

#endif // XBEEPROTOCOL_H
