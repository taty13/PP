// ConsoleApplication1.cpp: главный файл проекта.
// pp-lb1.cpp: главный файл проекта.
#include "stdafx.h"
#include "mpi.h"
#include <stdio.h>
using namespace System;
int main(int argc, char* argv[])
{
	int rank, size, resultlen;
	double startwtime = 0.0, endwtime;
	char name[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc, &argv);
	startwtime = MPI_Wtime();
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(name, &resultlen);
	endwtime = MPI_Wtime();
	printf("Hello world from process %d of %d at %s as %f second \n", rank, size, name,
		endwtime - startwtime);
	printf("Changes done");
	MPI_Finalize();
	return 0;
}