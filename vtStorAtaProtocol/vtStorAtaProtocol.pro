#-------------------------------------------------
#
# Project created by QtCreator 2015-11-08T16:48:07
#
#-------------------------------------------------

TARGET = vtStorAtaProtocol
TEMPLATE = lib
QMAKE_CXXFLAGS += -std=c++14
QMAKE_CXXFLAGS += -fpermissive

DEFINES += VTSTORATAPROTOCOL_LIBRARY

SOURCES += \
    AtaProtocolEssense1.cpp \
    Platform/Linux/ProtocolAtaPassThrough.cpp

HEADERS += \
    AtaProtocolEssense1.h \
    Platform/Linux/ProtocolAtaPassThrough.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE701A033
    TARGET.CAPABILITY =
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = vtStorAtaProtocol.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

INCLUDEPATH += "../Extern" "../vtStorAtaProtocol/Platform/Linux" "../Common" "../Common/Platform/x86x64" "../Common/Platform/x86x64/Linux" "../StorageUtility" "../StorageUtility/Linux" "../vtStor" "../vtStor/Platform/Linux"


CONFIG(release, debug|release) {

    DESTDIR = ../Build_vtStorAtaProtocol/Release
    OBJECTS_DIR = ../Build_vtStorAtaProtocol/Release

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_StorageUtility/Release/ -lStorageUtility

    INCLUDEPATH += $$PWD/../Build_StorageUtility/Release
    DEPENDPATH += $$PWD/../Build_StorageUtility/Release

    unix:!macx:!symbian: PRE_TARGETDEPS += $$PWD/../Build_StorageUtility/Release/libStorageUtility.a

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_vtStor/Release/ -lvtStor

    INCLUDEPATH += $$PWD/../Build_vtStor/Release
    DEPENDPATH += $$PWD/../Build_vtStor/Release
}

CONFIG(debug, debug|release) {

    DESTDIR = ../Build_vtStorAtaProtocol/Debug
    OBJECTS_DIR = ../Build_vtStorAtaProtocol/Debug

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_StorageUtility/Debug/ -lStorageUtility

    INCLUDEPATH += $$PWD/../Build_StorageUtility/Debug
    DEPENDPATH += $$PWD/../Build_StorageUtility/Debug

    unix:!macx:!symbian: PRE_TARGETDEPS += $$PWD/../Build_StorageUtility/Debug/libStorageUtility.a

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_vtStor/Debug/ -lvtStor

    INCLUDEPATH += $$PWD/../Build_vtStor/Debug
    DEPENDPATH += $$PWD/../Build_vtStor/Debug
}