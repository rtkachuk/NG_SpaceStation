QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../recipesLoader/recipesloader.cpp \
    ../sharedItemLoader/baseitem.cpp \
    ../sharedItemLoader/itemloader.cpp \
    actionwindow.cpp \
    buildingdialog.cpp \
    connectdialog.cpp \
    connectionmanager.cpp \
    generatorcontroller.cpp \
    inventorymenu.cpp \
    loaderprogress.cpp \
    main.cpp \
    mapworker.cpp \
    selectdirectiondialog.cpp \
    spacestation.cpp \
    statewindow.cpp \
    timer.cpp

HEADERS += \
    ../recipesLoader/recipesloader.h \
    ../sharedItemLoader/baseitem.h \
    ../sharedItemLoader/itemloader.h \
    actionwindow.h \
    buildingdialog.h \
    connectdialog.h \
    connectionmanager.h \
    enums.h \
    generatorcontroller.h \
    inventorymenu.h \
    loaderprogress.h \
    mapworker.h \
    selectdirectiondialog.h \
    spacestation.h \
    statewindow.h \
    timer.h

FORMS += \
    actionwindow.ui \
    buildingdialog.ui \
    connectdialog.ui \
    generatorcontroller.ui \
    inventorymenu.ui \
    loaderprogress.ui \
    selectdirectiondialog.ui \
    spacestation.ui \
    statewindow.ui \
    timer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
