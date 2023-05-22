cmake_minimum_required(VERSION 3.22)
project(Hexagon)

set(CMAKE_CXX_STANDARD 23)

add_executable(Hexagon main.cpp Bot.h myWindow.h Hexagon.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/SFML/lib/cmake/SFML")
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Hexagon sfml-system sfml-window sfml-graphics sfml-audio)