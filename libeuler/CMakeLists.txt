####################################################################################################################
#
# This is the CMake build file for libeuler. The build process can be controlled in several ways:
#
#     - To enable "release" or "debug" builds, CMake should be instantiated as follows:
#
#           cmake -DCMAKE_BUILD_TYPE=Release ..		(This is the default, if neither is selected.)
#           cmake -DCMAKE_BUILD_TYPE=Debug ..
#
####################################################################################################################

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.9)
PROJECT(euler)

SET(CMAKE_COLOR_MAKEFILE ON)
SET(CMAKE_VERBOSE_MAKEFILE OFF)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

# Locate our dependencies.

FIND_PACKAGE(GMP REQUIRED)
FIND_PACKAGE(MPFR REQUIRED)

# Set INCLUDE and C(XX)FLAGS

IF(NOT CMAKE_BUILD_TYPE)
	MESSAGE(STATUS "No CMAKE_BUILD_TYPE specified; defaulting to Release mode.")
	SET(CMAKE_BUILD_TYPE "Release")
ENDIF()

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -ansi -pedantic -Wshadow -Wpointer-arith -Wcast-qual -std=c++0x -O0")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -ansi -pedantic -Wshadow -Wpointer-arith -Wcast-qual -std=c++0x -fomit-frame-pointer")

STRING(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_LOWER)
IF(CMAKE_BUILD_TYPE_LOWER MATCHES debug)
	ADD_DEFINITIONS(-DLIBEULER_DEBUG)
ENDIF()

INCLUDE_DIRECTORIES("src")

# Define our list of sources.

SET(euler_HEADERS
	
	src/EDefines.h
	src/EExceptions.h
	
	src/euler/ECircularPrimeSieve.h
	src/euler/EFastTotient.h
	src/euler/ENumberGrid.h
	src/euler/EPoker.h
	src/euler/ESpiral.h
	src/euler/ESudoku.h
	src/euler/ETriangleStructure.h
	
	src/geodesy/EGeoCoord.h
	src/geodesy/ELatLonValue.h
	
	src/graph/EGridGraph.h
	src/graph/EGridVertex.h
	
	src/math/EExactCover.h
	src/math/EFactorization.h
	src/math/EMath.h
	src/math/EPrimeSieve.h
	
	src/structs/EGrid.h
	src/structs/EHashMap.h
	
	src/types/EBigInteger.h
	src/types/EDigitInteger.h
	src/types/EFraction.h
	src/types/ERightTriangle.h
	src/types/ETriangle.h
	
	src/util/EArray.h
	src/util/EArrayUtilities.h
	src/util/EBitwise.h
	src/util/EByteArray.h
	src/util/EDate.h
	src/util/EProfiler.h
	src/util/EString.h
	
)

SET(euler_SOURCES
	
	src/EExceptions.cpp
	
	src/euler/ECircularPrimeSieve.cpp
	src/euler/EFastTotient.cpp
	src/euler/ENumberGrid.cpp
	src/euler/EPoker.cpp
	src/euler/ESpiral.cpp
	src/euler/ESudoku.cpp
	src/euler/ETriangleStructure.cpp
	
	src/geodesy/EGeoCoord.cpp
	src/geodesy/ELatLonValue.cpp
	
	src/graph/EGridGraph.cpp
	src/graph/EGridVertex.cpp
	
	src/math/EExactCover.cpp
	src/math/EFactorization.cpp
	src/math/EMath.cpp
	src/math/EPrimeSieve.cpp
	
	src/types/EBigInteger.cpp
	src/types/EDigitInteger.cpp
	src/types/EFraction.cpp
	src/types/ERightTriangle.cpp
	src/types/ETriangle.cpp
	
	src/util/EBitwise.cpp
	src/util/EByteArray.cpp
	src/util/EDate.cpp
	src/util/EProfiler.cpp
	src/util/EString.cpp
	
)

SET(eulertest_SOURCES
	
	src/ETests.cpp
	
)

# Build our library.

ADD_LIBRARY(euler SHARED ${euler_SOURCES})
TARGET_LINK_LIBRARIES(euler m rt gmp gmpxx mpfr)

# If building in debug mode, build our test suite.

STRING(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_LOWER)
IF(CMAKE_BUILD_TYPE_LOWER MATCHES debug)
	ADD_EXECUTABLE(ETests ${eulertest_SOURCES})
	TARGET_LINK_LIBRARIES(ETests euler)
ENDIF()
