#include "xbeeprotocol.h"
#include "vector"
#include "math.h"
XBeeProtocol::XBeeProtocol()
{
}
char* XBeeProtocol::MakePacket(int input[])
{
    char *output = new char[10];
    output[0] = (char)'*';
    output[1] = 0;
    unsigned char mask = (unsigned char)128;
    for (int i = 0; i < 7; i++)
    {
        if (input[i] > 0 && i < 4)
        {
            output[1] += mask;

        }
        mask >>= 1;
        output[i + 2] = (char)abs(input[i]);
    }
    output[9] = (char)'^';
    return output;

}
