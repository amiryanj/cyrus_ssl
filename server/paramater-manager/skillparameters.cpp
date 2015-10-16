#include "skillparameters.h"

SkillParameters* SkillParameters::instance = NULL;

SkillParameters::SkillParameters()
{
    int_var_test = new VarInt("Int Var Test", 0, 0, 1000);
    double_var_test = new VarDouble("Double Var Test", 0., 0, 1.);

    VarListPtr parameterList(new VarList("Skill Parameters"));
    parameterList->addChild(VarIntPtr(int_var_test));
    parameterList->addChild(VarDoublePtr(double_var_test));

    m_world.push_back(parameterList);
    setSettingsFile("../../cyrus2014/settings/skillparameters.xml");
    load();
}

SkillParameters *SkillParameters::getInstance()
{
    if(instance == NULL)
        instance = new SkillParameters;
    return instance;
}
