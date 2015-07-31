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
  \file    VarShort.cpp
  \brief   C++ Implementation: VarShort
  \author  Javad Amiryan, (C) 2015
*/

#ifndef VSHORT_H_
#define VSHORT_H_
#include "VarType.h"
#include "VarShortVal.h"
#include <QSlider>
// FIXME: remove this include after implementing QSlider
#include <QSpinBox>

namespace VarTypes {
  /*!
    \class  VarShort
    \brief  A Vartype for storing short integers, providing a slider widget
    \author  Javad Amiryan, (C) 2015

    If you don't know what VarTypes are, please see \c VarTypes.h
  */

    class VarShort;
    typedef shared_ptr<VarShort> VarShortPtr;

    class VARTYPES_EXPORT VarShort : public VarTypeTemplate<VarShortVal>
    {
      Q_OBJECT
    protected:

      SafeVarVal<VarShortVal> _def;
      short _min;
      short _max;

    public:
      /// get the minimum accepted value if this data-type has a limited range
      /// \see setMin(...)
      /// \see hasMin()
      /// \see unsetMin()
      virtual short getMin() const { lock(); short v=_min; unlock(); return v; }

      /// get the maximum accepted value if this data-type has a limited range
      /// \see setMax(...)
      /// \see hasMax()
      /// \see unsetMax()
      virtual short getMax() const { lock(); short v=_max; unlock(); return v; }

      /// check whether this data type has a limited minimum value
      /// \see getMin(...)
      /// \see setMin(...)
      /// \see unsetMin()
      virtual bool hasMin() const { lock(); bool v= (_min != SHRT_MIN); unlock(); return v; }

      /// check whether this data type has a limited maximum value
      /// \see getMax(...)
      /// \see setMax(...)
      /// \see unsetMax()
      virtual bool hasMax() const { lock(); bool v= (_max != SHRT_MAX); unlock(); return v; }

      /// limit the minumum value of this parameter to a pre-set value
      /// \see getMin(...)
      /// \see hasMin()
      /// \see unsetMin()
      virtual void setMin(short minval) { lock(); _min=minval; unlock(); changed(); }

      /// limit the maximum value of this parameter to a pre-set value
      /// \see getMax(...)
      /// \see hasMax()
      /// \see unsetMax()
      virtual void setMax(short maxval) { lock(); _max=maxval; unlock(); changed(); }

      /// unset any previous limit of minimum value of this parameter
      /// \see getMin(...)
      /// \see setMin(...)
      /// \see hasMin()
      virtual void unsetMin() { lock(); _min=SHRT_MIN; unlock(); changed(); }

      /// unset any previous limit of maximum value of this parameter
      /// \see getMax(...)
      /// \see setMax(...)
      /// \see hasMax()
      virtual void unsetMax() { lock(); _max=SHRT_MAX; unlock(); changed(); }

      /// set the value of this node to val.
      virtual bool setShort(short val)
      {
        short tmp;
        if (hasMin() && val < getMin()) {
          tmp=_min;
        } else if (hasMax() && val > getMax()) {
          tmp=_max;
        } else {
          tmp=val;
        }
        return VarShortVal::setShort(tmp);
      };

      virtual void setDefault(short val)
      {
        _def.setShort(val);
        changed();
      }

      VarShort(string name="", short default_val=0, short min_val=SHRT_MIN, short max_val=SHRT_MAX) : VarShortVal(default_val), VarTypeTemplate<VarShortVal>(name)
      {
        setMin(min_val);
        setMax(max_val);
        setDefault(default_val);
      }

      virtual ~VarShort() {}

      virtual void resetToDefault()
      {
        setShort(_def.getShort());
      }

      virtual short    getShort()    const{ short res; lock(); res=_val; unlock(); return res; };
      virtual double getDouble() const { return (double)getShort(); };
      virtual short   get() const { return getShort(); };

      virtual bool   getBool()  const { return (getShort() == 1 ? true : false); };

      virtual bool setString(const string & val) { int num=0; sscanf(val.c_str(),"%d",&num); return setShort(num); };
      virtual bool setDouble(double val) { return setShort((short)val);  };
      virtual bool setBool(bool val)     { return setShort(val ? 1 : 0);  };

      //plotting functions:
      virtual bool hasValue() const { return true; }
      virtual bool hasMaxValue() const { return hasMax(); }
      virtual bool hasMinValue() const { return hasMin(); }
      virtual double getMinValue() const { return (double)getMin(); }
      virtual double getMaxValue() const  { return (double)getMax(); }
      virtual double getValue() const { return getDouble(); }


    #ifndef VDATA_NO_XML
    protected:
      virtual void updateAttributes(XMLNode & us) const
      {
        if (hasMin()) {
          us.updateAttribute(intToString(getMin()).c_str(),"minval","minval");
        } else {
          us.updateAttribute("","minval","minval");
        }
        if (hasMax()) {
          us.updateAttribute(intToString(getMax()).c_str(),"maxval","maxval");
        } else {
          us.updateAttribute("","maxval","maxval");
        }
      }

      virtual void readAttributes(XMLNode & us)
      {
        string s = fixString(us.getAttribute("minval"));
        if (s=="") {
          unsetMin();
        } else {
          int num=0; sscanf(s.c_str(),"%d",&num);
          setMin(num);
        }

        s = fixString(us.getAttribute("maxval"));
        if (s=="") {
          unsetMax();
        } else {
          int num=0; sscanf(s.c_str(),"%d",&num);
          setMax(num);
        }
      }

    #endif

      //Qt model/view gui stuff:
      public:
      virtual QWidget * createEditor(const VarItemDelegate * delegate, QWidget *parent, const QStyleOptionViewItem &option) {
        //TODO: hookup editor changes on press-enter and on spin:
        (void)delegate;
        (void)parent;
        (void)option;
        QSlider * w = new QSlider(Qt::Horizontal, parent);
        w->setRange(getMin(), getMax());
        //connect(w,SIGNAL(sliderMoved(int)), (const QObject *)delegate, SLOT(editorChangeEvent()));
        //uncomment the following line for instantaneous updates:
        //connect((const QObject *)w,SIGNAL(valueChanged ( short )),(const QObject *)delegate,SLOT(editorChangeEvent()));
        return w;
      }

      virtual void setEditorData(const VarItemDelegate * delegate, QWidget *editor) const {
        (void)delegate;
        QSlider * slider=(QSlider *) editor;
        slider->setRange(getMin(), getMax());
        slider->setValue(getShort());
      }

      virtual void setModelData(const VarItemDelegate * delegate, QWidget *editor) {
        (void)delegate;
        QSlider * slider =(QSlider *) editor;
        if (setShort(slider->value()) ) mvcEditCompleted();
      }
    };

    typedef shared_ptr<VarShort> VarShortPtr;

}
#endif // VARSHORT_H

