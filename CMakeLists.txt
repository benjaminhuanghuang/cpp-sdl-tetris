cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project(cpp-sdl-tetris)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR} 
                    src)

add_executable(tetris src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/square.cpp src/block.cpp)

target_link_libraries(tetris ${SDL2_LIBRARY}
                             ${SDL2_IMAGE_LIBRARY}
                             ${SDL2_TTF_LIBRARY})