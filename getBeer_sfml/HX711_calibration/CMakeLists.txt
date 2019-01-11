cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

#Change the name "getBeer" to whatever you want
project(getBeer VERSION 1.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")


# Specify default build type if none provided (before project() command)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
message(STATUS "Build type set to ${CMAKE_BUILD_TYPE}")

# Edit the subdirectories as needed
set(executable hxCalibrationX)
include_directories(
  # "${PROJECT_SOURCE_DIR}/include"
  # "${PROJECT_SOURCE_DIR}/src"
  )

add_executable(${executable}
  hx711.h
  hx711.cpp
  main.cpp
  )

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  message(STATUS "Configuring on/for Windows")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
endif()

target_link_libraries(${executable} -pthread -lwiringPi -lcrypt -lrt)
