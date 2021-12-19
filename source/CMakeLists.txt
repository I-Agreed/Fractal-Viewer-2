cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Fractal VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(Fractal main.cpp)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(Fractal PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "C:/Program Files/Boost/multiprecision/cpp_bin_float.hpp"
                           "C:/mingw_dev_lib/SFML-2.5.1/include"
                           )

find_library(SFML_GRAPHICS sfml-graphics "C:/mingw_dev_lib/SFML-2.5.1/lib")
find_library(SFML_WINDOW sfml-window "C:/mingw_dev_lib/SFML-2.5.1/lib")
find_library(SFML_SYSTEM sfml-system "C:/mingw_dev_lib/SFML-2.5.1/lib")
target_link_libraries(Fractal PUBLIC 
                        ${SFML_GRAPHICS}
                        ${SFML_WINDOW}
                        ${SFML_SYSTEM}
                        )
