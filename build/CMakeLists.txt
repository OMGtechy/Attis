cmake_minimum_required (VERSION 2.8)

project (attis)

file (GLOB_RECURSE attis_source "../source/*.cpp")

include_directories (../include)

if (NOT WIN32)
    add_definitions (-std=c++14)
endif()

add_executable (attis ${attis_source})