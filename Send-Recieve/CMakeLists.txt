find_package(
	MPI

	REQUIRED
)

add_executable(
	Send-Recieve

	Main.cxx
)

target_compile_features(
	Send-Recieve

	PRIVATE
		cxx_std_17
)

target_include_directories(
	Send-Recieve

	PRIVATE
		${MPI_CXX_INCLUDE_PATH}
)

target_link_libraries(
	Send-Recieve

	PRIVATE
		${MPI_CXX_LIBRARIES}
)



# Running mpiexec after

set(MPIEXEC_MAX_NUMPROCS 2)

add_custom_command(
	TARGET
		Send-Recieve

	POST_BUILD

	COMMAND
		${MPIEXEC_EXECUTABLE}

		ARGS
			${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_MAX_NUMPROCS} ./Send-Recieve
)