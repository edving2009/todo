cmake_minimum_required(VERSION 4.0)

project(todo LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(todo 
    src/main.cpp
    src/fs.cpp)

target_compile_features(todo
    PUBLIC
        cxx_std_26)

target_include_directories(todo
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src")

if(WIN32)
    target_compile_definitions(todo PRIVATE _CONSOLE UNICODE _UNICODE WIN32)
    target_compile_options(todo PRIVATE /W3)
else()
    target_compile_options(todo PRIVATE -Wall -Wextra)
endif()