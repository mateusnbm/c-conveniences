#
#
# CMakeLists.txt
#
# NBMDemos
#
#

cmake_minimum_required( VERSION 3.4.1 )

project( NBMDemos )

set( LOCAL_PATH ${CMAKE_SOURCE_DIR}/NBMDemos )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++03" )

add_definitions( ${GLOBAL_DEFINITIONS} )

include_directories( ${ROOT_PATH}/NBMAlgorithms )
include_directories( ${ROOT_PATH}/NBMStructures )
include_directories( ${ROOT_PATH}/NBMImageConveniences )
include_directories( ${LOCAL_PATH} )

file( GLOB DEMOS_FILES "${LOCAL_PATH}/*.cpp" )

set( LOCAL_SRC_FILES ${DEMOS_FILES} )
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -std=c99 -g" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -fpermissive -Wwrite-strings" )

#
# Demo algorithms.
#

set( BUBBLESORT-DEMO algorithm-bubblesort )
add_executable( ${BUBBLESORT-DEMO} algorithm-bubblesort.cpp )
target_link_libraries( ${BUBBLESORT-DEMO} NBMAlgorithms )

set( MERGESORT-DEMO algorithm-mergesort )
add_executable( ${MERGESORT-DEMO} algorithm-mergesort.cpp )
target_link_libraries( ${MERGESORT-DEMO} NBMAlgorithms )

set( QUICKSORT-DEMO algorithm-quicksort )
add_executable( ${QUICKSORT-DEMO} algorithm-quicksort.cpp )
target_link_libraries( ${QUICKSORT-DEMO} NBMAlgorithms )

#
# Demo structures.
#

set( LIST-DEMO structure-list )
add_executable( ${LIST-DEMO} structure-list.cpp )
target_link_libraries( ${LIST-DEMO} NBMStructures )

set( STACK-DEMO structure-stack )
add_executable( ${STACK-DEMO} structure-stack.cpp )
target_link_libraries( ${STACK-DEMO} NBMStructures )

#
# Demo image conveniences.
#

set( CONVOLUTION-DEMO image-convolution )
add_executable( ${CONVOLUTION-DEMO} image-convolution.cpp )
target_link_libraries( ${CONVOLUTION-DEMO} NBMImageConveniences )
