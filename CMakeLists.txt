cmake_minimum_required(VERSION 3.10.0)

project(nuwe-timer-app)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-DQT_DEPRECATED_WARNINGS)
#add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x060000)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(build_base_dir ${CMAKE_CURRENT_BINARY_DIR})
set(build_bin_dir ${build_base_dir}/bin)
set(build_lib_dir ${build_base_dir}/lib)
set(build_plugins_dir ${build_base_dir}/plugins)
set(build_vendor_dir ${build_base_dir}/vendor)
set(src_source_dir ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# find python
include(nuwe_find_python3)
nuwe_find_python3()
nuwe_check_python3_library()

# configure file
configure_file(nuwe_timer_configure.h.in nuwe_timer_configure.h)

add_subdirectory(src)
add_subdirectory(tests)
