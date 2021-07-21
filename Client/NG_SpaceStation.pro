QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    actionwindow.cpp \
    chatwindow.cpp \
    inventorywindow.cpp \
    main.cpp \
    mapworker.cpp \
    spacestation.cpp \
    statuswindow.cpp

HEADERS += \
    actionwindow.h \
    chatwindow.h \
    inventorywindow.h \
    mapworker.h \
    spacestation.h \
    statuswindow.h

FORMS += \
    actionwindow.ui \
    chatwindow.ui \
    inventorywindow.ui \
    spacestation.ui \
    statuswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
