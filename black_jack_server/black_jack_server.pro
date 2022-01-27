QT -= gui
QT += network
QT += core
QT += sql
CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        bj_tcp_server.cpp \
        db_connexion.cpp \
        game_handler.cpp \
        main.cpp \
        player_thread.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


HEADERS += \
    bj_tcp_server.h \
    db_connexion.h \
    game_handler.h \
    player_thread.h


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/release/ -lblackjackcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/release/ -lblackjackcore
else:unix: LIBS += -L$$PWD/../lib/ -lblackjackcore

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib
