#-------------------------------------------------
#
# Project created by QtCreator 2015-12-22T17:09:54
#
#-------------------------------------------------

TARGET = vtStorScsi
TEMPLATE = lib
QMAKE_CXXFLAGS += -std=c++14
QMAKE_CXXFLAGS += -fpermissive
DEFINES += VTSTORSCSI_LIBRARY

SOURCES += \
    CommandHandlerScsi.cpp \
    CommandDescriptorScsi.cpp \
    DriveScsi.cpp \
    DriveEnumeratorScsi.cpp \
    ScsiCommandExtensions.cpp

HEADERS += \
    CommandHandlerScsi.h \
    CommandDescriptorScsi.h \
    DriveScsi.h \
    DriveEnumeratorScsi.h \
    ScsiCommandExtensions.h

INCLUDEPATH += "../Extern" "../../vtStorScsiProtocol" "../../vtStorScsiProtocol/Platform/Linux" "../../vtStorScsi/Platform/Linux" "../../Common" "../../Common/Platform/x86x64" "../../Common/Platform/x86x64/Linux" "../../StorageUtility" "../../StorageUtility/Linux" "../../vtStor" "../../vtStor/Platform/Linux"

CONFIG(debug, debug|release) {

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_StorageUtility/Debug/ -lStorageUtility

    INCLUDEPATH += $$PWD/../Build_StorageUtility/Debug
    DEPENDPATH += $$PWD/../Build_StorageUtility/Debug

    unix:!macx:!symbian: PRE_TARGETDEPS += $$PWD/../Build_StorageUtility/Debug/libStorageUtility.a

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_vtStor/Debug/ -lvtStor

    INCLUDEPATH += $$PWD/../Build_vtStor/Debug
    DEPENDPATH += $$PWD/../Build_vtStor/Debug

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_vtStorScsiProtocol/Debug/ -lvtStorScsiProtocol

    INCLUDEPATH += $$PWD/../Build_vtStorScsiProtocol/Debug
    DEPENDPATH += $$PWD/../Build_vtStorScsiProtocol/Debug
}

CONFIG(release, debug|release) {

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_StorageUtility/Release/ -lStorageUtility

    INCLUDEPATH += $$PWD/../Build_StorageUtility/Release
    DEPENDPATH += $$PWD/../Build_StorageUtility/Release

    unix:!macx:!symbian: PRE_TARGETDEPS += $$PWD/../Build_StorageUtility/Release/libStorageUtility.a

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_vtStor/Release/ -lvtStor

    INCLUDEPATH += $$PWD/../Build_vtStor/Release
    DEPENDPATH += $$PWD/../Build_vtStor/Release

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_vtStorScsiProtocol/Release/ -lvtStorScsiProtocol

    INCLUDEPATH += $$PWD/../Build_vtStorScsiProtocol/Release
    DEPENDPATH += $$PWD/../Build_vtStorScsiProtocol/Release
}

OTHER_FILES += \
    Common.props


