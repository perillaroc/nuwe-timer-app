set(core_test_include_paths
    ${src_source_dir}/libs
    ${src_source_dir}/plugins
    )

set(core_test_libraries
    $<TARGET_LINKER_FILE:progress_util_lib>
    $<TARGET_LINKER_FILE:python_env_lib>
    $<TARGET_LINKER_FILE:core_lib>
)

add_subdirectory(checker)
add_subdirectory(node)
add_subdirectory(node_state)
add_subdirectory(task)
add_subdirectory(trigger)
