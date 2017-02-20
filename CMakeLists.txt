cmake_minimum_required(VERSION 3.5.2)
project (normalization)

include_directories(3rd/include include)

set(SOURCES src/main.cpp src/parameter.cpp src/recognizer.cpp src/util.cpp)

# file(GLOB SOURCES "src/*.cpp")

add_executable(normal ${SOURCES})
