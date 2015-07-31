//========================================================================
//  This software is free: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License Version 3,
//  as published by the Free Software Foundation.
//
//  This software is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  Version 3 in the file COPYING that came with this distribution.
//  If not, see <http://www.gnu.org/licenses/>.
//========================================================================
/*!
  \file    VarShortVal.h
  \brief   C++ Interface: VarShortVal
  \author  Javad Amiryan, (C) 2015
*/

#ifndef VSHORTVAL_H_
#define VSHORTVAL_H_
#include "VarVal.h"

namespace VarTypes {
  /*!
    \class  VarShortVal
    \brief  A Vartype for storing short integers
    \author Javad Amiryan, (C) 2015
    \see    VarTypes.h

    If you don't know what VarTypes are, please see \c VarTypes.h
  */

  class VarShortVal : virtual public VarVal
  {
  protected:

    short _val;

  public:

    /// set the value of this node to val.
    virtual bool setShort(short val)
    {
      lock();
      if (_val!=val) {
        _val=val;
        unlock();
        changed();
        return true;
      }
      unlock();
      return false;
    };

    VarShortVal(short default_val=0) : VarVal()
    {
      setShort(default_val);
      changed();
    }

    virtual ~VarShortVal() {}

    virtual void printdebug() const
    {
      lock();
      printf("%d\n",_val);
      unlock();
    }

    virtual VarVal * clone() const {
      VarShortVal * tmp = new VarShortVal();
      tmp->setShort(getShort());
      return tmp;
    }


    virtual VarTypeId getType() const { return VARTYPE_ID_INT; };

    virtual string getString() const
    {
      char result[255];
      result[0]=0;
      sprintf(result,"%d",getShort());
      return result;
    };

    virtual short    getShort()    const{ short res; lock(); res=_val; unlock(); return res; };
    virtual double getDouble() const { return (double)getShort(); };
    virtual short   get() const { return getShort(); };

    virtual bool   getBool()  const { return (getShort() == 1 ? true : false); };

    virtual bool setString(const string & val) { int num=0; sscanf(val.c_str(),"%d",&num); return setShort(num); };
    virtual bool setDouble(double val) { return setShort((short)val);  };
    virtual bool setBool(bool val)     { return setShort(val ? true : false);  };

    //plotting functions:
    virtual bool hasValue() const { return true; }
    virtual bool hasMaxValue() const { return false; }
    virtual bool hasMinValue() const { return false; }
    virtual double getMinValue() const { return 0; }
    virtual double getMaxValue() const  { return 1; }
    virtual double getValue() const { return getDouble(); }

  };
};


#endif // VSHORTVAL_H_
