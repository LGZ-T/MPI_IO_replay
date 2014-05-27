#define _GNU_SOURCE // for clock_gettime, must be placed at the head of file!
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <mpi.h>

#define BUFS 1024*1024*100
#define HANDLES 100000

struct timespec begin, end, dur;
MPI_Datatype datatype[HANDLES];
MPI_File fh[HANDLES];
MPI_Request request[HANDLES];
MPI_Status status, array_of_statuses[HANDLES];
#define AS 300000
int array_of_gsizes_arraystore[AS], array_of_distribs_arraystore[AS], array_of_dargs_arraystore[AS], array_of_psizes_arraystore[AS], array_of_sizes_arraystore[AS], array_of_subsizes_arraystore[AS], array_of_starts_arraystore[AS], array_of_blocklengths_arraystore[AS], array_of_displacements_arraystore[AS], array_of_types_arraystore[AS];
int f_count, procs, myrank;
int size, rank;
unsigned long f_offset;
char sendbuf[BUFS], recvbuf[BUFS], buf[BUFS], buffer[BUFS];

int main(int argc,char *argv[])
{
	MPI_Init(&argc,&argv);
	clock_gettime(CLOCK_MONOTONIC, &begin);
	MPI_Comm_size(MPI_COMM_WORLD,&procs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);

	printf("Process %d running...\n", myrank);

	if (myrank == 0) {
		for(long int i=0; i<641; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<298; i++); /* Simulate compute time */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		for(long int i=0; i<9473; i++); /* Simulate compute time */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		for(long int i=0; i<1090; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 13, MPI_INT, 0, MPI_COMM_WORLD);

		for(long int i=0; i<61; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 5, MPI_CHAR, 0, MPI_COMM_WORLD);

		for(long int i=0; i<20164701; i++); /* Simulate compute time */

		MPI_Type_contiguous(4096, MPI_BYTE, &datatype[1]);

		for(long int i=0; i<1996; i++); /* Simulate compute time */

		MPI_Type_commit(&datatype[1]);

		for(long int i=0; i<1484; i++); /* Simulate compute time */

		MPI_Type_create_subarray(2, (array_of_sizes_arraystore[0] = 480,array_of_sizes_arraystore[1] = 484,array_of_sizes_arraystore), (array_of_subsizes_arraystore[0] = 120,array_of_subsizes_arraystore[1] = 124,array_of_subsizes_arraystore), (array_of_starts_arraystore[0] = 0,array_of_starts_arraystore[1] = 4,array_of_starts_arraystore), 0, datatype[1], &datatype[2]);

		for(long int i=0; i<80; i++); /* Simulate compute time */

		MPI_Type_commit(&datatype[2]);

		for(long int i=0; i<3796; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(long int i=0; i<150033; i++); /* Simulate compute time */

		MPI_File_open(MPI_COMM_SELF, "tile", 2, MPI_INFO_NULL, &(fh[1]));

		for(long int i=0; i<1403; i++); /* Simulate compute time */

		MPI_File_set_view(fh[1], 0, datatype[1], datatype[2], "native", MPI_INFO_NULL);

		for(long int i=0; i<151; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(long int i=0; i<639; i++); /* Simulate compute time */

		MPI_File_read(fh[1], buf, 14400, datatype[1], &status);

		for(long int i=0; i<549; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(long int i=0; i<1353; i++); /* Simulate compute time */

		MPI_File_close(&(fh[1]));

		for(long int i=0; i<335; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<22715; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<104; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<71; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<79; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<13371; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<64; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<63; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<62; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<66; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<3739; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<66; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<71; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<56; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<70; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	}

	if (myrank == 1) {
		for(long int i=0; i<641; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<298; i++); /* Simulate compute time */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		for(long int i=0; i<9473; i++); /* Simulate compute time */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		for(long int i=0; i<1090; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 13, MPI_INT, 0, MPI_COMM_WORLD);

		for(long int i=0; i<61; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 5, MPI_CHAR, 0, MPI_COMM_WORLD);

		for(long int i=0; i<20164701; i++); /* Simulate compute time */

		MPI_Type_contiguous(4096, MPI_BYTE, &datatype[1]);

		for(long int i=0; i<1996; i++); /* Simulate compute time */

		MPI_Type_commit(&datatype[1]);

		for(long int i=0; i<1484; i++); /* Simulate compute time */

		MPI_Type_create_subarray(2, (array_of_sizes_arraystore[0] = 480,array_of_sizes_arraystore[1] = 484,array_of_sizes_arraystore), (array_of_subsizes_arraystore[0] = 120,array_of_subsizes_arraystore[1] = 124,array_of_subsizes_arraystore), (array_of_starts_arraystore[0] = 0,array_of_starts_arraystore[1] = 4,array_of_starts_arraystore), 0, datatype[1], &datatype[2]);

		for(long int i=0; i<80; i++); /* Simulate compute time */

		MPI_Type_commit(&datatype[2]);

		for(long int i=0; i<3796; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(long int i=0; i<150033; i++); /* Simulate compute time */

		MPI_File_open(MPI_COMM_SELF, "tile", 2, MPI_INFO_NULL, &(fh[1]));

		for(long int i=0; i<1403; i++); /* Simulate compute time */

		MPI_File_set_view(fh[1], 0, datatype[1], datatype[2], "native", MPI_INFO_NULL);

		for(long int i=0; i<151; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(long int i=0; i<639; i++); /* Simulate compute time */

		MPI_File_read(fh[1], buf, 14400, datatype[1], &status);

		for(long int i=0; i<549; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(long int i=0; i<1353; i++); /* Simulate compute time */

		MPI_File_close(&(fh[1]));

		for(long int i=0; i<335; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<22715; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<104; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<71; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<79; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<13371; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<64; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<63; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<62; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<66; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<3739; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<66; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<71; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<56; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<70; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	}

	if (myrank == 2) {
		for(long int i=0; i<641; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<298; i++); /* Simulate compute time */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		for(long int i=0; i<9473; i++); /* Simulate compute time */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		for(long int i=0; i<1090; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 13, MPI_INT, 0, MPI_COMM_WORLD);

		for(long int i=0; i<61; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 5, MPI_CHAR, 0, MPI_COMM_WORLD);

		for(long int i=0; i<20164701; i++); /* Simulate compute time */

		MPI_Type_contiguous(4096, MPI_BYTE, &datatype[1]);

		for(long int i=0; i<1996; i++); /* Simulate compute time */

		MPI_Type_commit(&datatype[1]);

		for(long int i=0; i<1484; i++); /* Simulate compute time */

		MPI_Type_create_subarray(2, (array_of_sizes_arraystore[0] = 480,array_of_sizes_arraystore[1] = 484,array_of_sizes_arraystore), (array_of_subsizes_arraystore[0] = 120,array_of_subsizes_arraystore[1] = 124,array_of_subsizes_arraystore), (array_of_starts_arraystore[0] = 0,array_of_starts_arraystore[1] = 4,array_of_starts_arraystore), 0, datatype[1], &datatype[2]);

		for(long int i=0; i<80; i++); /* Simulate compute time */

		MPI_Type_commit(&datatype[2]);

		for(long int i=0; i<3796; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(long int i=0; i<150033; i++); /* Simulate compute time */

		MPI_File_open(MPI_COMM_SELF, "tile", 2, MPI_INFO_NULL, &(fh[1]));

		for(long int i=0; i<1403; i++); /* Simulate compute time */

		MPI_File_set_view(fh[1], 0, datatype[1], datatype[2], "native", MPI_INFO_NULL);

		for(long int i=0; i<151; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(long int i=0; i<639; i++); /* Simulate compute time */

		MPI_File_read(fh[1], buf, 14400, datatype[1], &status);

		for(long int i=0; i<549; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(long int i=0; i<1353; i++); /* Simulate compute time */

		MPI_File_close(&(fh[1]));

		for(long int i=0; i<335; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<22715; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<104; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<71; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<79; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<13371; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<64; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<63; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<62; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<66; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<3739; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<66; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<71; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<56; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<70; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	}

	if (myrank == 3) {
		for(long int i=0; i<641; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<298; i++); /* Simulate compute time */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		for(long int i=0; i<9473; i++); /* Simulate compute time */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		for(long int i=0; i<1090; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 13, MPI_INT, 0, MPI_COMM_WORLD);

		for(long int i=0; i<61; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 5, MPI_CHAR, 0, MPI_COMM_WORLD);

		for(long int i=0; i<20164701; i++); /* Simulate compute time */

		MPI_Type_contiguous(4096, MPI_BYTE, &datatype[1]);

		for(long int i=0; i<1996; i++); /* Simulate compute time */

		MPI_Type_commit(&datatype[1]);

		for(long int i=0; i<1551; i++); /* Simulate compute time */

		MPI_Type_create_subarray(2, (array_of_sizes_arraystore[0] = 480,array_of_sizes_arraystore[1] = 484,array_of_sizes_arraystore), (array_of_subsizes_arraystore[0] = 120,array_of_subsizes_arraystore[1] = 124,array_of_subsizes_arraystore), (array_of_starts_arraystore[0] = 120,array_of_starts_arraystore[1] = 124,array_of_starts_arraystore), 0, datatype[1], &datatype[2]);

		for(long int i=0; i<80; i++); /* Simulate compute time */

		MPI_Type_commit(&datatype[2]);

		for(long int i=0; i<3796; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(long int i=0; i<150033; i++); /* Simulate compute time */

		MPI_File_open(MPI_COMM_SELF, "tile", 2, MPI_INFO_NULL, &(fh[1]));

		for(long int i=0; i<1403; i++); /* Simulate compute time */

		MPI_File_set_view(fh[1], 0, datatype[1], datatype[2], "native", MPI_INFO_NULL);

		for(long int i=0; i<151; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(long int i=0; i<639; i++); /* Simulate compute time */

		MPI_File_read(fh[1], buf, 14400, datatype[1], &status);

		for(long int i=0; i<549; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(long int i=0; i<1353; i++); /* Simulate compute time */

		MPI_File_close(&(fh[1]));

		for(long int i=0; i<335; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<22715; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<104; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<71; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<79; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<13371; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<64; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<63; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<62; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<66; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<3739; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<66; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<71; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<56; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<70; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	}

	if (myrank == 4) {
		for(long int i=0; i<641; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<298; i++); /* Simulate compute time */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		for(long int i=0; i<9473; i++); /* Simulate compute time */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		for(long int i=0; i<1090; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 13, MPI_INT, 0, MPI_COMM_WORLD);

		for(long int i=0; i<61; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 5, MPI_CHAR, 0, MPI_COMM_WORLD);

		for(long int i=0; i<20164701; i++); /* Simulate compute time */

		MPI_Type_contiguous(4096, MPI_BYTE, &datatype[1]);

		for(long int i=0; i<1996; i++); /* Simulate compute time */

		MPI_Type_commit(&datatype[1]);

		for(long int i=0; i<1936; i++); /* Simulate compute time */

		MPI_Type_create_subarray(2, (array_of_sizes_arraystore[0] = 480,array_of_sizes_arraystore[1] = 484,array_of_sizes_arraystore), (array_of_subsizes_arraystore[0] = 120,array_of_subsizes_arraystore[1] = 124,array_of_subsizes_arraystore), (array_of_starts_arraystore[0] = 120,array_of_starts_arraystore[1] = 124,array_of_starts_arraystore), 0, datatype[1], &datatype[2]);

		for(long int i=0; i<80; i++); /* Simulate compute time */

		MPI_Type_commit(&datatype[2]);

		for(long int i=0; i<3796; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(long int i=0; i<150033; i++); /* Simulate compute time */

		MPI_File_open(MPI_COMM_SELF, "tile", 2, MPI_INFO_NULL, &(fh[1]));

		for(long int i=0; i<1403; i++); /* Simulate compute time */

		MPI_File_set_view(fh[1], 0, datatype[1], datatype[2], "native", MPI_INFO_NULL);

		for(long int i=0; i<151; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(long int i=0; i<639; i++); /* Simulate compute time */

		MPI_File_read(fh[1], buf, 14400, datatype[1], &status);

		for(long int i=0; i<549; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(long int i=0; i<1353; i++); /* Simulate compute time */

		MPI_File_close(&(fh[1]));

		for(long int i=0; i<335; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<22715; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<104; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<71; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<79; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<13371; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<64; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<63; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<62; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<66; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<3739; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<66; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<71; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<56; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<70; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	}

	if (myrank == 5) {
		for(long int i=0; i<641; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<298; i++); /* Simulate compute time */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		for(long int i=0; i<9473; i++); /* Simulate compute time */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		for(long int i=0; i<1090; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 13, MPI_INT, 0, MPI_COMM_WORLD);

		for(long int i=0; i<61; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 5, MPI_CHAR, 0, MPI_COMM_WORLD);

		for(long int i=0; i<20164701; i++); /* Simulate compute time */

		MPI_Type_contiguous(4096, MPI_BYTE, &datatype[1]);

		for(long int i=0; i<1996; i++); /* Simulate compute time */

		MPI_Type_commit(&datatype[1]);

		for(long int i=0; i<1201; i++); /* Simulate compute time */

		MPI_Type_create_subarray(2, (array_of_sizes_arraystore[0] = 480,array_of_sizes_arraystore[1] = 484,array_of_sizes_arraystore), (array_of_subsizes_arraystore[0] = 120,array_of_subsizes_arraystore[1] = 124,array_of_subsizes_arraystore), (array_of_starts_arraystore[0] = 120,array_of_starts_arraystore[1] = 124,array_of_starts_arraystore), 0, datatype[1], &datatype[2]);

		for(long int i=0; i<80; i++); /* Simulate compute time */

		MPI_Type_commit(&datatype[2]);

		for(long int i=0; i<3796; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(long int i=0; i<150033; i++); /* Simulate compute time */

		MPI_File_open(MPI_COMM_SELF, "tile", 2, MPI_INFO_NULL, &(fh[1]));

		for(long int i=0; i<1403; i++); /* Simulate compute time */

		MPI_File_set_view(fh[1], 0, datatype[1], datatype[2], "native", MPI_INFO_NULL);

		for(long int i=0; i<151; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(long int i=0; i<639; i++); /* Simulate compute time */

		MPI_File_read(fh[1], buf, 14400, datatype[1], &status);

		for(long int i=0; i<549; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(long int i=0; i<1353; i++); /* Simulate compute time */

		MPI_File_close(&(fh[1]));

		for(long int i=0; i<335; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<22715; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<104; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<71; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<79; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<13371; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<64; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<63; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<62; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<66; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<3739; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<66; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<71; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<56; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<70; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	}

	if (myrank == 6) {
		for(long int i=0; i<641; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<298; i++); /* Simulate compute time */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		for(long int i=0; i<9473; i++); /* Simulate compute time */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		for(long int i=0; i<1090; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 13, MPI_INT, 0, MPI_COMM_WORLD);

		for(long int i=0; i<61; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 5, MPI_CHAR, 0, MPI_COMM_WORLD);

		for(long int i=0; i<20164701; i++); /* Simulate compute time */

		MPI_Type_contiguous(4096, MPI_BYTE, &datatype[1]);

		for(long int i=0; i<1996; i++); /* Simulate compute time */

		MPI_Type_commit(&datatype[1]);

		for(long int i=0; i<831; i++); /* Simulate compute time */

		MPI_Type_create_subarray(2, (array_of_sizes_arraystore[0] = 480,array_of_sizes_arraystore[1] = 484,array_of_sizes_arraystore), (array_of_subsizes_arraystore[0] = 120,array_of_subsizes_arraystore[1] = 124,array_of_subsizes_arraystore), (array_of_starts_arraystore[0] = 240,array_of_starts_arraystore[1] = 244,array_of_starts_arraystore), 0, datatype[1], &datatype[2]);

		for(long int i=0; i<80; i++); /* Simulate compute time */

		MPI_Type_commit(&datatype[2]);

		for(long int i=0; i<3796; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(long int i=0; i<150033; i++); /* Simulate compute time */

		MPI_File_open(MPI_COMM_SELF, "tile", 2, MPI_INFO_NULL, &(fh[1]));

		for(long int i=0; i<1403; i++); /* Simulate compute time */

		MPI_File_set_view(fh[1], 0, datatype[1], datatype[2], "native", MPI_INFO_NULL);

		for(long int i=0; i<151; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(long int i=0; i<639; i++); /* Simulate compute time */

		MPI_File_read(fh[1], buf, 14400, datatype[1], &status);

		for(long int i=0; i<549; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(long int i=0; i<1353; i++); /* Simulate compute time */

		MPI_File_close(&(fh[1]));

		for(long int i=0; i<335; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<22715; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<104; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<71; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<79; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<13371; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<64; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<63; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<62; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<66; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<3739; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<66; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<71; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<56; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<70; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	}

	if (myrank == 7) {
		for(long int i=0; i<641; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<298; i++); /* Simulate compute time */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		for(long int i=0; i<9473; i++); /* Simulate compute time */

		MPI_Comm_rank(MPI_COMM_WORLD, &rank);

		for(long int i=0; i<1090; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 13, MPI_INT, 0, MPI_COMM_WORLD);

		for(long int i=0; i<61; i++); /* Simulate compute time */

		MPI_Bcast(buffer, 5, MPI_CHAR, 0, MPI_COMM_WORLD);

		for(long int i=0; i<20164701; i++); /* Simulate compute time */

		MPI_Type_contiguous(4096, MPI_BYTE, &datatype[1]);

		for(long int i=0; i<1996; i++); /* Simulate compute time */

		MPI_Type_commit(&datatype[1]);

		for(long int i=0; i<1330; i++); /* Simulate compute time */

		MPI_Type_create_subarray(2, (array_of_sizes_arraystore[0] = 480,array_of_sizes_arraystore[1] = 484,array_of_sizes_arraystore), (array_of_subsizes_arraystore[0] = 120,array_of_subsizes_arraystore[1] = 124,array_of_subsizes_arraystore), (array_of_starts_arraystore[0] = 240,array_of_starts_arraystore[1] = 244,array_of_starts_arraystore), 0, datatype[1], &datatype[2]);

		for(long int i=0; i<80; i++); /* Simulate compute time */

		MPI_Type_commit(&datatype[2]);

		for(long int i=0; i<3796; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(long int i=0; i<150033; i++); /* Simulate compute time */

		MPI_File_open(MPI_COMM_SELF, "tile", 2, MPI_INFO_NULL, &(fh[1]));

		for(long int i=0; i<1403; i++); /* Simulate compute time */

		MPI_File_set_view(fh[1], 0, datatype[1], datatype[2], "native", MPI_INFO_NULL);

		for(long int i=0; i<151; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(long int i=0; i<639; i++); /* Simulate compute time */

		MPI_File_read(fh[1], buf, 14400, datatype[1], &status);

		for(long int i=0; i<549; i++); /* Simulate compute time */

		MPI_Barrier(MPI_COMM_WORLD);

		for(long int i=0; i<1353; i++); /* Simulate compute time */

		MPI_File_close(&(fh[1]));

		for(long int i=0; i<335; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<22715; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<104; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<71; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<79; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<13371; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<64; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<63; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<62; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<66; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<3739; i++); /* Simulate compute time */

		MPI_Comm_size(MPI_COMM_WORLD, &size);

		for(long int i=0; i<66; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<71; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<56; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

		for(long int i=0; i<70; i++); /* Simulate compute time */

		MPI_Allreduce(sendbuf, recvbuf, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	}

	printf("Process %d finished\n", myrank);

	clock_gettime(CLOCK_MONOTONIC, &end);

	dur.tv_sec = end.tv_sec - begin.tv_sec;

	dur.tv_nsec = end.tv_nsec - begin.tv_nsec + dur.tv_sec * 1000000000;
	printf("Process %d cost %ld.%09ld time\n", myrank, dur.tv_sec, dur.tv_nsec);


	MPI_Finalize();
	return 0;
}
