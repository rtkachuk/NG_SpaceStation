QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../sharedItemLoader/baseitem.cpp \
    ../sharedItemLoader/basetool.cpp \
    ../sharedItemLoader/baseweapon.cpp \
    ../sharedItemLoader/itemloader.cpp \
    actionwindow.cpp \
    connectdialog.cpp \
    connectionmanager.cpp \
    main.cpp \
    mapworker.cpp \
    selectdirectiondialog.cpp \
    spacestation.cpp

HEADERS += \
    ../sharedItemLoader/baseitem.h \
    ../sharedItemLoader/basetool.h \
    ../sharedItemLoader/baseweapon.h \
    ../sharedItemLoader/itemloader.h \
    actionwindow.h \
    connectdialog.h \
    connectionmanager.h \
    mapworker.h \
    selectdirectiondialog.h \
    spacestation.h

FORMS += \
    actionwindow.ui \
    connectdialog.ui \
    selectdirectiondialog.ui \
    spacestation.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
