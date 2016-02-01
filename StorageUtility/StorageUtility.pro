#-------------------------------------------------
#
# Project created by QtCreator 2015-11-08T09:32:57
#
#-------------------------------------------------

TARGET = StorageUtility
TEMPLATE = lib
CONFIG += staticlib
QMAKE_CXXFLAGS += -std=c++14

SOURCES += Scsi.cpp \
    Linux/StorageUtility.cpp \
    Linux/Device.cpp \
    Ata.cpp

HEADERS += Scsi.h \
    Ata.h \
    Linux/StorageUtility.h \
    Linux/Device.h

INCLUDEPATH += "../Common" "../Common/Platform/x86x64" "../Common/Platform/x86x64/Linux" "../vtStor/Platform/Linux" "../StorageUtility/Linux" "../Extern"

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

CONFIG(debug, debug|release) {
    DESTDIR = ../Build_StorageUtility/Debug
    OBJECTS_DIR = ../Build_StorageUtility/Debug
}

CONFIG(release, debug|release) {
    DESTDIR = ../Build_StorageUtility/Release
    OBJECTS_DIR = ../Build_StorageUtility/Release
}

LIBS += -ludev