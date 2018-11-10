cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

#Change the name "game" to whatever you want
project(game VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}-static-libgcc -static-libstdc++")

# Edit the subdirectories as needed
include_directories(${PROJECT_BINARY_DIR})

add_executable(game
  src/Dispenser.cpp
  include/Dispenser.hpp
  main.cpp
  )

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  message(STATUS "Configuring on/for Windows")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
endif()

# Specify default build type if none provided (before project() command)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# Configuration options
# Remember to specify -DSFML_DIR="D:/lib/SFML" (install directory of SFML)

set(SFML_STATIC_LIBRARIES TRUE CACHE BOOL "Use static SFML librares")

# Add directory containing FindSFML.cmake to module path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/;${CMAKE_MODULE_PATH}")

find_package(SFML 2.5 COMPONENTS audio graphics window network system REQUIRED)

# If found, include and link; otherwise output error message
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  message("${SFML_INCLUDE_DIR}")
else()
  set(SFML_ROOT "" CACHE PATH "")
  message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
  message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()



# Linking to all the libraries, for simplicity
target_link_libraries(game sfml-audio sfml-graphics sfml-network sfml-window sfml-system)

# Remember to set -DCMAKE_INSTALL_PREFIX="where_you_want_it_installed" if using install()
