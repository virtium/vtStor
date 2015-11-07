#-------------------------------------------------
#
# Project created by QtCreator 2015-11-08T09:32:57
#
#-------------------------------------------------

TARGET = StorageUtility
TEMPLATE = lib
CONFIG += staticlib
QMAKE_CXXFLAGS += -std=c++14

LIBS += -ludev

SOURCES += Scsi.cpp \
    DeviceInterface.cpp \
    Ata.cpp \
    Linux/StorageUtility.cpp \
    Linux/Device.cpp

HEADERS += Scsi.h \
    DeviceInterface.h \
    Ata.h \
    Linux/StorageUtility.h \
    Linux/Device.h
INCLUDEPATH += "../Common" ".././Common/Platform/x86x64" "../Common/Platform/x86x64/Linux" "../vtStor/Platform/Linux" "../StorageUtility/Linux"
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}