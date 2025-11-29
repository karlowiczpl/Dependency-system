cmake_minimum_required(VERSION 3.15)
project(Dependency_system C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(Dependency_system  src/dependency_system.c)
target_include_directories(Dependency_system PUBLIC include)

if (CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    enable_testing()
    add_subdirectory(tests)
endif()
