include(../../../nuwe-timer-app.pri)

QT       += core gui widgets

TARGET = core
TEMPLATE = lib
CONFIG += shared dll

DEFINES += CORE_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$source_base_dir/src/libs

LIBS += -L$$build_lib_dir -lprogress_util -lpython_env

SOURCES += \
    node.cpp \
    trigger.cpp \
    task.cpp \
    node_state.cpp \
    sms_task.cpp \
    time_trigger.cpp

HEADERS +=\
        core_global.h \
    node.h \
    trigger.h \
    task.h \
    node_state.h \
    sms_task.h \
    time_trigger.h

win32{
    DESTDIR = $$build_base_dir/lib
}
unix {
    target.path = /usr/lib
    INSTALLS += target
}
