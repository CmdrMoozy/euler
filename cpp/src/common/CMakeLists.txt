SET(euler-common_SOURCES

	EDefines.h

	euler/ESudoku.cpp
	euler/ESudoku.h

	math/EExactCover.cpp
	math/EExactCover.h

	util/Bitwise.cpp
	util/Bitwise.hpp
	util/EBitwise.cpp
	util/EBitwise.h
	util/Path.cpp
	util/Path.hpp
	util/Process.cpp
	util/Process.hpp

)

ADD_LIBRARY(euler-common STATIC ${euler-common_SOURCES})
TARGET_LINK_LIBRARIES(euler-common ${euler_LIBRARIES})
