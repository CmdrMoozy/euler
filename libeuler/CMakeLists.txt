SET(euler_HEADERS

	src/libeuler/EDefines.h
	src/libeuler/EExceptions.h

	src/libeuler/euler/ECircularPrimeSieve.h
	src/libeuler/euler/EFastTotient.h
	src/libeuler/euler/ENumberGrid.h
	src/libeuler/euler/EPoker.h
	src/libeuler/euler/ESpiral.h
	src/libeuler/euler/ESudoku.h
	src/libeuler/euler/ETriangleStructure.h

	src/libeuler/geodesy/EGeoCoord.h
	src/libeuler/geodesy/ELatLonValue.h

	src/libeuler/graph/Edge.h
	src/libeuler/graph/EGridGraph.h
	src/libeuler/graph/EGridVertex.h
	src/libeuler/graph/Graph.h
	src/libeuler/graph/Vertex.h

	src/libeuler/math/EExactCover.h
	src/libeuler/math/EFactorization.h
	src/libeuler/math/EMath.h
	src/libeuler/math/Math.h
	src/libeuler/math/EPrimeSieve.h

	src/libeuler/structs/EGrid.h
	src/libeuler/structs/EHashMap.h
	src/libeuler/structs/Hash.h

	src/libeuler/types/EBigInteger.h
	src/libeuler/types/EDigitInteger.h
	src/libeuler/types/EFraction.h
	src/libeuler/types/ERightTriangle.h
	src/libeuler/types/ERomanNumeral.h
	src/libeuler/types/ETriangle.h

	src/libeuler/util/AbsoluteValue.h
	src/libeuler/util/EArray.h
	src/libeuler/util/EArrayUtilities.h
	src/libeuler/util/EBitwise.h
	src/libeuler/util/EByteArray.h
	src/libeuler/util/EDate.h
	src/libeuler/util/Profiler.h
	src/libeuler/util/EString.h
	src/libeuler/util/ScopeExit.h

)

SET(euler_SOURCES

	src/libeuler/EExceptions.cpp

	src/libeuler/euler/ECircularPrimeSieve.cpp
	src/libeuler/euler/EFastTotient.cpp
	src/libeuler/euler/ENumberGrid.cpp
	src/libeuler/euler/EPoker.cpp
	src/libeuler/euler/ESpiral.cpp
	src/libeuler/euler/ESudoku.cpp
	src/libeuler/euler/ETriangleStructure.cpp

	src/libeuler/geodesy/EGeoCoord.cpp
	src/libeuler/geodesy/ELatLonValue.cpp

	src/libeuler/graph/Edge.cpp
	src/libeuler/graph/EGridGraph.cpp
	src/libeuler/graph/EGridVertex.cpp
	src/libeuler/graph/Graph.cpp
	src/libeuler/graph/Vertex.cpp

	src/libeuler/math/EExactCover.cpp
	src/libeuler/math/EFactorization.cpp
	src/libeuler/math/EMath.cpp
	src/libeuler/math/Math.cpp
	src/libeuler/math/EPrimeSieve.cpp

	src/libeuler/structs/Hash.cpp

	src/libeuler/types/EBigInteger.cpp
	src/libeuler/types/EDigitInteger.cpp
	src/libeuler/types/EFraction.cpp
	src/libeuler/types/ERightTriangle.cpp
	src/libeuler/types/ERomanNumeral.cpp
	src/libeuler/types/ETriangle.cpp

	src/libeuler/util/EBitwise.cpp
	src/libeuler/util/EByteArray.cpp
	src/libeuler/util/EDate.cpp
	src/libeuler/util/Profiler.cpp
	src/libeuler/util/EString.cpp

)

SET(eulertest_SOURCES

	src/libeuler/ETests.cpp

)

ADD_LIBRARY(euler SHARED ${euler_SOURCES})
TARGET_LINK_LIBRARIES(euler ${euler_LIBRARIES})

IF(CMAKE_BUILD_TYPE_LOWER MATCHES debug)
	ADD_EXECUTABLE(ETests ${eulertest_SOURCES})
	TARGET_LINK_LIBRARIES(ETests euler)
ENDIF()
