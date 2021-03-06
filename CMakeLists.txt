cmake_minimum_required(VERSION 3.12.1)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(QSolver)

option(BUILD_TESTS "Build tests." OFF)
option(BUILD_DOC "Build API documentation." OFF)

include_directories(include)
add_subdirectory(src)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if (BUILD_DOC)
    add_subdirectory(doc)
endif()
