SET(euler-common_SOURCES

	EDefines.h
	EExceptions.cpp
	EExceptions.h

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
	math/EMath.cpp
	math/EMath.h
	math/Math.cpp
	math/Math.hpp
	math/EPrimeSieve.cpp
	math/EPrimeSieve.h

	structs/BitArray.cpp
	structs/BitArray.hpp

	types/EFraction.cpp
	types/EFraction.h
	types/ERomanNumeral.cpp
	types/ERomanNumeral.h

	util/Bitwise.cpp
	util/Bitwise.hpp
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
