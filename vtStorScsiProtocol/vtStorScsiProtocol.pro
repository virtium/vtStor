
#-------------------------------------------------
#
# Project created by QtCreator 2015-12-22T17:30:33
#
#-------------------------------------------------

TARGET = vtStorScsiProtocol
TEMPLATE = lib
QMAKE_CXXFLAGS += -std=c++14
QMAKE_CXXFLAGS += -fpermissive

DEFINES += VTSTORSCSIPROTOCOL_LIBRARY

SOURCES += \
    ScsiProtocolEssense1.cpp \
    Platform/Linux/ProtocolScsiPassThrough.cpp

HEADERS += \
    ScsiProtocolEssense1.h \
    Platform/Linux/ProtocolScsiPassThrough.h

INCLUDEPATH +=  "../Extern" "../vtStorScsiProtocol/Platform/Linux" "../Common" "../Common/Platform/x86x64" "../Common/Platform/x86x64/Linux" "../StorageUtility" "../StorageUtility/Linux" "../vtStor" "../vtStor/Platform/Linux"

CONFIG(debug, debug|release) {

    DESTDIR = ../Build_vtStorScsiProtocol/Debug
    OBJECTS_DIR = ../Build_vtStorScsiProtocol/Debug

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_StorageUtility/Debug/ -lStorageUtility

    INCLUDEPATH += $$PWD/../Build_StorageUtility/Debug
    DEPENDPATH += $$PWD/../Build_StorageUtility/Debug

    unix:!macx:!symbian: PRE_TARGETDEPS += $$PWD/../Build_StorageUtility/Debug/libStorageUtility.a

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_vtStor/Debug/ -lvtStor

    INCLUDEPATH += $$PWD/../Build_vtStor/Debug
    DEPENDPATH += $$PWD/../Build_vtStor/Debug
}

CONFIG(release, debug|release) {

    DESTDIR = ../Build_vtStorScsiProtocol/Release
    OBJECTS_DIR = ../Build_vtStorScsiProtocol/Release

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_StorageUtility/Release/ -lStorageUtility

I   NCLUDEPATH += $$PWD/../Build_StorageUtility/Release
    DEPENDPATH += $$PWD/../Build_StorageUtility/Release

    unix:!macx:!symbian: PRE_TARGETDEPS += $$PWD/../Build_StorageUtility/Release/libStorageUtility.a

     unix:!macx:!symbian: LIBS += -L$$PWD/../Build_vtStor/Release/ -lvtStor

    INCLUDEPATH += $$PWD/../Build_vtStor/Release
    DEPENDPATH += $$PWD/../Build_vtStor/Release

}