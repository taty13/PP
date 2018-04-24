#include "stdafx.h"
#include "mpi.h"
#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std;



int main(int  argc, char * argv[])
{
	const double pi = 3.1415926535897932;
	int rank, size, resultlen;
	double starttime, endtime;
	double sum;
	char name[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc, &argv);
	int n = 1;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Get_processor_name(name, &resultlen);
	printf("Process %d of %d start on %s\n", rank, size, name, n);
	MPI_Barrier(MPI_COMM_WORLD);
	fflush(stdout);
	for (;;)
	{
		if (rank == 0)
		{
			printf("Enter intervals (0 or less to exit): ");
			cin >> n;
		}
		MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
		if (n <= 0) break;
		sum = 0;
		double h = 2 * n;
		int i = rank + 1;
		double x = 0;
		starttime = MPI_Wtime();
		while (i < n)
		{
			x = (2 * i - 1) / h;
			sum = sum + 4 / (1 + pow(x, 2));
			i = i + size;
		}
		MPI_Barrier(MPI_COMM_WORLD);
		double result = 0;
		MPI_Reduce(&sum, &result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
		endtime = MPI_Wtime();
		if (rank == 0)
		{
			result = (double)1 / n * result;
			printf("pi = %.16f, error pi = %.16f\n work time: %.6f\n", result, abs(pi - result), endtime - starttime);
		}
		fflush(stdout);
	}
	MPI_Finalize();
}
