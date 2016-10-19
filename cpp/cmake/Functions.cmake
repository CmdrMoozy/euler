macro(eulerListSubdirectories result directory)
	file(GLOB children RELATIVE ${directory} ${directory}/*)
	set(subdirs "")
	foreach(child ${children})
		if(IS_DIRECTORY ${directory}/${child})
			list(APPEND subdirs ${child})
		endif()
	endforeach()
	set(${result} ${subdirs})
endmacro()

function(eulerAddSubdirectories)
	eulerListSubdirectories(PROBLEMS ${CMAKE_CURRENT_SOURCE_DIR})
	foreach(PROBLEM ${PROBLEMS})
		add_subdirectory(${PROBLEM})
	endforeach()
endfunction()

function(eulerAddProblem)
	set(problem_main "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
	get_filename_component(problem_SOURCES ${problem_main} NAME)
	get_filename_component(problem ${problem_main} DIRECTORY)
	get_filename_component(problem ${problem} NAME)

	# Add a target to build the executable.
	add_executable(${problem} ${problem_SOURCES})
	target_link_libraries(${PROBLEM} ${euler_LIBRARIES} euler-common)

	# Copy any supporting files to the build output directory.
	file(GLOB problem_DATA ${CMAKE_CURRENT_SOURCE_DIR}/*.txt)
	list(REMOVE_ITEM problem_DATA "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt")
	foreach(file ${problem_DATA})
		message(STATUS ${file})
		add_custom_command(TARGET ${problem} PRE_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy
			${file} $<TARGET_FILE_DIR:${problem}>)
	endforeach()
endfunction()
