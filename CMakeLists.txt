cmake_minimum_required(VERSION 3.24)
project(Raspainter)

set(CMAKE_CXX_STANDARD 17)
add_executable(Raspainter main.cpp glad.c Shader.h main.h Camera.h vertices.h mesh.h Model.h)

#Adding the GLFW header file and library to the project
target_include_directories(Raspainter PUBLIC /Library/Developer/CommandLineTools/usr/include/OpenGL/include)
find_library(TEST_LIBRARY libglfw.3.dylib lib)
target_link_libraries(Raspainter LINK_PUBLIC  ${TEST_LIBRARY})

find_library(TEST_LIBRARY1 libassimp.5.2.5.dylib lib)
target_link_libraries(Raspainter LINK_PUBLIC  ${TEST_LIBRARY1})

find_library(TEST_LIBRARY2 libassimp.5.dylib lib)
target_link_libraries(Raspainter LINK_PUBLIC  ${TEST_LIBRARY2})

find_library(TEST_LIBRARY3 libassimp.dylib lib)
target_link_libraries(Raspainter LINK_PUBLIC  ${TEST_LIBRARY3})