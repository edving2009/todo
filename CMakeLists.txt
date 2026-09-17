cmake_minimum_required(VERSION 4.0)

project(todo LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(todo 
    src/main.cpp
    src/fs.cpp
    src/terminal.cpp)

target_compile_features(todo
    PUBLIC
        cxx_std_23)

target_include_directories(todo
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src")

if(WIN32)
    target_compile_definitions(todo PRIVATE _CONSOLE UNICODE _UNICODE WIN32)
    target_compile_options(todo PRIVATE
 	/W3 $<$<CONFIG:Release>:/O2 /Oi /Gy>)
    target_link_options(todo PRIVATE
        $<$<CONFIG:Release>:/OPT:REF /OPT:ICF>)
else()
    target_compile_options(todo PRIVATE
	-Wall -Wextra
	$<$<CONFIG:Release>:-O3>)
endif()