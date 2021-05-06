cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -x c++ -std=c++2a -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall -Wextra -pedantic")

if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conaninfo.txt)
    list(PREPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_BINARY_DIR}")
endif()

find_package(libgit2 REQUIRED)

add_subdirectory(src)
