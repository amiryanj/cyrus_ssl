#include "skillparameters.h"

SkillParameters* SkillParameters::instance = NULL;

SkillParameters::SkillParameters()
{
    int_var_test = new VarInt("Int Var Test", 0, 0, 1000);
    double_var_test = new VarDouble("Double Var Test", 0., 0, 1.);

    mParameterList->addChild(VarIntPtr(int_var_test));
    mParameterList->addChild(VarDoublePtr(double_var_test));

    this->setParameterListName("Skill Parameters");
    this->loadSettings("../../cyrus2014/settings/skillparameters.xml");
}

SkillParameters *SkillParameters::getInstance()
{
    if(instance == NULL)
        instance = new SkillParameters;
    return instance;
}
