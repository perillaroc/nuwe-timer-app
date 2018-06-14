project(core)

find_package(Qt5 COMPONENTS
    Core
    Gui
    Widgets
    REQUIRED)

set(core_lib_source_files
    node.cpp
    trigger.cpp
    task.cpp
    node_state.cpp
    sms_task.cpp
    time_trigger.cpp
    sms_checker.cpp
)

set(core_lib_header_files
    core_global.h
    node.h
    trigger.h
    task.h
    node_state.h
    sms_task.h
    time_trigger.h
    sms_checker.h
)

add_library(core_lib SHARED
    ${core_lib_source_files}
    ${core_lib_header_files}
)

target_include_directories(
    core_lib PUBLIC
    ${source_lib_dir}
    )

target_compile_definitions(
    core_lib PRIVATE
    CORE_LIBRARY)

target_link_libraries(
    core_lib
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    $<TARGET_LINKER_FILE:progress_util_lib>
    $<TARGET_LINKER_FILE:python_env_lib>
)

set_target_properties(
    core_lib
    PROPERTIES
        OUTPUT_NAME core
        ARCHIVE_OUTPUT_DIRECTORY ${build_lib_dir}
        RUNTIME_OUTPUT_DIRECTORY ${build_bin_dir}
)
