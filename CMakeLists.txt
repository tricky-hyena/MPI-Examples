﻿cmake_minimum_required(
	VERSION
		3.8
)

project(
	MPI-Examples

	LANGUAGES
		CXX
)

add_subdirectory(
	Send-Recieve/
)

add_subdirectory(
	Circle/
)

add_subdirectory(
	Time/
)
