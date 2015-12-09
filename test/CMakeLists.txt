set(euler-test_SOURCES

	euler-test.cpp

	graph/GraphTest.cpp

	math/EMathTest.cpp
	math/EPrimeSieveTest.cpp
	math/MathTest.cpp

	types/EDigitIntegerTest.cpp

	util/EArrayTest.cpp
	util/EBitwiseTest.cpp
	util/EByteArrayTest.cpp

)

add_executable(euler-test ${euler-test_SOURCES})
target_link_libraries(euler-test ${euler_LIBRARIES} euler)
add_test(euler-test euler-test)
