cmake_minimum_required(VERSION 3.0.2)
project(euler)

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)

set(CMAKE_MODULE_PATH

	${PROJECT_SOURCE_DIR}/3rdparty/cmu/cmake/modules
	${PROJECT_SOURCE_DIR}/cmake
	${PROJECT_SOURCE_DIR}/vrfy/CMake

)

# Note which type of build we're performing.

if(NOT CMAKE_BUILD_TYPE)
	message(STATUS "No CMAKE_BUILD_TYPE specified; defaulting to Release.")
	set(CMAKE_BUILD_TYPE "Release")
endif()

string(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_LOWER)

# Includ extra CMake functions.

include(${CMAKE_SOURCE_DIR}/cmake/Functions.cmake)

# Find our dependencies.

find_package(GMP REQUIRED)
find_package(MPFR REQUIRED)
find_package(RE2 REQUIRED)

# Setup our compile flags.

include(${CMAKE_SOURCE_DIR}/3rdparty/cmu/cmake/SetFlags.cmake)
cmuSetCompileFlags()

add_definitions(-DEULER_SOURCE_DIR="${CMAKE_SOURCE_DIR}")
add_definitions(-DEULER_BINARY_DIR="${CMAKE_BINARY_DIR}")

if(CMAKE_BUILD_TYPE_LOWER MATCHES debug)
	add_definitions(-DLIBEULER_DEBUG)
endif()

include_directories(3rdparty/include src)

# Set the libraries we'll use.

set(euler_LIBRARIES

	m
	rt
	pthread
	${GMP_LIBRARIES}
	${GMPXX_LIBRARIES}
	${MPFR_LIBRARIES}
	${RE2_LIBRARIES}

)

# Add our targets.

enable_testing()

add_subdirectory(src/common)
add_subdirectory(src/done)
add_subdirectory(src/new)
add_subdirectory(src/run)
add_subdirectory(src/test)
