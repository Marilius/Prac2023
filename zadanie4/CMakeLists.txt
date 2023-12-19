cmake_minimum_required(VERSION 3.16)
project(zadanie4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-O3 -Wall)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

set(GA src/lims.hpp src/crossing.cpp src/selection.cpp src/life_engine.hpp src/survival.cpp src/mutation.cpp src/ga.cpp)

set(SOURCE_EXE main.cpp)
set(RESEARCH_EXE research/research.cpp)

add_library(zadanie4 ${GA})

# option(USER_TEST "Compile main.cpp file" OFF)

add_executable(main ${SOURCE_EXE})
target_link_libraries(main zadanie4 ${CURSES_LIBRARIES})

add_executable(rsch ${RESEARCH_EXE})
target_link_libraries(rsch zadanie4 ${CURSES_LIBRARIES})
