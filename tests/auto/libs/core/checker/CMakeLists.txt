project(test_core_checker)

find_package(Qt5 COMPONENTS
    Core
    Gui
    Widgets
    REQUIRED)

set(test_core_checker_header_files
    tst_test_sms_checker.h)

set(test_core_checker_source_files
    main.cpp)

add_executable(test_core_checker
    ${test_core_checker_header_files}
    ${test_core_checker_source_files}
    ${gtest_source_files}
    )

target_link_libraries(test_core_checker PRIVATE
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    ${core_test_libraries}
    $<TARGET_LINKER_FILE:sms_task_package>
)

target_include_directories(test_core_checker PUBLIC
    ${gtest_include_path}
    ${core_test_include_paths}
)

set_target_properties(test_core_checker
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${build_bin_dir}
)

add_test(NAME test_core_checker
    COMMAND $<TARGET_FILE:test_core_checker>)
