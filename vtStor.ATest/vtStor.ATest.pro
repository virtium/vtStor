TARGET = vtStor.ATest
CONFIG   += console
CONFIG   -= app_bundle
QMAKE_CXXFLAGS += -std=c++14
QMAKE_CXXFLAGS += -fpermissive

TEMPLATE = app

SOURCES += main.cpp

INCLUDEPATH += "../../vtStorAta" "../../vtStorAta/Platform/Linux" "../../vtStorAtaProtocol" "../../vtStorAtaProtocol/Platform/Linux" "../../vtStorAta/Platform/Linux" "../../vtStorScsi" "../../vtStorScsi/Platform/Linux" "../../vtStorScsiProtocol" "../../vtStorScsiProtocol/Platform/Linux" "../../vtStorScsi/Platform/Linux" "../../Common" "../../Common/Platform/x86x64" "../../Common/Platform/x86x64/Linux" "../../StorageUtility" "../../StorageUtility/Linux" "../../vtStor" "../../vtStor/Platform/Linux"



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

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_vtStorAta/Release/ -lvtStorAta

    INCLUDEPATH += $$PWD/../Build_vtStorAta/Release
    DEPENDPATH += $$PWD/../Build_vtStorAta/Release

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_vtStorScsiProtocol/Release/ -lvtStorScsiProtocol

    INCLUDEPATH += $$PWD/../Build_vtStorScsiProtocol/Release
    DEPENDPATH += $$PWD/../Build_vtStorScsiProtocol/Release

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_vtStorScsi/Release/ -lvtStorScsi

    INCLUDEPATH += $$PWD/../Build_vtStorScsi/Release
    DEPENDPATH += $$PWD/../Build_vtStorScsi/Release
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

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_vtStorAta/Debug/ -lvtStorAta

    INCLUDEPATH += $$PWD/../Build_vtStorAta/Debug
    DEPENDPATH += $$PWD/../Build_vtStorAta/Debug

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_vtStorScsiProtocol/Debug/ -lvtStorScsiProtocol

    INCLUDEPATH += $$PWD/../Build_vtStorScsiProtocol/Debug
    DEPENDPATH += $$PWD/../Build_vtStorScsiProtocol/Debug

    unix:!macx:!symbian: LIBS += -L$$PWD/../Build_vtStorScsi/Debug/ -lvtStorScsi

    INCLUDEPATH += $$PWD/../Build_vtStorScsi/Debug
    DEPENDPATH += $$PWD/../Build_vtStorScsi/Debug
}

unix:!macx:!symbian: LIBS += -ludev
