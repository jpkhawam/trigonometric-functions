cmake_minimum_required(VERSION 3.22)
project(TrigonometricFunctions)

set(CMAKE_CXX_STANDARD 20)

add_executable(TrigonometricFunctions src/main.cpp src/functions.h src/types.h)

set(OpenGlLinkers -lglut -lGLU -lGL)
target_link_libraries(TrigonometricFunctions ${OpenGlLinkers})
