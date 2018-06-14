project(test_core_task)

find_package(Qt5 COMPONENTS
    Core
    Gui
    Widgets
    Test
    REQUIRED)

set(test_core_task_source_files
    tst_task_test.cpp)

add_executable(test_core_task
    ${test_core_task_source_files}
    )

target_link_libraries(test_core_task PRIVATE
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    Qt5::Test
    ${core_test_libraries})

target_include_directories(test_core_task PUBLIC
    ${core_test_include_paths})

set_target_properties(test_core_task
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${build_bin_dir}
)
