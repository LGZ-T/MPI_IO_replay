/* 
 *This file is generated automaticaly by wrapper generator.
 * define neccessary variables below
 */

#include "simple_compress.h"
SimpleCompress *sc;

struct timespec tm1, tm2;
int ret, result_len;
char comm_name[100], etype_name[100], filetype_name[100], datatype_name[100];
#define BUFFER_SIZE 4096
const int threshold = BUFFER_SIZE * 0.9;
int bytes, written_bytes;
char rec_buffer[4096];

/*
 *  (C) 2009 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */

#define _XOPEN_SOURCE 500
#define _GNU_SOURCE /* for tdestroy() */

#include <iostream>
#include "recorder-runtime-config.h"

#include <stdio.h>
#ifdef HAVE_MNTENT_H
#include <mntent.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <zlib.h>
#include <assert.h>
#include <search.h>

#include "mpi.h"
#include "recorder-compress.h"
#include "recorder-dynamic.h"

extern char* __progname;
FILE *__recorderfh;

struct timespec ts;

struct timespec recorder_wtime(void)
{
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);

    	return ts;
}

struct timespec ts_minus(struct timespec a, struct timespec b)
{
	struct timespec result;

	result.tv_sec = a.tv_sec-b.tv_sec;
	result.tv_nsec = a.tv_nsec-b.tv_nsec;

	if (result.tv_nsec < 0) {
		result.tv_nsec += 1000000000;
		result.tv_sec--;
	}

	return result;
}

