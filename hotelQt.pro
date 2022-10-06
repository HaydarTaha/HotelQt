QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += sdk_no_version_check

QMAKE_CXXFLAGS=-Wall -Werror

#LIBS += -L/usr/local/mysql-8.0.30-macos12-arm64/lib -lmysqlclient -lssl -lcrypto -lresolv
LIBS += -L/opt/homebrew/Cellar/mysql/8.0.30_1/lib -lmysqlclient -lz #-L/usr/local/mysql-8.0.30-macos12-arm64/lib -lzstd

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addemployee.cpp \
    employee.cpp \
    emplyeenumber.cpp \
    main.cpp \
    mainwindow.cpp \
    rooms.cpp

HEADERS += \
    addemployee.h \
    employee.h \
    emplyeenumber.h \
    mainwindow.h \
    rooms.h

FORMS += \
    addemployee.ui \
    employee.ui \
    emplyeenumber.ui \
    mainwindow.ui \
    rooms.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
