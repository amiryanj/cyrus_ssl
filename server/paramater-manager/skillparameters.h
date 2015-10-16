#ifndef SKILLPARAMETERS_H
#define SKILLPARAMETERS_H

#include "../vartypes/VarTypesBase.h"

using namespace VarTypes;


// singleton class using vartypes
class SkillParameters : public VarTypesBase
{
    SkillParameters();
    static SkillParameters* instance;
public:
    static SkillParameters* getInstance();

    VarInt* int_var_test;
    VarDouble* double_var_test;
};

#endif // SKILLPARAMETERS_H
