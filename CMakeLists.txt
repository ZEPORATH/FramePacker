cmake_minimum_required(VERSION 3.14)

project(FramePacker LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
find_package(spdlog REQUIRED)
find_package(cppzmq)
find_package(Threads REQUIRED)

add_executable(FramePacker
  main.cpp
  framepacker.cpp
  framepacker.h
)

add_executable(Client client.cpp client.h framepacker.cpp framepacker.h)
add_executable(BroadcastServer server.cpp server.h framepacker.cpp framepacker.h)

target_link_libraries(FramePacker ${OpenCV_LIBS})
target_link_libraries(Client cppzmq Threads::Threads ${OpenCV_LIBS})
target_link_libraries(BroadcastServer cppzmq Threads::Threads ${OpenCV_LIBS} )
