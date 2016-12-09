cmake_minimum_required(VERSION 3.6)
project(jajko)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp common.h egg.cpp egg.h rdraw.cpp rdraw.h)
add_executable(jajko ${SOURCE_FILES})

target_link_libraries(jajko -lGL -lGLU -lglut)
