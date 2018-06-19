project(sms_task)

find_package(Qt5 COMPONENTS
    Core
    Gui
    Widgets
    REQUIRED)

set(sms_task_source_files
    sms_task.cpp
    sms_checker.cpp
)

set(sms_task_header_files
    sms_task_global.h
    sms_task.h
    sms_checker.h
)

add_library(sms_task_package STATIC
    ${sms_task_source_files}
    ${sms_task_header_files}
)

target_include_directories(
    sms_task_package PUBLIC
    ${src_source_dir}/libs
    )

target_compile_definitions(
    sms_task_package PRIVATE
    SMS_TASK_LIBRARY)

target_link_libraries(
    sms_task_package
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    $<TARGET_LINKER_FILE:core_lib>
    $<TARGET_LINKER_FILE:progress_util_lib>
    $<TARGET_LINKER_FILE:python_env_lib>
)

set_target_properties(
    sms_task_package
    PROPERTIES
        OUTPUT_NAME sms_task
        ARCHIVE_OUTPUT_DIRECTORY ${build_lib_dir}
        RUNTIME_OUTPUT_DIRECTORY ${build_bin_dir}
)
