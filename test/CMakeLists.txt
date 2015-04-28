find_package(DWARF REQUIRED)

set(test_SOURCES

	Test.cpp

	tests/math/MathTest.cpp
	tests/math/MathTest.h

)

include_directories(${CMAKE_SOURCE_DIR}/vrfy/src)

add_executable(Test ${test_SOURCES})
target_link_libraries(Test ${euler_LIBRARIES} euler ${Vrfy_LIBS})
