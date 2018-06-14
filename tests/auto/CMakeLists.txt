set(test_auto_base_dir ${CMAKE_CURRENT_SOURCE_DIR})

if(${GOOGLETEST_DIR})
    message(FATAL_ERROR "Please set GOOGLETEST_DIR to source directory of google test.")
endif()

set(gtest_src_dir ${GOOGLETEST_DIR}/googletest)
set(gmock_src_dir ${GOOGLETEST_DIR}/googlemock)

set(gtest_definitions
    GTEST_LANG_CXX11)

set(gtest_include_path
    ${gtest_src_dir}
    ${gtest_src_dir}/include
    ${gmock_src_dir}
    ${gmock_src_dir}/include)

set(gtest_source_files
    ${gtest_src_dir}/src/gtest-all.cc
    ${gmock_src_dir}/src/gmock-all.cc)

add_subdirectory(libs)
