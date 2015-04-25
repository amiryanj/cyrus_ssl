#ifndef _SSLNAMESPACE_H
#define _SSLNAMESPACE_H

#include "utility/vector3d.h"

namespace SSL {

    typedef double time_sec;
    typedef double time_msec;

    typedef double pose_meter;
    typedef double pose_mmeter;

    typedef Vector3D point3D;


    enum Color {Yellow = 0, Blue = 1};
    enum Side {Left = -1, Right = 1};

    struct SSLObjectState {
        Vector3D acc;
        Vector3D vel;
        Vector3D pos;
    };

    struct id_color{
        SSL::Color color;
        unsigned int id;

        bool operator==(const id_color& other)
            { return ((this->id==other.id) && (int) this->color == (int) other.color); }

        bool operator>(const id_color& other){
            if(this->color>other.color)
                return true;
            else if(this->color<other.color)
                return false;
            return ((int) this->id> (int) other.id);
        }
    };

}

#endif // SSLNAMESPACE_H
