QT -= gui
QT += network

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ../sharedItemLoader/baseitem.cpp \
        ../sharedItemLoader/basetool.cpp \
        ../sharedItemLoader/baseweapon.cpp \
        ../sharedItemLoader/itemloader.cpp \
        inventorycontroller.cpp \
        itemcontroller.cpp \
        main.cpp \
        mapfileloader.cpp \
        mapworker.cpp \
        server.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../sharedItemLoader/baseitem.h \
    ../sharedItemLoader/basetool.h \
    ../sharedItemLoader/baseweapon.h \
    ../sharedItemLoader/itemloader.h \
    enums.h \
    inventorycontroller.h \
    itemcontroller.h \
    mapfileloader.h \
    mapworker.h \
    server.h
