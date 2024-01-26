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
