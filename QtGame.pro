QT       += core gui \
        multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += resources_big

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    consoObject.cpp \
    element.cpp \
    finishflag.cpp \
    fixedblock.cpp \
    gameEngine.cpp \
    gelprojectile.cpp \
    info.cpp \
    lifebar.cpp \
    menu.cpp \
    menubutton.cpp \
    gel.cpp \
    heart.cpp \
    main.cpp \
    map.cpp \
    mask.cpp \
    mobilevirus.cpp \
    pausegroup.cpp \
    player.cpp \
    projectile.cpp \
    unit.cpp \
    victorygroup.cpp \
    virus.cpp \
    wall.cpp

HEADERS += \
    collidemanager.h \
    configuration.h \
    consoObject.h \
    element.h \
    finishflag.h \
    fixedblock.h \
    gameEngine.h \
    gelprojectile.h \
    info.h \
    lifebar.h \
    menubutton.h \
    gel.h \
    heart.h \
    map.h \
    mask.h \
    mobilevirus.h \
    pausegroup.h \
    player.h \
    projectile.h \
    unit.h \
    victorygroup.h \
    virus.h \
    wall.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Ressource.qrc
