include(../../../nuwe-timer-app.pri)

DEFINES += PYTHON_ENV_LIBRARY

QT       += core gui widgets

TARGET = python_env
TEMPLATE = lib
CONFIG += shared dll

INCLUDEPATH += $$source_base_dir/src/libs
LIBS += -L$$build_lib_dir -lprogress_util

win32{
    DESTDIR = $$build_lib_dir
}
unix {
    target.path = /usr/lib
    INSTALLS += target
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    python_command.cpp \
    python_engine.cpp

HEADERS += \
    python_command.h \
    python_engine.h \
    python_env_global.h
