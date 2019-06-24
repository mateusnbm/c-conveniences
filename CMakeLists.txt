cmake_minimum_required(VERSION 3.4.1)
project(DSNativeMobile)

set(ROOT_PATH ${PROJECT_SOURCE_DIR})
set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})

# The version number.
set(VERSION_MAJOR 1) # Version X.0.0
set(VERSION_MINOR 2) # Version 0.X.0
set(VERSION_PATCH 0) # Version 0.0.X

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

if (DEFINED ANDROID_ABI)  #Android
  message(STATUS "Building for ANDROID!")
  set(GLOBAL_DEFINITIONS -DBUILD_ANDROID)
  set(STATIC_FOLDER ${ANDROID_ABI})
  set(OUTPUT_LIBRARY_TYPE SHARED)
elseif( WIN32 OR ( UNIX  AND NOT APPLE ) OR MSVC )
  message(STATUS "Building for PC!")
  set(GLOBAL_DEFINITIONS -DBUILD_PC)
  set(STATIC_FOLDER "x86_64")
  set(OUTPUT_LIBRARY_TYPE SHARED)
else()
  message(STATUS "Building for IOS!")
  set(GLOBAL_DEFINITIONS -DBUILD_IOS)
  set(OUTPUT_LIBRARY_TYPE STATIC)
endif()

set(CMAKE_C_FLAGS "-fexceptions -Wstack-protector -fstack-protector ${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wincompatible-pointer-types-discards-qualifiers -w -fexceptions -fstack-protector -Wstack-protector")



#
#
#

add_subdirectory(${ROOT_PATH}/NBMAlgorithms)
add_subdirectory(${ROOT_PATH}/NBMStructures)
add_subdirectory(${ROOT_PATH}/NBMImageConveniences)
add_subdirectory(${ROOT_PATH}/NBMDemos)
