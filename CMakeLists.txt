cmake_minimum_required(VERSION 3.7)

project(opengl-renderer-tests)

add_subdirectory(glad)

find_package(SDL2 CONFIG REQUIRED)
file(GLOB SOURCES "src/*.cpp")
include_directories(include)
add_executable(opengl-renderer-tests ${SOURCES})

target_link_libraries(opengl-renderer-tests PRIVATE SDL2::SDL2 SDL2::SDL2main glad)
set_property(TARGET opengl-renderer-tests PROPERTY CXX_STANDARD 17)