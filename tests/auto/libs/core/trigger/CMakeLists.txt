project(test_core_trigger)

find_package(Qt5 COMPONENTS
    Core
    Gui
    Widgets
    REQUIRED)

set(test_core_trigger_header_files
    tst_test_time_trigger.h)

set(test_core_trigger_source_files
    main.cpp)

add_executable(test_core_trigger
    ${test_core_trigger_header_files}
    ${test_core_trigger_source_files}
    ${gtest_source_files}
    )

target_link_libraries(test_core_trigger PRIVATE
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    ${core_test_libraries})

target_include_directories(test_core_trigger PUBLIC
    ${gtest_include_path}
    ${core_test_include_paths})

set_target_properties(test_core_trigger
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${build_bin_dir}
)
