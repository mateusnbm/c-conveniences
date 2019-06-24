#
#
# CMakeLists.txt
#
# NBMImageConveniences
#
#

cmake_minimum_required( VERSION 3.4.1 )

project( NBMImageConveniences )

set( LOCAL_PATH ${CMAKE_SOURCE_DIR}/NBMImageConveniences )
set( CXIMAGE_VERSION CxImage )
set( CXIMAGE_PATH ${LOCAL_PATH}/${CXIMAGE_VERSION} )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++03")

#
# CxImage
#

add_definitions( ${GLOBAL_DEFINITIONS} )

include_directories( ${CXIMAGE_PATH}/CxImage )
include_directories( ${CXIMAGE_PATH}/zlib )
include_directories( ${CXIMAGE_PATH}/jasper/include )
include_directories( ${CXIMAGE_PATH}/jpeg )
include_directories( ${CXIMAGE_PATH}/png )
include_directories( ${CXIMAGE_PATH}/tiff )

include_directories( ${LOCAL_PATH} )

file( GLOB ZLIB_SRC "${CXIMAGE_PATH}/zlib/*.c" )
file( GLOB JASPER_SRC_BASE "${CXIMAGE_PATH}/jasper/base/*.c" )
file( GLOB JASPER_SRC_BMP "${CXIMAGE_PATH}/jasper/bmp/*.c" )
file( GLOB JASPER_SRC_JP2 "${CXIMAGE_PATH}/jasper/jp2/*.c" )
file( GLOB JASPER_SRC_JPC "${CXIMAGE_PATH}/jasper/jpc/*.c" )
file( GLOB JASPER_SRC_JPG "${CXIMAGE_PATH}/jasper/jpg/*.c" )
file( GLOB JASPER_SRC_MIF "${CXIMAGE_PATH}/jasper/mif/*.c" )
file( GLOB JASPER_SRC_PGX "${CXIMAGE_PATH}/jasper/pgx/*.c" )
file( GLOB JASPER_SRC_PNM "${CXIMAGE_PATH}/jasper/pnm/*.c" )
file( GLOB JASPER_SRC_RAS "${CXIMAGE_PATH}/jasper/ras/*.c" )
file( GLOB JPEG_SRC "${CXIMAGE_PATH}/jpeg/*.c" )
file( GLOB PNG_SRC "${CXIMAGE_PATH}/png/*.c" )
file( GLOB TIFF_SRC "${CXIMAGE_PATH}/tiff/*.c" )
file( GLOB CXIMAGE_SRC "${CXIMAGE_PATH}/CxImage/*.cpp" )

#
# Conveniences
#

file(GLOB IMAGE_CONVENIENCES_FILES "${LOCAL_PATH}/*.cpp")

#
# Configure library.
#

set(
    JASPER_SRC
    ${JASPER_SRC_BASE}
    ${JASPER_SRC_BMP}
    ${JASPER_SRC_JP2}
    ${JASPER_SRC_JPC}
    ${JASPER_SRC_JPG}
    ${JASPER_SRC_MIF}
    ${JASPER_SRC_PGX}
    ${JASPER_SRC_PNM}
    ${JASPER_SRC_RAS}
    )

set(
    LOCAL_SRC_FILES
    ${ZLIB_SRC}
    ${JASPER_SRC}
    ${JPEG_SRC}
    ${PNG_SRC}
    ${TIFF_SRC}
    ${CXIMAGE_SRC}
    ${IMAGE_CONVENIENCES_FILES}
    )

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -std=c99 -g" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -fpermissive -Wwrite-strings" )

add_library( NBMImageConveniences ${OUTPUT_LIBRARY_TYPE} ${LOCAL_SRC_FILES} )
