#-------------------------------------------------
#
# Project created by QtCreator 2015-11-08T18:00:23
#
#-------------------------------------------------

TARGET = vtStorAta
TEMPLATE = lib
QMAKE_CXXFLAGS += -std=c++14
DEFINES += VTSTORATA_LIBRARY
QMAKE_CXXFLAGS += -fpermissive

SOURCES += DriveEnumeratorAta.cpp \
    DriveAtaCommandExtensions.cpp \
    DriveAta.cpp \
    CommandHandlerAta.cpp \
    CommandDescriptorAta.cpp \
    vtStorAta.cpp

HEADERS +=  vtStorAta.h \
    DriveEnumeratorAta.h \
    DriveAtaCommandExtensions.h \
    DriveAta.h \
    CommandHandlerAta.h \
    CommandDescriptorAta.h \
    Platform/Linux/vtStorAtaPlatformDefines.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE5F0BAEB
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = vtStorAta.dll
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

INCLUDEPATH += "../../vtStorAtaProtocol" "../../vtStorAtaProtocol/Platform/Linux" "../../vtStorAta/Platform/Linux" "../../Common" "../../Common/Platform/x86x64" "../../Common/Platform/x86x64/Linux" "../../StorageUtility" "../../StorageUtility/Linux" "../../vtStor" "../../vtStor/Platform/Linux"

CONFIG(release, debug|release) {

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_StorageUtility/Release/ -lStorageUtility

    INCLUDEPATH += $$PWD/../Build_StorageUtility/Release
    DEPENDPATH += $$PWD/../Build_StorageUtility/Release

    unix:!macx:!symbian: PRE_TARGETDEPS += $$PWD/../Build_StorageUtility/Release/libStorageUtility.a

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_vtStor/Release/ -lvtStor

    INCLUDEPATH += $$PWD/../Build_vtStor/Release
    DEPENDPATH += $$PWD/../Build_vtStor/Release

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_vtStorAtaProtocol/Release/ -lvtStorAtaProtocol

    INCLUDEPATH += $$PWD/../Build_vtStorAtaProtocol/Release
    DEPENDPATH += $$PWD/../Build_vtStorAtaProtocol/Release
}

CONFIG(debug, debug|release) {

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_StorageUtility/Debug/ -lStorageUtility

    INCLUDEPATH += $$PWD/../Build_StorageUtility/Debug
    DEPENDPATH += $$PWD/../Build_StorageUtility/Debug

    unix:!macx:!symbian: PRE_TARGETDEPS += $$PWD/../Build_StorageUtility/Debug/libStorageUtility.a

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_vtStor/Debug/ -lvtStor

    INCLUDEPATH += $$PWD/../Build_vtStor/Debug
    DEPENDPATH += $$PWD/../Build_vtStor/Debug

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_vtStorAtaProtocol/Debug/ -lvtStorAtaProtocol

    INCLUDEPATH += $$PWD/../Build_vtStorAtaProtocol/Debug
    DEPENDPATH += $$PWD/../Build_vtStorAtaProtocol/Debug
}
