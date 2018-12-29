cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

#Change the name "dispenser" to whatever you want
project(dispenser VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")

# Specify default build type if none provided (before project() command)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
message(STATUS "Build type set to ${CMAKE_BUILD_TYPE}")

# Install setup (TODO)
message(STATUS "Project will be installed to ${CMAKE_INSTALL_PREFIX}")
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
  ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
  ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
  ${PROJECT_BINARY_DIR}/..)

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR} CACHE PATH "Installation directory for libraries")
set(INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR} CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR} CACHE PATH "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKEDIR CMake)
else()
  set(DEF_INSTALL_CMAKEDIR share/cmake/${PROJECT_NAME})
endif()
set(INSTALL_CMAKEDIR ${DEF_INSTALL_CMAKEDIR} CACHE PATH "Installation directory for CMake files")

# Report to user
foreach(p LIB BIN INCLUDE CMAKE)
  file(TO_NATIVE_PATH ${CMAKE_INSTALL_PREFIX}/${INSTALL_${p}DIR} _path )
  # message(STATUS "Installing ${p} components to ${_path}")
  unset(_path)
endforeach()

# Edit the subdirectories as needed

set(MAINSRC main.cpp)
set(executable getBeerX)
include_directories(
  "${PROJECT_SOURCE_DIR}/include"
  "${PROJECT_SOURCE_DIR}/src"
  )

add_executable(${executable}
  include/ValveOperator.hpp
  src/ValveOperator.cpp
  include/Valve.hpp
  src/Valve.cpp
  include/ResourceHolder.hpp
  include/ResourceHolder.inl
  include/ResourceIdentifiers.hpp
  include/StateIdentifiers.hpp
  include/App.hpp
  src/App.cpp
  main.cpp
  )

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  message(STATUS "Configuring on/for Windows")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
endif()


# Configuration options
# Remember to specify -DSFML_DIR="D:/lib/SFML" (install directory of SFML)

# set(SFML_STATIC_LIBRARIES TRUE CACHE BOOL "Use static SFML librares")

# Add directory containing FindSFML.cmake to module path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake/;${CMAKE_MODULE_PATH}")

find_package(SFML 2.5.1 COMPONENTS audio graphics window network system REQUIRED)

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
target_link_libraries(${executable} sfml-audio sfml-graphics sfml-network sfml-window sfml-system -lcppgpio)

# Remember to set -DCMAKE_INSTALL_PREFIX="where_you_want_it_installed" if using install()
