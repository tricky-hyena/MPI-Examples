find_package(
	MPI

	REQUIRED
)

add_executable(
	Circle

	Main.cxx
)

target_compile_features(
	Circle

	PRIVATE
		cxx_std_17
)

target_include_directories(
	Circle

	PRIVATE
		${MPI_CXX_INCLUDE_PATH}
)

target_link_libraries(
	Circle

	PRIVATE
		${MPI_CXX_LIBRARIES}
)

# Running mpiexec after build

set(MPIEXEC_MAX_NUMPROCS 20)

add_custom_command(
	TARGET
		Circle

	POST_BUILD

	COMMAND
		${MPIEXEC_EXECUTABLE}

		ARGS
			${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_MAX_NUMPROCS} Circle
)