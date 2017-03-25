set(euler-test_SOURCES

	euler-test.cpp

	graph/GraphTest.cpp

	math/EMathTest.cpp
	math/EPrimeSieveTest.cpp
	math/MathTest.cpp

	structs/BitArrayTest.cpp

	types/EFractionTest.cpp

	util/BitwiseTest.cpp
	util/EBitwiseTest.cpp

)

add_executable(euler-test ${euler-test_SOURCES})
target_link_libraries(euler-test ${euler_LIBRARIES} euler-common)
add_test(euler-test euler-test)
