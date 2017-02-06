include(../test_core.pri)

include($$auto_test_base_dir/gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread

HEADERS += \
    tst_test_sms_checker.h

SOURCES += \
    main.cpp
