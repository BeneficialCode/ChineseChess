cmake_minimum_required(VERSION 3.5)

project(ChineseChess)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(SOURCES
    "src/Application/Main.cpp"
    "src/Application/Application.cpp"
    "src/Application/Application.h"
)

add_executable(${PROJECT_NAME} WIN32 ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

target_include_directories(${PROJECT_NAME} PRIVATE
    "src"
)