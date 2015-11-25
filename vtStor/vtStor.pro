#-------------------------------------------------
#
# Project created by QtCreator 2015-11-08T09:43:59
#
#-------------------------------------------------

TARGET = vtStor
TEMPLATE = lib

DEFINES += VTSTOR_LIBRARY
QMAKE_CXXFLAGS += -std=c++14
QMAKE_CXXFLAGS += -fpermissive
SOURCES += \
    vtStor.cpp \
    ProtocolInterface.cpp \
    ProtocolEssense.cpp \
    DriveManagerInterface.cpp \
    DriveManager.cpp \
    DriveInterface.cpp \
    DriveEnumeratorInterface.cpp \
    Drive.cpp \
    CommandHandlerInterface.cpp \
    CommandDescriptor.cpp \
    BufferInterface.cpp \
    BufferFormatter.cpp \
    Buffer.cpp

HEADERS += \
    vtStor.h \
    ProtocolInterface.h \
    ProtocolEssense.h \
    DriveManagerInterface.h \
    DriveManager.h \
    DriveInterface.h \
    DriveEnumeratorInterface.h \
    Drive.h \
    CommandHandlerInterface.h \
    CommandDescriptor.h \
    BufferInterface.h \
    BufferFormatter.h \
    Buffer.h \
    Platform/Linux/vtStorPlatformDefines.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE342FE1B
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = vtStor.dll
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

    INCLUDEPATH += "../../StorageUtility/Linux" "../../Common" "../../Common/Platform/x86x64" "../../Common/Platform/x86x64/Linux" "../../vtStor/Platform/Linux" "../../StorageUtility"

    INCLUDEPATH += $$PWD/
    DEPENDPATH += $$PWD/

CONFIG(release, debug|release) {

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_StorageUtility/Release/ -lStorageUtility

    INCLUDEPATH += $$PWD/../Build_StorageUtility/Release
    DEPENDPATH += $$PWD/../Build_StorageUtility/Release

    unix:!macx:!symbian: PRE_TARGETDEPS += $$PWD/../Build_StorageUtility/Release/libStorageUtility.a
}

CONFIG(debug, debug|release) {

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_StorageUtility/Debug/ -lStorageUtility

    INCLUDEPATH += $$PWD/../Build_StorageUtility/Debug
    DEPENDPATH += $$PWD/../Build_StorageUtility/Debug

    unix:!macx:!symbian: PRE_TARGETDEPS += $$PWD/../Build_StorageUtility/Debug/libStorageUtility.a
}