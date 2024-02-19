find_package(
	MPI

	REQUIRED
)

add_executable(
	Time

	Main.cxx
)

target_compile_features(
	Time

	PRIVATE
		cxx_std_17
)

target_include_directories(
	Time

	PRIVATE
		${MPI_CXX_INCLUDE_PATH}
)

target_link_libraries(
	Time

	PRIVATE
		${MPI_CXX_LIBRARIES}
)

# Running mpiexec after build

set(MPIEXEC_MAX_NUMPROCS 6)

add_custom_command(
	TARGET
		Time

	POST_BUILD

	COMMAND
		${MPIEXEC_EXECUTABLE}

		ARGS
			${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_MAX_NUMPROCS} Time
)