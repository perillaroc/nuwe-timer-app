include($$PWD/../../../nuwe-timer-app.pri)

INCLUDEPATH += $$source_base_dir/src/libs
INCLUDEPATH += $$source_base_dir/src/plugins

LIBS += -L$$build_lib_dir -lprogress_util -lpython_env -lcore
