cmake_minimum_required(VERSION 3.5.2)
project (normalization)

include_directories(3rd/include include)
find_library(PCRE_LIBRARIES pcrecpp)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpcrecpp -std=c++11")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lpcrecpp")
set(SOURCES src/main.cpp src/util.cpp)

# file(GLOB SOURCES "src/*.cpp")

add_executable(normal ${SOURCES})
