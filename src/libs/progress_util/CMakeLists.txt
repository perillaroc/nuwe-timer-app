project(progress_util)

add_definitions(-DPROGRESS_UTIL_LIBRARY)

find_package(Qt5 COMPONENTS
    Core
    Gui
    Widgets
    REQUIRED)

set(progress_util_header_files
    progress_util.h
    progress_util_global.h
    synchronous_job.h
    shell_command.h
    async_job.h
)

set(progress_util_src_files
    progress_util.cpp
    synchronous_job.cpp
    shell_command.cpp
    async_job.cpp
)

add_library(progress_util_lib STATIC
    ${progress_util_header_files}
    ${progress_util_src_files}
)

target_compile_definitions(progress_util_lib PRIVATE
    PROGRESS_UTIL_LIBRARY)

target_link_libraries(progress_util_lib
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
)

set_target_properties(progress_util_lib
    PROPERTIES
        OUTPUT_NAME progress_util
        ARCHIVE_OUTPUT_DIRECTORY ${build_lib_dir}
        RUNTIME_OUTPUT_DIRECTORY ${build_bin_dir}
)
