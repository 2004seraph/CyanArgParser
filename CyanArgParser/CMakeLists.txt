# CMakeList.txt : CMake project for CyanArgParser, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set (CMAKE_CXX_STANDARD 17)

project ("CyanArgParser" VERSION 1.0.0 DESCRIPTION "A simple C++ argument parser")

add_library(CyanArgParser STATIC
    src/argParser.cpp
)

set_target_properties(
    CyanArgParser PROPERTIES 

    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER include/argParser.hpp
)

target_include_directories(CyanArgParser PRIVATE .)

install(
    TARGETS CyanArgParser
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)


# TESTS

add_subdirectory(testing)