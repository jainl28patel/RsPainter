cmake_minimum_required(VERSION 3.24)
project(Raspainter)

set(CMAKE_CXX_STANDARD 17)
add_executable(Raspainter main.cpp glad.c Shader.h)

#Adding the GLFW header file and library to the project
target_include_directories(Raspainter PUBLIC /Library/Developer/CommandLineTools/usr/include/OpenGL/include)
find_library(TEST_LIBRARY libglfw lib)
target_link_libraries(Raspainter LINK_PUBLIC ${TEST_LIBRARY})