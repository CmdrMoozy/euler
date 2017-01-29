set(euler-test_SOURCES

	euler-test.cpp

	euler/ECircularPrimeSieveTest.cpp
	euler/EPokerTest.cpp
	euler/ESpiralTest.cpp

	graph/GraphTest.cpp

	math/EMathTest.cpp
	math/EPrimeSieveTest.cpp
	math/MathTest.cpp
	math/PrimeSieveTest.cpp

	structs/BitArrayTest.cpp
	structs/BitIteratorTest.cpp

	types/EDigitIntegerTest.cpp
	types/EFractionTest.cpp
	types/ERightTriangleTest.cpp
	types/ETriangleTest.cpp

	util/BitwiseTest.cpp
	util/EArrayUtilitiesTest.cpp
	util/EBitwiseTest.cpp

)

add_executable(euler-test ${euler-test_SOURCES})
target_link_libraries(euler-test ${euler_LIBRARIES} euler-common)
add_test(euler-test euler-test)
