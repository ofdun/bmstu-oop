cmake_minimum_required(VERSION 3.28)

project(viewer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(inc)

SET(APP_SOURCES 
    src/main.cpp
    src/validators.cpp
    src/graph.cpp
    src/graphics.cpp
    src/transform.cpp
    src/point.cpp
    src/transformGraph.cpp
    src/app.cpp
    src/renderer.cpp
    src/utils.cpp
    src/handler.cpp)


SET(APP_NAME "viewer.exe")

add_executable(${APP_NAME} ${APP_SOURCES})

find_package(SDL3 REQUIRED)

target_link_libraries(${APP_NAME} PRIVATE SDL3::SDL3)
