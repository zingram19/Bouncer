cmake_minimum_required(VERSION 3.7)
project(bouncer)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/inc)

add_executable(bouncer main.cpp game.cpp game.h main.h loop.cpp const.h texture.cpp texture.h controls.cpp level.cpp level.h)

target_link_libraries(bouncer ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_IMAGE_LIBRARY})