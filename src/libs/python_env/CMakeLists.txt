project(python_env)

find_package(Qt5 COMPONENTS 
    Core
    Gui
    Widgets
    REQUIRED
)

set(python_env_source_files
    python_command.cpp
    python_engine.cpp
)

set(python_env_header_files
    python_command.h
    python_engine.h
    python_env_global.h
)

add_library(python_env_lib SHARED
    ${python_env_header_files}
    ${python_env_source_files}
)

target_include_directories(python_env_lib PUBLIC
    ${source_lib_dir}
    )

target_compile_definitions(python_env_lib PRIVATE
    PYTHON_ENV_LIBRARY
    )

target_link_libraries(
    python_env_lib
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    $<TARGET_LINKER_FILE:progress_util_lib>
)

set_target_properties(
    python_env_lib
    PROPERTIES
        OUTPUT_NAME python_env
        ARCHIVE_OUTPUT_DIRECTORY ${build_lib_dir}
        RUNTIME_OUTPUT_DIRECTORY ${build_bin_dir}
)



