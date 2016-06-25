SET(euler-common_SOURCES

	EDefines.h
	EExceptions.cpp
	EExceptions.h

	euler/ECircularPrimeSieve.cpp
	euler/ECircularPrimeSieve.h
	euler/EFastTotient.cpp
	euler/EFastTotient.h
	euler/ENumberGrid.cpp
	euler/ENumberGrid.h
	euler/EPoker.cpp
	euler/EPoker.h
	euler/ESpiral.cpp
	euler/ESpiral.h
	euler/ESudoku.cpp
	euler/ESudoku.h
	euler/ETriangleStructure.cpp
	euler/ETriangleStructure.h
	euler/GridGraphUtils.cpp
	euler/GridGraphUtils.h

	geodesy/EGeoCoord.cpp
	geodesy/EGeoCoord.h
	geodesy/ELatLonValue.cpp
	geodesy/ELatLonValue.h

	graph/astar.cpp
	graph/astar.h
	graph/dijkstra.cpp
	graph/dijkstra.h
	graph/Edge.cpp
	graph/Edge.h
	graph/Graph.cpp
	graph/Graph.h
	graph/Vertex.cpp
	graph/Vertex.h

	math/EExactCover.cpp
	math/EExactCover.h
	math/EFactorization.cpp
	math/EFactorization.h
	math/EMath.cpp
	math/EMath.h
	math/Math.cpp
	math/Math.hpp
	math/EPrimeSieve.cpp
	math/EPrimeSieve.h
	math/PrimeSieve.cpp
	math/PrimeSieve.hpp

	string/Util.cpp
	string/Util.hpp

	structs/BitArray.cpp
	structs/BitArray.hpp
	structs/EGrid.h

	types/BigDecimal.cpp
	types/BigDecimal.hpp
	types/EBigInteger.cpp
	types/EBigInteger.h
	types/EDigitInteger.cpp
	types/EDigitInteger.h
	types/EFraction.cpp
	types/EFraction.h
	types/ERightTriangle.cpp
	types/ERightTriangle.h
	types/ERomanNumeral.cpp
	types/ERomanNumeral.h
	types/ETriangle.cpp
	types/ETriangle.h

	util/AbsoluteValue.h
	util/benchmark.cpp
	util/benchmark.hpp
	util/Bitwise.cpp
	util/Bitwise.hpp
	util/EArray.h
	util/EArrayUtilities.h
	util/EBitwise.cpp
	util/EBitwise.h
	util/EDate.cpp
	util/EDate.h
	util/Path.cpp
	util/Path.hpp
	util/Process.cpp
	util/Process.hpp
	util/Profiler.cpp
	util/Profiler.hpp
	util/EString.cpp
	util/EString.h

)

ADD_LIBRARY(euler-common STATIC ${euler-common_SOURCES})
TARGET_LINK_LIBRARIES(euler-common ${euler_LIBRARIES})
