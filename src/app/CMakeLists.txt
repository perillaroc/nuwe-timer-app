project(app)

find_package(Qt5 COMPONENTS
    Core
    Gui
    Widgets
    REQUIRED)

set(app_source_files
    main.cpp
    mainwindow.cpp)

set(app_header_files
    mainwindow.h)

set(app_form_files
    mainwindow.ui)

set(app_resource_files
    images.qrc)

add_executable(app_exe
    ${app_header_files}
    ${app_source_files}
    ${app_form_files}
    ${app_resource_files})

target_include_directories(
    app_exe PRIVATE
    ${src_source_dir}/libs
)

target_link_libraries(app_exe
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    $<TARGET_LINKER_FILE:progress_util_lib>
    $<TARGET_LINKER_FILE:python_env_lib>
    $<TARGET_LINKER_FILE:core_lib>
    )

set_target_properties(
    app_exe
    PROPERTIES
        RUNTIME_OUTPUT_NAME "nuwe-timer-app"
        RUNTIME_OUTPUT_DIRECTORY  ${build_bin_dir}
)

add_custom_command(
    TARGET app_exe
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/nwpc-sms-collector"
    "${build_bin_dir}/nwpc-sms-collector"
)
