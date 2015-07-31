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
            return this->parameters_tree_model;
        }

        void setSettingsFile(const std::string &_name) {
            setting_file = _name;
        }

        void load() {
            world = VarXML::read(world, setting_file);
            parameters_tree_model.setRootItems(world);
        }

        void save() {
            VarXML::write(world, setting_file);
          #ifdef DEBUG_ME
            std::cout << "Setting file [" << setting_file << "] stored." << std::endl;
          #endif
        }

    protected:
        std::string setting_file;
        std::vector<VarPtr> world; // our list of toplevel node(s)
        VarTreeModel parameters_tree_model;
    };
};

#endif // VARTYPESBASE_H
