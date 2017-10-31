cmake_minimum_required(VERSION 3.9)
project(Dragons_Crystals)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Model.cpp Model.h View.h TextView.cpp TextView.h Controller.cpp Controller.h Commands.h Room.h Event.h Player.h Event.cpp Factory.cpp Factory.h)
add_executable(Dragons_Crystals ${SOURCE_FILES})