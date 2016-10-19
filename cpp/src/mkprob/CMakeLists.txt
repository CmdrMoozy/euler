set(euler-mkprob_SOURCES

	euler-mkprob.cpp

)

add_executable(euler-mkprob ${euler-mkprob_SOURCES})
target_link_libraries(euler-mkprob ${euler_LIBRARIES} euler-common)
