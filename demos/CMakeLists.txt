#
# CMakeLists.txt
#
# structures/demos/
#

cmake_minimum_required( VERSION 3.4.1 )

project( demos )

set( LOCAL_PATH ${CMAKE_SOURCE_DIR}/demos )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++03" )

add_definitions( ${GLOBAL_DEFINITIONS} )

include_directories( ${ROOT_PATH}/algorithms )
include_directories( ${ROOT_PATH}/structures )
include_directories( ${LOCAL_PATH} )

file( GLOB DEMOS_FILES "${LOCAL_PATH}/*.cpp" )

set( LOCAL_SRC_FILES ${DEMOS_FILES} )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -std=c99 -g" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -fpermissive -Wwrite-strings" )

#
# Algorithms.
#

set( BUBBLESORT-DEMO algorithm-bubblesort )
add_executable( ${BUBBLESORT-DEMO} algorithm-bubblesort.cpp )
target_link_libraries( ${BUBBLESORT-DEMO} algorithms )

set( MERGESORT-DEMO algorithm-mergesort )
add_executable( ${MERGESORT-DEMO} algorithm-mergesort.cpp )
target_link_libraries( ${MERGESORT-DEMO} algorithms )

set( QUICKSORT-DEMO algorithm-quicksort )
add_executable( ${QUICKSORT-DEMO} algorithm-quicksort.cpp )
target_link_libraries( ${QUICKSORT-DEMO} algorithms )

#
# Structures.
#

set( LIST-DEMO structure-list )
add_executable( ${LIST-DEMO} structure-list.cpp )
target_link_libraries( ${LIST-DEMO} structures )

set( STACK-DEMO structure-stack )
add_executable( ${STACK-DEMO} structure-stack.cpp )
target_link_libraries( ${STACK-DEMO} structures )
