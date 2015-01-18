#include "settingmanager.h"
#include <QtCore>
#include <QString>
void SettingManager::Save(QString fileaddress)
{
    QFile savefile(fileaddress);
    if(!savefile.open(QIODevice::WriteOnly))
    {
        qWarning("Cant Open Save File");
    }
    QJsonObject jobj,jsetting;
    jsetting["Code"]="hello";
    jobj["Setting"]=jsetting;
    QJsonDocument jdoc(jobj);
    savefile.write(jdoc.toJson());
}

SettingManager::SettingManager()
{


}
