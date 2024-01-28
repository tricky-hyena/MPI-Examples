#include <iostream>

#include "mpi.h"

enum class ProcessId
{
	kUndefined = -1,
	kFirst,
	kSecond,
};

const auto kMessageTag = 0;

char buffer[128];

const char kMessage[] = "Hello, world!";

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);

	auto currentProcessId = -1;

	MPI_Comm_rank(MPI_COMM_WORLD, &currentProcessId);

	switch (static_cast<ProcessId>(currentProcessId))
	{
		case ProcessId::kFirst:
		{
			std::cout
					<< "Sending message \""
					<< kMessage
					<< "\" to process with Id = "
					<< static_cast<int>(ProcessId::kSecond)
					<< std::endl;
			
			MPI_Send(
				kMessage,
				sizeof(kMessage),
				MPI_CHAR,
				static_cast<int>(ProcessId::kSecond),
				kMessageTag,
				MPI_COMM_WORLD
			);

			break;
		}
		
		case ProcessId::kSecond:
		{
			MPI_Status status;

			MPI_Recv(
				static_cast<void*>(buffer),
				sizeof(buffer),
				MPI_CHAR,
				static_cast<int>(ProcessId::kFirst),
				kMessageTag,
				MPI_COMM_WORLD,
				&status);

			std::cout
				<< "Recieving message "
				<< "from process with Id = "
				<< status.MPI_SOURCE
				<< std::endl;

			std::cout
				<< "Recieved message: \""
				<< buffer
				<< "\"\n\n";

			break;
		}

		default:
		{
			std::cerr
				<< "Undefined process with Id = "
				<< static_cast<int>(currentProcessId)
				<< std::endl;
		}
	}

	MPI_Finalize();

	return 0;
}