void recorder_mpi_initialize(int *argc, char ***argv)
{
    int nprocs;
    int rank;

    RECORDER_MPI_CALL(PMPI_Comm_size)(MPI_COMM_WORLD, &nprocs);
    RECORDER_MPI_CALL(PMPI_Comm_rank)(MPI_COMM_WORLD, &rank);

    char *logfile_name;
    char *logdir_name;
    logfile_name=(char*)malloc(PATH_MAX);
    logdir_name=(char*)malloc(PATH_MAX);
    char cuser[L_cuserid] = {0};
    cuserid(cuser);

    sprintf(logdir_name,"%s_%s",cuser, __progname);
    int status;
    status = mkdir(logdir_name, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    sprintf(logfile_name,"%s/log.%d",logdir_name,rank);
    __recorderfh=fopen(logfile_name,"w");

    printf(" logfile_name %s ,recorderfh %d\n",logfile_name,__recorderfh);

	// initialize sc
	create_sc_by_filename(&sc, logfile_name);

    free(logfile_name);
    free(logdir_name);

    return;
}

void recorder_shutdown(int timing_flag)
{
    fclose(__recorderfh);

    return;
}
int MPI_Isend(void *buf,int count,MPI_Datatype datatype,int dest,int tag,MPI_Comm comm,MPI_Request *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
PMPI_Comm_get_name(comm, comm_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_Isend)(buf, count, datatype, dest, tag, comm, request);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Isend buf=*buf count=%d datatype=%s dest=%d tag=%d comm=%s request=Error \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, count, datatype_name, dest, tag, comm_name, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_Irecv(void *buf,int count,MPI_Datatype datatype,int source,int tag,MPI_Comm comm,MPI_Request *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
PMPI_Comm_get_name(comm, comm_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_Irecv)(buf, count, datatype, source, tag, comm, request);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Irecv buf=*buf count=%d datatype=%s source=%d tag=%d comm=%s request=Error \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, count, datatype_name, source, tag, comm_name, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_Send(void *buf,int count,MPI_Datatype datatype,int dest,int tag,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
PMPI_Comm_get_name(comm, comm_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_Send)(buf, count, datatype, dest, tag, comm);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Send buf=*buf count=%d datatype=%s dest=%d tag=%d comm=%s \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, count, datatype_name, dest, tag, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_Recv(void *buf,int count,MPI_Datatype datatype,int source,int tag,MPI_Comm comm,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
PMPI_Comm_get_name(comm, comm_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_Recv)(buf, count, datatype, source, tag, comm, status);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Recv buf=*buf count=%d datatype=%s source=%d tag=%d comm=%s status=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, count, datatype_name, source, tag, comm_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_Allreduce(void *sendbuf,void *recvbuf,int count,MPI_Datatype datatype,MPI_Op op,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
PMPI_Comm_get_name(comm, comm_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_Allreduce)(sendbuf, recvbuf, count, datatype, op, comm);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Allreduce sendbuf=*sendbuf recvbuf=*recvbuf count=%d datatype=%s op=%d comm=%s \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, count, datatype_name, op, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_Allgather(void *sendbuf,int  sendcount,MPI_Datatype sendtype,void *recvbuf,int recvcount,MPI_Datatype recvtype,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Comm_get_name(comm, comm_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_Allgather)(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Allgather sendbuf=*sendbuf sendcount=%d sendtype=%s recvbuf=*recvbuf recvcount=%d recvtype=%s comm=%s \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, sendcount, sendtype, recvcount, recvtype, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_Allgatherv(void *sendbuf,int sendcount,MPI_Datatype sendtype,void *recvbuf,int *recvcount,int *displs,MPI_Datatype recvtype,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Comm_get_name(comm, comm_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_Allgatherv)(sendbuf, sendcount, sendtype, recvbuf, recvcount, displs, recvtype, comm);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Allgatherv sendbuf=*sendbuf sendcount=%d sendtype=%s recvbuf=*recvbuf recvcount=*recvcount displs=*displs recvtype=%s comm=%s \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, sendcount, sendtype, recvtype, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_Alltoall(void *sendbuf,int sendcount,MPI_Datatype sendtype,void *recvbuf,int recvcount,MPI_Datatype recvtype,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Comm_get_name(comm, comm_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_Alltoall)(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Alltoall sendbuf=*sendbuf sendcount=%d sendtype=%s recvbuf=*recvbuf recvcount=%d recvtype=%s comm=%s \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, sendcount, sendtype, recvcount, recvtype, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_Alltoallv(void *sendbuf,int *sendcounts,int *sdispls,MPI_Datatype sendtype,void *recvbuf,int *recvcounts,int *rdispls,MPI_Datatype recvtype,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Comm_get_name(comm, comm_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_Alltoallv)(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Alltoallv sendbuf=*sendbuf sendcounts=*sendcounts sdispls=*sdispls sendtype=%s recvbuf=*recvbuf recvcounts=*recvcounts rdispls=*rdispls recvtype=%s comm=%s \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, sendtype, recvtype, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_Alltoallw(void *sendbuf,int *sendcounts,int *sdispls,MPI_Datatype *sendtypes,void *recvbuf,int *recvcounts,int *rdispls,MPI_Datatype *recvtypes,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Comm_get_name(comm, comm_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_Alltoallw)(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Alltoallw sendbuf=*sendbuf sendcounts=*sendcounts sdispls=*sdispls sendtypes=%s recvbuf=*recvbuf recvcounts=*recvcounts rdispls=*rdispls recvtypes=%s comm=%s \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, sendtypes, recvtypes, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_Barrier(MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Comm_get_name(comm, comm_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_Barrier)(comm);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Barrier comm=%s \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_Bsend(void *buf,int count,MPI_Datatype datatype,int dest,int tag,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
PMPI_Comm_get_name(comm, comm_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_Bsend)(buf, count, datatype, dest, tag, comm);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Bsend buf=*buf count=%d datatype=%s dest=%d tag=%d comm=%s \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, count, datatype_name, dest, tag, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_Gather(void *sendbuf,int sendcount,MPI_Datatype sendtype,void *recvbuf,int recvcount,MPI_Datatype recvtype,int root,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Comm_get_name(comm, comm_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_Gather)(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Gather sendbuf=*sendbuf sendcount=%d sendtype=%s recvbuf=*recvbuf recvcount=%d recvtype=%s root=%d comm=%s \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, sendcount, sendtype, recvcount, recvtype, root, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_Gatherv(void *sendbuf,int sendcount,MPI_Datatype sendtype,void *recvbuf,int *recvcounts,int *displs,MPI_Datatype recvtype,int root,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Comm_get_name(comm, comm_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_Gatherv)(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Gatherv sendbuf=*sendbuf sendcount=%d sendtype=%s recvbuf=*recvbuf recvcounts=*recvcounts displs=*displs recvtype=%s root=%d comm=%s \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, sendcount, sendtype, recvtype, root, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_Scatter(void *sendbuf,int sendcount,MPI_Datatype sendtype,void *recvbuf,int recvcount,MPI_Datatype recvtype,int root,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Comm_get_name(comm, comm_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_Scatter)(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Scatter sendbuf=*sendbuf sendcount=%d sendtype=%s recvbuf=*recvbuf recvcount=%d recvtype=%s root=%d comm=%s \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, sendcount, sendtype, recvcount, recvtype, root, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_Scatterv(void *sendbuf,int *sendcounts,int *displs,MPI_Datatype sendtype,void *recvbuf,int recvcount,MPI_Datatype recvtype,int root,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Comm_get_name(comm, comm_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_Scatterv)(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Scatterv sendbuf=*sendbuf sendcounts=*sendcounts displs=*displs sendtype=%s recvbuf=*recvbuf recvcount=%d recvtype=%s root=%d comm=%s \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, sendtype, recvcount, recvtype, root, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_Wait(MPI_Request *request,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
	ret = RECORDER_MPI_CALL(PMPI_Wait)(request, status);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Wait request=Error status=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, request, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_Waitall(int count,MPI_Request *array_of_requests,MPI_Status *array_of_statuses)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
	ret = RECORDER_MPI_CALL(PMPI_Waitall)(count, array_of_requests, array_of_statuses);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Waitall count=%d array_of_requests=Error array_of_statuses=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, count, array_of_requests, array_of_statuses);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_Waitany(int count,MPI_Request *array_of_requests,int *index,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
	ret = RECORDER_MPI_CALL(PMPI_Waitany)(count, array_of_requests, index, status);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Waitany count=%d array_of_requests=Error index=*index status=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, count, array_of_requests, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_Waitsome(int incount,MPI_Request *array_of_requests,int *outcount,int *array_of_indices,MPI_Status *array_of_statuses)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
	ret = RECORDER_MPI_CALL(PMPI_Waitsome)(incount, array_of_requests, outcount, array_of_indices, array_of_statuses);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Waitsome incount=%d array_of_requests=Error outcount=*outcount array_of_indices=*array_of_indices array_of_statuses=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, incount, array_of_requests, array_of_statuses);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_Bcast(void *buffer,int count,MPI_Datatype datatype,int root,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
PMPI_Comm_get_name(comm, comm_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_Bcast)(buffer, count, datatype, root, comm);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Bcast buffer=*buffer count=%d datatype=%s root=%d comm=%s \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, count, datatype_name, root, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_Reduce(void *sendbuf,void *recvbuf,int count,MPI_Datatype datatype,MPI_Op op,int root,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
PMPI_Comm_get_name(comm, comm_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_Reduce)(sendbuf, recvbuf, count, datatype, op, root, comm);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Reduce sendbuf=*sendbuf recvbuf=*recvbuf count=%d datatype=%s op=%d root=%d comm=%s \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, count, datatype_name, op, root, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_close(MPI_File *fh)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
	ret = RECORDER_MPI_CALL(PMPI_File_close)(fh);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_close fh=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_set_size(MPI_File fh,MPI_Offset size)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
	ret = RECORDER_MPI_CALL(PMPI_File_set_size)(fh, size);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_set_size fh=%d size=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, size);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_iread_at(MPI_File fh,MPI_Offset offset,void *buf,int count,MPI_Datatype datatype,__D_MPI_REQUEST *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_iread_at)(fh, offset, buf, count, datatype, request);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_iread_at fh=%d offset=%d buf=*buf count=%d datatype=%s request=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, offset, count, datatype_name, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_iread(MPI_File fh,void  *buf,int  count,MPI_Datatype  datatype,__D_MPI_REQUEST  *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_iread)(fh, buf, count, datatype, request);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_iread fh=%d buf=*buf count=%d datatype=%s request=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, count, datatype_name, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_iread_shared(MPI_File fh,void *buf,int count,MPI_Datatype datatype,__D_MPI_REQUEST *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_iread_shared)(fh, buf, count, datatype, request);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_iread_shared fh=%d buf=*buf count=%d datatype=%s request=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, count, datatype_name, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_iwrite_at(MPI_File fh,MPI_Offset offset,void *buf,int count,MPI_Datatype datatype,__D_MPI_REQUEST *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_iwrite_at)(fh, offset, buf, count, datatype, request);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_iwrite_at fh=%d offset=%d buf=*buf count=%d datatype=%s request=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, offset, count, datatype_name, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_iwrite(MPI_File fh,void *buf,int count,MPI_Datatype datatype,__D_MPI_REQUEST *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_iwrite)(fh, buf, count, datatype, request);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_iwrite fh=%d buf=*buf count=%d datatype=%s request=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, count, datatype_name, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_iwrite_shared(MPI_File fh,void *buf,int count,MPI_Datatype datatype,__D_MPI_REQUEST *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_iwrite_shared)(fh, buf, count, datatype, request);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_iwrite_shared fh=%d buf=*buf count=%d datatype=%s request=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, count, datatype_name, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_open(MPI_Comm comm,char *filename,int amode,MPI_Info info,MPI_File *fh)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Comm_get_name(comm, comm_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_open)(comm, filename, amode, info, fh);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_open comm=%s filename=%s amode=%d info=%d fh=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, comm_name, filename, amode, info, fh);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_read_all_begin(MPI_File fh,void *buf,int count,MPI_Datatype datatype)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_read_all_begin)(fh, buf, count, datatype);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_all_begin fh=%d buf=*buf count=%d datatype=%s \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, count, datatype_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_read_all(MPI_File fh,void *buf,int count,MPI_Datatype datatype,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_read_all)(fh, buf, count, datatype, status);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_all fh=%d buf=*buf count=%d datatype=%s status=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, count, datatype_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_read_at_all(MPI_File fh,MPI_Offset offset,void *buf,int count,MPI_Datatype datatype,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_read_at_all)(fh, offset, buf, count, datatype, status);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_at_all fh=%d offset=%d buf=*buf count=%d datatype=%s status=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, offset, count, datatype_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_read_at_all_begin(MPI_File fh,MPI_Offset offset,void *buf,int count,MPI_Datatype datatype)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_read_at_all_begin)(fh, offset, buf, count, datatype);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_at_all_begin fh=%d offset=%d buf=*buf count=%d datatype=%s \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, offset, count, datatype_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_read_at(MPI_File fh,MPI_Offset offset,void *buf,int count,MPI_Datatype datatype,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_read_at)(fh, offset, buf, count, datatype, status);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_at fh=%d offset=%d buf=*buf count=%d datatype=%s status=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, offset, count, datatype_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_read(MPI_File fh,void *buf,int count,MPI_Datatype datatype,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_read)(fh, buf, count, datatype, status);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read fh=%d buf=*buf count=%d datatype=%s status=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, count, datatype_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_read_ordered_begin(MPI_File fh,void *buf,int count,MPI_Datatype datatype)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_read_ordered_begin)(fh, buf, count, datatype);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_ordered_begin fh=%d buf=*buf count=%d datatype=%s \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, count, datatype_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_read_ordered(MPI_File fh,void *buf,int count,MPI_Datatype datatype,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_read_ordered)(fh, buf, count, datatype, status);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_ordered fh=%d buf=*buf count=%d datatype=%s status=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, count, datatype_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_read_shared(MPI_File fh,void *buf,int count,MPI_Datatype datatype,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_read_shared)(fh, buf, count, datatype, status);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_shared fh=%d buf=*buf count=%d datatype=%s status=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, count, datatype_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_set_view(MPI_File fh,MPI_Offset disp,MPI_Datatype etype,MPI_Datatype filetype,char *datarep,MPI_Info info)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(etype, etype_name, &result_len);
PMPI_Type_get_name(filetype, filetype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_set_view)(fh, disp, etype, filetype, datarep, info);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_set_view fh=%d disp=%d etype=%s filetype=%s datarep=%s info=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, disp, etype_name, filetype_name, datarep, info);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_sync(MPI_File fh)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
	ret = RECORDER_MPI_CALL(PMPI_File_sync)(fh);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_sync fh=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_write_all_begin(MPI_File fh,void *buf,int count,MPI_Datatype datatype)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_write_all_begin)(fh, buf, count, datatype);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_all_begin fh=%d buf=*buf count=%d datatype=%s \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, count, datatype_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_write_all(MPI_File fh,void *buf,int count,MPI_Datatype datatype,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_write_all)(fh, buf, count, datatype, status);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_all fh=%d buf=*buf count=%d datatype=%s status=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, count, datatype_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_write_at_all_begin(MPI_File fh,MPI_Offset offset,void *buf,int count,MPI_Datatype datatype)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_write_at_all_begin)(fh, offset, buf, count, datatype);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_at_all_begin fh=%d offset=%d buf=*buf count=%d datatype=%s \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, offset, count, datatype_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_write_at_all(MPI_File fh,MPI_Offset offset,void *buf,int count,MPI_Datatype datatype,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_write_at_all)(fh, offset, buf, count, datatype, status);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_at_all fh=%d offset=%d buf=*buf count=%d datatype=%s status=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, offset, count, datatype_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_write_at(MPI_File fh,MPI_Offset offset,void *buf,int count,MPI_Datatype datatype,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_write_at)(fh, offset, buf, count, datatype, status);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_at fh=%d offset=%d buf=*buf count=%d datatype=%s status=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, offset, count, datatype_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_write(MPI_File fh,void *buf,int count,MPI_Datatype datatype,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_write)(fh, buf, count, datatype, status);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write fh=%d buf=*buf count=%d datatype=%s status=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, count, datatype_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_write_ordered_begin(MPI_File fh,void *buf,int count,MPI_Datatype datatype)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_write_ordered_begin)(fh, buf, count, datatype);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_ordered_begin fh=%d buf=*buf count=%d datatype=%s \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, count, datatype_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_write_ordered(MPI_File fh,void *buf,int count,MPI_Datatype datatype,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_write_ordered)(fh, buf, count, datatype, status);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_ordered fh=%d buf=*buf count=%d datatype=%s status=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, count, datatype_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_File_write_shared(MPI_File fh,void *buf,int count,MPI_Datatype datatype,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Type_get_name(datatype, datatype_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_File_write_shared)(fh, buf, count, datatype, status);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_shared fh=%d buf=*buf count=%d datatype=%s status=%d \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, fh, count, datatype_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_Comm_rank(MPI_Comm comm,int *rank)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Comm_get_name(comm, comm_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_Comm_rank)(comm, rank);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Comm_rank comm=%s rank=*rank \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

int MPI_Comm_size(MPI_Comm comm,int *size)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = ts_minus(recorder_wtime(), tm2);
PMPI_Comm_get_name(comm, comm_name, &result_len);
	ret = RECORDER_MPI_CALL(PMPI_Comm_size)(comm, size);
	tm2 = ts_minus(recorder_wtime(), tm1);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Comm_size comm=%s size=*size \n",  tm1.tv_sec, tm1.tv_nsec, tm2.tv_sec, tm2.tv_nsec, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	/* tm2 stands for the true exit moment of this function */
	tm2 = recorder_wtime();
	return ret;
}

