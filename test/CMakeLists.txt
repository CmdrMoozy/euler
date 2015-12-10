set(euler-test_SOURCES

	euler-test.cpp

	euler/ECircularPrimeSieveTest.cpp
	euler/EFastTotientTest.cpp
	euler/ENumberGridTest.cpp
	euler/ETriangleStructureTest.cpp

	geodesy/EGeoCoordTest.cpp

	graph/GraphTest.cpp

	math/EFactorizationTest.cpp
	math/EMathTest.cpp
	math/EPrimeSieveTest.cpp
	math/MathTest.cpp

	structs/EGridTest.cpp

	types/EDigitIntegerTest.cpp
	types/ETriangleTest.cpp

	util/EArrayTest.cpp
	util/EArrayUtilitiesTest.cpp
	util/EBitwiseTest.cpp
	util/EByteArrayTest.cpp

)

add_executable(euler-test ${euler-test_SOURCES})
target_link_libraries(euler-test ${euler_LIBRARIES} euler)
add_test(euler-test euler-test)
