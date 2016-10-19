set(euler-run_SOURCES

	euler-run.cpp

)

add_executable(euler-run ${euler-run_SOURCES})
target_link_libraries(euler-run ${euler_LIBRARIES} euler-common)
add_test(euler-run euler-run)
