include(../../nuwe-timer-app.pri)

QT       += core gui widgets

TEMPLATE = app

TARGET = nuwe-timer-app
DESTDIR=$$build_base_dir/bin

INCLUDEPATH += ../libs
LIBS += -L$$build_lib_dir -lprogress_util

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    check_task.cpp \
    python_command.cpp \
    python_engine.cpp

HEADERS  += mainwindow.h \
    check_task.h \
    python_command.h \
    python_engine.h

FORMS    += mainwindow.ui

DISTFILES += \
    nwpc-sms-collector/sms_collector.py

nwpc_sms_target_dir = $${DESTDIR}/nwpc-sms-collector
nwpc_sms_target_dir~=s,/,\\,g
nwpc_sms_dir = $$PWD/nwpc-sms-collector
nwpc_sms_dir~=s,/,\\,g

QMAKE_POST_LINK += $$quote(IF NOT EXIST $${nwpc_sms_target_dir} (MKDIR $${nwpc_sms_target_dir})$$escape_expand(\n\t))
QMAKE_POST_LINK += $$quote(XCOPY $${nwpc_sms_dir} $${nwpc_sms_target_dir} /E /Y$$escape_expand(\n\t))