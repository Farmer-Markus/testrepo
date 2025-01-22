cmake_minimum_required(VERSION 3.6)

project(SDL_GAME)

if(ANDROID)
find_library(SDL2 SDL2)
#find_library(SDL2TTF SDL2_ttf)
find_library(SDL2IMAGE SDL2_image)
#find_library(SDL2MIXER SDL2_mixer)
else()
find_package(SDL2 REQUIRED)
#find_package(SDL2_TTF REQUIRED)
find_package(SDL2_Image REQUIRED)
#find_package(SDL2_MIXER REQUIRED)
endif()

include_directories(${SDL2_INCLUDE_DIRS})
#include_directories(${SDL2TTF_INCLUDE_DIRS})
include_directories(${SDL2IMAGE_INCLUDE_DIRS})
#include_directories(${SDL2MIXER_INCLUDE_DIRS})

if(ANDROID)
    add_library(main SHARED)
    target_sources(main PUBLIC main.cpp game.cpp world.cpp texture.cpp building.cpp)
    target_link_libraries(main SDL2 log SDL2_image) # SDL2_image GLESv2)
else()
    add_executable(SDL-Game main.cpp game.cpp world.cpp texture.cpp building.cpp)
    target_link_libraries(SDL-Game SDL2 SDL2_image::SDL2_image) #${SDL2IMAGE_LIBRARIES} ${SDL2MIXER_LIBRARIES} ${SDL2TTF_LIBRARIES})
endif()





