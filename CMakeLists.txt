cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conaninfo.txt)
    list(PREPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_BINARY_DIR}")
endif()

find_package(libgit2 REQUIRED)

add_subdirectory(src)
