// ConsoleApplication2.cpp: главный файл проекта.

#include "stdafx.h"

#include "mpi.h"

#include <cstdlib>

#include <iostream>

using namespace std;

int main(int argc, char * argv[])

{

	int rank, size, resultlen;

	char name[MPI_MAX_PROCESSOR_NAME];

	MPI_Init(&argc, &argv);

	int res = 1;

	MPI_Comm_size(MPI_COMM_WORLD, &size);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Get_processor_name(name, &resultlen);

	while (res >0)

	{

		if (rank == 0)

		{

			printf("Enter a digit(0 or less to exit): ");

			cin >> res;

		}

		MPI_Bcast(&res, 1, MPI_INT, 0, MPI_COMM_WORLD);

		printf("Process %d of %d (%s) got %d\n", rank, size, name, res);

		fflush(stdout);

		MPI_Barrier(MPI_COMM_WORLD);

	}

	MPI_Finalize();

	return 0;

}