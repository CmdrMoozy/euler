cmake_minimum_required(VERSION 3.0.2)
project(euler)

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/make)

# Note which type of build we're performing.

if(NOT CMAKE_BUILD_TYPE)
	message(STATUS "No CMAKE_BUILD_TYPE specified; defaulting to Release.")
	set(CMAKE_BUILD_TYPE "Release")
endif()

string(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_LOWER)

# Includ extra CMake functions.

include(${CMAKE_SOURCE_DIR}/make/Functions.cmake)

# Find our dependencies.

find_package(GMP REQUIRED)
find_package(MPFR REQUIRED)
find_package(PCRE REQUIRED)

# Setup our compile flags.

include(${CMAKE_SOURCE_DIR}/make/SetFlags.cmake)
eulerSetCompileFlags()

if(CMAKE_BUILD_TYPE_LOWER MATCHES debug)
	add_definitions(-DLIBEULER_DEBUG)
endif()

include_directories("${PROJECT_SOURCE_DIR}/libeuler/src")

# Set the libraries we'll use.

set(euler_LIBRARIES

	m
	rt
	pthread
	${GMP_LIBRARIES}
	${GMPXX_LIBRARIES}
	${MPFR_LIBRARIES}
	${PCRE_LIBRARIES}

)

add_subdirectory(libeuler)
add_subdirectory(done)
add_subdirectory(new)

if(CMAKE_BUILD_TYPE_LOWER MATCHES debug)
	add_subdirectory(vrfy)
endif()
