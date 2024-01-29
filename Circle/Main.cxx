#include <iostream>
#include <string>

#include "mpi.h"

int main(int argc, char* argv[])
{
	std::string message = "Hello, ";

	const auto kMessageTag = 0;

	char buffer[128];

	MPI_Init(&argc, &argv);

	auto currentProcessId = -1;

	MPI_Comm_rank(MPI_COMM_WORLD, &currentProcessId);

	auto numberOfProcesses = 0;

	MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcesses);

	MPI_Status status;

	if (currentProcessId == 0)
	{
		message += std::to_string(currentProcessId + 1);

		std::cout
			<< "Sending message \""
			<< message
			<< "\" from process with Id = "
			<< currentProcessId
			<< " to process with Id = "
			<< currentProcessId + 1
			<< std::endl;

		MPI_Send(
			message.c_str(),
			message.length() + 1,
			MPI_CHAR,
			currentProcessId + 1,
			kMessageTag,
			MPI_COMM_WORLD
		);

		MPI_Recv(
			static_cast<void*>(buffer),
			sizeof(buffer),
			MPI_CHAR,
			numberOfProcesses - 1,
			kMessageTag,
			MPI_COMM_WORLD,
			&status
		);

		std::cout
			<< "Recieved message \""
			<< buffer
			<< "\" by process with Id = "
			<< currentProcessId
			<< " from process with Id = "
			<< status.MPI_SOURCE
			<< std::endl;
	}
	else
	{
		MPI_Recv(
			static_cast<void*>(buffer),
			sizeof(buffer),
			MPI_CHAR,
			currentProcessId - 1,
			kMessageTag,
			MPI_COMM_WORLD,
			&status
		);

		std::cout
			<< "Recieved message \""
			<< buffer
			<< "\" by process with Id = "
			<< currentProcessId
			<< " from process with Id = "
			<< status.MPI_SOURCE
			<< std::endl;

		auto targetProcessId = currentProcessId + 1;

		if (targetProcessId >= numberOfProcesses)
			targetProcessId = 0;

		message += std::to_string(targetProcessId);

		std::cout
			<< "Sending message \""
			<< message
			<< "\" from process with Id = "
			<< currentProcessId
			<< " to process with Id = "
			<< targetProcessId
			<< std::endl;

		MPI_Send(
			message.c_str(),
			message.length() + 1,
			MPI_CHAR,
			targetProcessId,
			kMessageTag,
			MPI_COMM_WORLD
		);
	}

	MPI_Finalize();

	return 0;
}
