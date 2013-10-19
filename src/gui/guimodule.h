#ifndef GUIMODULE_H
#define GUIMODULE_H

#include "general.h"
#include "tools/SSLListener.h"
#include "ai/SSLWorldModel.h"

class GuiModule : public SSLListener
{
public:
    GuiModule();
    void check();

private:
    SSLWorldModel *world;
};

#endif // GUIMODULE_H
