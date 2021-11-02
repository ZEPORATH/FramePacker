cmake_minimum_required(VERSION 3.14)

project(FramePacker LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
find_package(spdlog REQUIRED)

add_executable(FramePacker
  main.cpp
  framepacker.cpp
  framepacker.h
)
target_link_libraries(FramePacker ${OpenCV_LIBS})
