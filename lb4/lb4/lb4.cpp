// lb4.cpp: главный файл проекта.

//

#include "stdafx.h"

#include "mpi.h"

#include <cstdlib>

#include <iostream>

#include <cmath>

#include <malloc.h>

using namespace std;

int main(int argc, char * argv[])

{

	int rank, size, resultlen;

	double starttime, endtime;

	char name[MPI_MAX_PROCESSOR_NAME];

	MPI_Init(&argc, &argv);

	starttime = MPI_Wtime();

	MPI_Comm_size(MPI_COMM_WORLD, &size);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Get_processor_name(name, &resultlen);

	char check = '=';

	int memory = 1024;

	if (rank == 0) {

		int number = 0;

		for (int i = 0; i < strlen(argv[1]); i++)

		{

			number = (int)argv[1][i] - 48;

			memory = memory * 10 + number;

		}

	}

	MPI_Bcast(&memory, 1, MPI_INT, 0, MPI_COMM_WORLD);

	char * buffer = (char*)malloc(memory);

	MPI_Status status;

	if (rank == 0)

	{

		for (int i = 0; i < memory; i++)

			buffer[i] = (rand() % 26 + 'a');

		MPI_Send(buffer, memory, MPI_CHAR, rank + 1, 1, MPI_COMM_WORLD);

		MPI_Recv(buffer, memory, MPI_CHAR, size - 1, 1, MPI_COMM_WORLD, &status);

		if (buffer == NULL) exit(1);

		endtime = MPI_Wtime();

		printf("Process No %d from process %d: total time %.6f\n", rank, size - 1, endtime - starttime);

		fflush(stdout);

	}

	else {

		MPI_Recv(buffer, memory, MPI_CHAR, rank - 1, 1, MPI_COMM_WORLD, &status);

		if (buffer == NULL) exit(1);

		endtime = MPI_Wtime();

		printf("Process No %d got %d bytes from process %d: %.6f\n", rank, memory, rank - 1, endtime - starttime);

		fflush(stdout);

		if (rank == size - 1)

			MPI_Send(buffer, memory, MPI_CHAR, 0, 1, MPI_COMM_WORLD);

		else MPI_Send(buffer, memory, MPI_CHAR, rank + 1, 1, MPI_COMM_WORLD);

	}

	MPI_Finalize();

	free(buffer);

}