cmake_minimum_required(VERSION 3.22)
project(Hexagon)
set(CMAKE_CXX_STANDARD 23)
set(BUILD_SHARED_LIBS FALSE)
include(FetchContent)
FETCHCONTENT_DECLARE(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git)
FETCHCONTENT_MAKEAVAILABLE(SFML)
add_executable(Hexagon main.cpp Hexagon.h myWindow.h Hexagon.cpp myWindow.cpp)
target_link_libraries(Hexagon sfml-system sfml-window sfml-graphics)
target_compile_options(Hexagon PRIVATE -Wall -Wextra -pedantic)