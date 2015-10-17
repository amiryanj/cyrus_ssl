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

#include "VarTypes.h"
#include "VarXML.h"
#include "VarTreeModel.h"
#include <iostream>

#define DEBUG_VARTYPES
#ifndef VARTYPES_EXPORT
#define VARTYPES_EXPORT
#endif

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
        VarTypesBase() {
            mSettingFile = "";
            mParameterList = VarListPtr(new VarList);
        }

        ~VarTypesBase() {
            save();
//            delete mParameterList;
        }

        VarTreeModel& getParametersTree() {
            return this->mParametersTreeModel;
        }
        std::string getParameterListName() const {
            return mParameterList->getName();
        }

        void setSettingsFile(const std::string &_name) {
            mSettingFile = _name;
        }
        void setParameterListName(const std::string &_name) {
            mParameterList->setName(_name);
        }

        void loadSettings(const string & setting_file = "") {
            if(!setting_file.empty()) {
                this->mSettingFile = setting_file;
            }
            mWorld.clear();
            mWorld.push_back(mParameterList);
            mWorld = VarXML::read(mWorld, mSettingFile);
            mParametersTreeModel.setRootItems(mWorld);
        }

        void save() {
            if(!mSettingFile.empty()) {
                VarXML::write(mWorld, mSettingFile);
          #ifdef DEBUG_VARTYPES
            std::cout << "Setting file [" << mSettingFile << "] stored." << std::endl;
          #endif
            }
            else {
//                std::cout << "Warning: " << type_info(*this).name() << "Setting file name is empty ..." << std::endl;
            }
        }

    protected:
        std::string mSettingFile;
        std::vector<VarPtr> mWorld; // our list of toplevel node(s)
        VarTreeModel mParametersTreeModel;
        VarListPtr mParameterList;
    };
};

#endif // VARTYPESBASE_H
