#ifndef STDLIST_H
#define STDLIST_H

#include <vector>

template<typename T>
class STDVector : public std::vector<T>
{
public:
    STDVector(){}

    inline void insertAt(int at, const T& t)
    {
        insert(this->begin() + at, t);
    }

    inline void append(const T& t)
    {
        this->push_back(t);
    }

    inline void prepend(const T &t)
    {
        this->insertAt(0, t);
    }

    T& removeLast()
    {
        T& _last = this->back();
        if(this->size()>0)
            this->pop_back();
        return _last;
    }

    inline int count() const
    {
        return this->size();
    }

protected:


};

#endif // STDLIST_H
