cmake_minimum_required(VERSION 3.10)

project(Dungeon)
find_package(Threads REQUIRED)
add_definitions("-std=c++17")


set(Dungeon_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/Includes)
set(Dungeon_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/Sources)
set(CMAKE_CXX_FLAGS "-O3")
set(CMAKE_BUILD_TYPE Release)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/bin)

add_executable(Dungeon
	${Dungeon_SOURCE_DIR}/DungeonGame/Dungeon/Generator.cpp
	${Dungeon_INCLUDE_DIR}/DungeonGame/utill/Input.hpp
	src/main.cpp
)

target_include_directories(Dungeon PUBLIC ${Dungeon_INCLUDE_DIR})