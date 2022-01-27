QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client_connection_window.cpp \
    controller.cpp \
    main.cpp \
    black_jack.cpp

HEADERS += \
    black_jack.h \
    client_connection_window.h \
    controller.h

FORMS += \
    black_jack.ui \
    client_connection_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/release/ -lblackjackcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib//release/ -lblackjackcore
else:unix: LIBS += -L$$PWD/../lib/ -lblackjackcore

INCLUDEPATH += $$PWD/../lib/
DEPENDPATH += $$PWD/../lib/

RESOURCES += \
    Card_images.qrc
