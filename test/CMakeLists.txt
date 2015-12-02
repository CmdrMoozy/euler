set(euler-test_SOURCES

	euler-test.cpp

	graph/GraphTest.cpp

	math/MathTest.cpp

)

add_executable(euler-test ${euler-test_SOURCES})
target_link_libraries(euler-test ${euler_LIBRARIES} euler)
add_test(euler-test euler-test)
