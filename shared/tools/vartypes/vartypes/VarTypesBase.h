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
  \file    VarTypesBase.h
  \brief   C++ Interface: VarTypesBase
  \author  Javad Amiryan, 2015
*/
//========================================================================

#ifndef VARTYPESBASE_H
#define VARTYPESBASE_H

#define DEBUG_ME

#include "VarTreeModel.h"
#include "VarTypes.h"
#include "VarXML.h"
#include <iostream>

namespace VarTypes {
/*!
  \class  VarTypesBase
  \brief  Base class for using VarTypes
  \author Javad Amiryan, (C) 2015
  \see    VarTypes.h

    This class can be inherited by any class which aims to use
    VarTypes data types and storing them into a .xml setting files.
    If you don't know what VarTypes are, please see \c VarTypes.h
*/
    class VARTYPES_EXPORT VarTypesBase
    {
    public:
        VarTypesBase() { }
        ~VarTypesBase() { save(); }

        VarTreeModel& getParametersTree() {
            return this->m_parameters_tree_model;
        }

        void setSettingsFile(const std::string &_name) {
            m_setting_file = _name;
        }

        void load() {
            m_world = VarXML::read(m_world, m_setting_file);
            m_parameters_tree_model.setRootItems(m_world);
        }

        void save() {
            VarXML::write(m_world, m_setting_file);
          #ifdef DEBUG_ME
            std::cout << "Setting file [" << m_setting_file << "] stored." << std::endl;
          #endif
        }

    protected:
        std::string m_setting_file;
        std::vector<VarPtr> m_world; // our list of toplevel node(s)
        VarTreeModel m_parameters_tree_model;
    };
}

#endif // VARTYPESBASE_H
