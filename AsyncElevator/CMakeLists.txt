cmake_minimum_required(VERSION 3.30)
project(AsyncElevator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(APP_NAME AsyncElevator)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

include_directories(inc)

add_executable(${APP_NAME} src/main.cpp
        inc/Doors.h
        src/Doors.cpp
        inc/Cabin.h
        src/Cabin.cpp
        inc/Controller.h
        src/Controller.cpp
        src/Elevator.cpp
        inc/Elevator.h
        src/ui/MainWindow.hpp
        src/ui/MainWindow.cpp
        inc/Floor.h)

target_link_libraries(${APP_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)