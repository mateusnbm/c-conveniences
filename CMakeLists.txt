#
# CMakeLists.txt
#

cmake_minimum_required(VERSION 3.4.1)

project(c_conveniences)

set(ROOT_PATH ${PROJECT_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})

set(CMAKE_C_FLAGS "-fexceptions -Wstack-protector -fstack-protector ${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wincompatible-pointer-types-discards-qualifiers -w -fexceptions -fstack-protector -Wstack-protector")

add_subdirectory(${ROOT_PATH}/NBMAlgorithms)
add_subdirectory(${ROOT_PATH}/NBMStructures)
add_subdirectory(${ROOT_PATH}/NBMImageConveniences)
add_subdirectory(${ROOT_PATH}/NBMDemos)
