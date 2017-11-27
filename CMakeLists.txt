cmake_minimum_required(VERSION 3.8)
project(Visiongev)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

set(SOURCE_FILES mainContours.cpp avansvisionlib.cpp avansvisionlib.h includes.h Algorithms.cpp Algorithms.h)
add_executable(Visiongev ${SOURCE_FILES})

include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(Visiongev ${OpenCV_LIBS})