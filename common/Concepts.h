/*
 * Color.h
 *
 *  Created on: Aug 14, 2013
 *      Author: mostafa
 */

#ifndef __CONCEPTS
#define __CONCEPTS

namespace SSL{
    enum Color {Yellow = 0, Blue = 1};
    enum Side {Left = -1, Right = 1};
}


struct id_color{
    SSL::Color color;
    unsigned int id;

    bool operator==(const id_color& other){
        return ((this->id==other.id) && (int) this->color == (int) other.color);
    }

    bool operator>(const id_color& other){
        if(this->color>other.color)
            return true;
        else if(this->color<other.color)
            return false;
        return ((int) this->id> (int) other.id);
    }
};

#endif // __CONCEPTS
