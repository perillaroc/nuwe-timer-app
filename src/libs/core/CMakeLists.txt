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
    time_trigger.cpp
)

set(core_lib_header_files
    core_global.h
    node.h
    trigger.h
    task.h
    node_state.h
    time_trigger.h
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
)

set_target_properties(
    core_lib
    PROPERTIES
        OUTPUT_NAME core
        ARCHIVE_OUTPUT_DIRECTORY ${build_lib_dir}
        RUNTIME_OUTPUT_DIRECTORY ${build_bin_dir}
)
