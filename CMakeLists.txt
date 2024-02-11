cmake_minimum_required(VERSION 3.28.1)
project(rayteste)

find_package(PkgConfig REQUIRED)
pkg_search_module(RAYLIB REQUIRED raylib)
SET (CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(teste main.cpp)

target_include_directories(teste PRIVATE ${RAYLIB_INCLUDE_DIRS})
target_link_libraries(teste PRIVATE ${RAYLIB_LIBRARIES})

