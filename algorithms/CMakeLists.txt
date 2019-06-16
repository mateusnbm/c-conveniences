cmake_minimum_required(VERSION 3.4.1)
Project(algorithms)

set(LOCAL_PATH ${CMAKE_SOURCE_DIR}/algorithms)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++03")

add_definitions(${GLOBAL_DEFINITIONS})

include_directories(${LOCAL_PATH})

file(GLOB ALGORITHMS_FILES "${LOCAL_PATH}/*.cpp")

set(LOCAL_SRC_FILES ${ALGORITHMS_FILES})

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -std=c99 -g")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -fpermissive -Wwrite-strings")

add_library(algorithms ${OUTPUT_LIBRARY_TYPE} ${LOCAL_SRC_FILES})
