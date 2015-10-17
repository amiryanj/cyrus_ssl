QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += VDATA_NO_THREAD_SAFETY
DEFINES += VARTYPES_EXPORT

INCLUDEPATH += $$$PWD
INCLUDEPATH += $$PWD/vartypes
INCLUDEPATH += $$PWD/vartypes/gui
INCLUDEPATH += $$PWD/vartypes/xml
INCLUDEPATH += $$PWD/vartypes/primitives

SOURCES += \
    $$PWD/vartypes/gui/VarItem.cpp \
    $$PWD/vartypes/gui/VarItemDelegate.cpp \
    $$PWD/vartypes/gui/VarTreeModel.cpp \
    $$PWD/vartypes/gui/VarTreeView.cpp \
    $$PWD/vartypes/gui/VarTreeViewOptions.cpp \
    $$PWD/vartypes/primitives/VarBlob.cpp \
    $$PWD/vartypes/primitives/VarBool.cpp \
    $$PWD/vartypes/primitives/VarBoolVal.cpp \
    $$PWD/vartypes/primitives/VarDouble.cpp \
    $$PWD/vartypes/primitives/VarDoubleVal.cpp \
    $$PWD/vartypes/primitives/VarExternal.cpp \
    $$PWD/vartypes/primitives/VarInt.cpp \
    $$PWD/vartypes/primitives/VarIntVal.cpp \
    $$PWD/vartypes/primitives/VarList.cpp \
    $$PWD/vartypes/primitives/VarProtoBuffer.cpp \
    $$PWD/vartypes/primitives/VarProtoBufferVal.cpp \
    $$PWD/vartypes/primitives/VarQWidget.cpp \
    $$PWD/vartypes/primitives/VarSelection.cpp \
    $$PWD/vartypes/primitives/VarShort.cpp \
    $$PWD/vartypes/primitives/VarShortVal.cpp \
    $$PWD/vartypes/primitives/VarString.cpp \
    $$PWD/vartypes/primitives/VarStringEnum.cpp \
    $$PWD/vartypes/primitives/VarStringVal.cpp \
    $$PWD/vartypes/primitives/VarTrigger.cpp \
    $$PWD/vartypes/primitives/VarType.cpp \
    $$PWD/vartypes/primitives/VarVal.cpp \
    $$PWD/vartypes/xml/xmlParser.cpp \
    $$PWD/vartypes/VarBase64.cpp \
    $$PWD/vartypes/VarNotifier.cpp \
    $$PWD/vartypes/VarTypes.cpp \
    $$PWD/vartypes/VarTypesBase.cpp \
    $$PWD/vartypes/VarTypesFactory.cpp \
    $$PWD/vartypes/VarTypesInstance.cpp \
    $$PWD/vartypes/VarXML.cpp
    

HEADERS += \
    $$PWD/vartypes/gui/VarItem.h \
    $$PWD/vartypes/gui/VarItemDelegate.h \
    $$PWD/vartypes/gui/VarTreeModel.h \
    $$PWD/vartypes/gui/VarTreeView.h \
    $$PWD/vartypes/gui/VarTreeViewOptions.h \
    $$PWD/vartypes/primitives/VarBlob.h \
    $$PWD/vartypes/primitives/VarBool.h \
    $$PWD/vartypes/primitives/VarBoolVal.h \
    $$PWD/vartypes/primitives/VarDouble.h \
    $$PWD/vartypes/primitives/VarDoubleVal.h \
    $$PWD/vartypes/primitives/VarExternal.h \
    $$PWD/vartypes/primitives/VarInt.h \
    $$PWD/vartypes/primitives/VarIntVal.h \
    $$PWD/vartypes/primitives/VarList.h \
    $$PWD/vartypes/primitives/VarProtoBuffer.h \
    $$PWD/vartypes/primitives/VarProtoBufferVal.h \
    $$PWD/vartypes/primitives/VarQWidget.h \
    $$PWD/vartypes/primitives/VarSelection.h \
    $$PWD/vartypes/primitives/VarShort.h \
    $$PWD/vartypes/primitives/VarShortVal.h \
    $$PWD/vartypes/primitives/VarString.h \
    $$PWD/vartypes/primitives/VarStringEnum.h \
    $$PWD/vartypes/primitives/VarStringVal.h \
    $$PWD/vartypes/primitives/VarTrigger.h \
    $$PWD/vartypes/primitives/VarType.h \
    $$PWD/vartypes/primitives/VarVal.h \
    $$PWD/vartypes/xml/xmlParser.h \
    $$PWD/vartypes/DllDefines.h \
    $$PWD/vartypes/VarBase64.h \
    $$PWD/vartypes/VarNotifier.h \
    $$PWD/vartypes/VarTypes.h \
    $$PWD/vartypes/VarTypesBase.h \
    $$PWD/vartypes/VarTypesFactory.h \
    $$PWD/vartypes/VarTypesInstance.h \
    $$PWD/vartypes/VarXML.h


