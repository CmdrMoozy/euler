SET(euler-common_SOURCES

	EDefines.h
	EExceptions.cpp
	EExceptions.h

	euler/ECircularPrimeSieve.cpp
	euler/ECircularPrimeSieve.h
	euler/EPoker.cpp
	euler/EPoker.h
	euler/ESpiral.cpp
	euler/ESpiral.h
	euler/ESudoku.cpp
	euler/ESudoku.h
	euler/GridGraphUtils.cpp
	euler/GridGraphUtils.h

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
	structs/BitIterator.hpp

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
	util/Bitwise.cpp
	util/Bitwise.hpp
	util/EArray.h
	util/EArrayUtilities.h
	util/EBitwise.cpp
	util/EBitwise.h
	util/Path.cpp
	util/Path.hpp
	util/Process.cpp
	util/Process.hpp
	util/EString.cpp
	util/EString.h

)

ADD_LIBRARY(euler-common STATIC ${euler-common_SOURCES})
TARGET_LINK_LIBRARIES(euler-common ${euler_LIBRARIES})
