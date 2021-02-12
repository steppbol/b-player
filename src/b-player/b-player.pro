linux-g++* {
QT       += core gui widgets multimedia
}

win32 {
QT       += core gui widgets multimedia winextras
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

VERSION = 1.0.0
QMAKE_TARGET_COMPANY = steppbol
QMAKE_TARGET_PRODUCT = B-Player
QMAKE_TARGET_DISCRIPTION = Audio player is designed to facilitate work with audiofiles
QMAKE_TARGET_COPYRIGHT = steppbol

TARGET = B-Player
TEMPLATE = app

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    style.cpp \
    volumebutton.cpp \
    widget.cpp

HEADERS += \
    style.h \
    volumebutton.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    buttons.qrc

RC_ICONS = icon/b-player.ico
