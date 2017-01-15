include(../../../nuwe-timer-app.pri)

DEFINES += PROGRESS_UTIL_LIBRARY

QT       += core gui widgets

TARGET = progress_util
TEMPLATE = lib
CONFIG += shared dll

win32{
    DESTDIR = $$build_base_dir/lib
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}


SOURCES += progress_util.cpp \
    synchronous_job.cpp \
    shell_command.cpp \
    async_job.cpp

HEADERS += progress_util.h\
        progress_util_global.h \
    synchronous_job.h \
    shell_command.h \
    async_job.h

