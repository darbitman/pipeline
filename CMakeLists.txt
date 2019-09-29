cmake_minimum_required(VERSION 3.0)

project(SeamCarver)

set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

# Generate CMakeLists.txt that will pull the repo
configure_file(
    CMakeLists.googletest.txt
    ${PROJECT_SOURCE_DIR}/googletest-download/CMakeLists.txt
)

# Use the generated CMakeLists.txt file to generate the build files to download googletest
execute_process(
    COMMAND
        ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY
        ${PROJECT_SOURCE_DIR}/googletest-download
)

# Use the generate build files to download googletest
execute_process(
    COMMAND
        ${CMAKE_COMMAND} --build .
    WORKING_DIRECTORY
        ${PROJECT_SOURCE_DIR}/googletest-download
)

set(gtest_force_shared_crt ON CACHE BOOL "")
set(INSTALL_GTEST OFF CACHE BOOL "")
set(BUILD_GMOCK OFF CACHE BOOL "")

add_subdirectory(
    ${PROJECT_SOURCE_DIR}/googletest-src
    ${PROJECT_SOURCE_DIR}/googletest-build
)

#find_package(OpenCV)

add_subdirectory(src)

option(BUILD_UNIT_TESTS "" ON)
