/* 
 *This file is generated automaticaly by a wrapper generator!
 * define neccessary variables below
 */

#include "simple_compress.h"
SimpleCompress *sc;

struct timespec tm1, tm2, tm3, tm4, compute_time, mpi_time, this_func_time;
struct timespec compute_time_all, mpi_time_all, recorder_time_all;
int ret, result_len;
char comm_name[100], etype_name[100], filetype_name[100], datatype_name[100], oldtype_name[100], newtype_name[100];
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

const long nano = 1000000000;

struct timespec operator+(const struct timespec& a, const struct timespec& b)
{
	struct timespec result;

	result.tv_sec = a.tv_sec+b.tv_sec;
	result.tv_nsec = a.tv_nsec+b.tv_nsec;

	if (result.tv_nsec >= nano) {
		result.tv_nsec -= nano;
		result.tv_sec++;
	}

	return result;
}

struct timespec& operator+=(struct timespec& a, const timespec& b)
{
	a.tv_sec += b.tv_sec;
	a.tv_nsec += b.tv_nsec;

	if (a.tv_nsec >= nano) {
		a.tv_nsec -= nano;
		a.tv_sec++;
	}

	return a;
}

struct timespec operator-(const struct timespec& a, const struct timespec& b)
{
	struct timespec result;

	result.tv_sec = a.tv_sec-b.tv_sec;
	result.tv_nsec = a.tv_nsec-b.tv_nsec;

	if (result.tv_nsec < 0) {
		result.tv_nsec += nano;
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
	delete_sc(sc);
	fflush(__recorderfh);
	fprintf(__recorderfh, "Compute_time=%ld.%.9ld MPI_Call_time=%ld.%.9ld Recorder_time=%ld.%.9ld\n", compute_time_all, mpi_time_all, recorder_time_all);
    fclose(__recorderfh);

    return;
}
int MPI_Ibsend(void *buf,int count,MPI_Datatype datatype,int dest,int tag,MPI_Comm comm,MPI_Request *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Ibsend)(buf, count, datatype, dest, tag, comm, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Ibsend buf=buf count=%d datatype=%s dest=%d tag=%d comm=%s request=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, tag, comm_name, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Irsend(void *buf,int count,MPI_Datatype datatype,int dest,int tag,MPI_Comm comm,MPI_Request *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Irsend)(buf, count, datatype, dest, tag, comm, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Irsend buf=buf count=%d datatype=%s dest=%d tag=%d comm=%s request=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, tag, comm_name, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Issend(void *buf,int count,MPI_Datatype datatype,int dest,int tag,MPI_Comm comm,MPI_Request *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Issend)(buf, count, datatype, dest, tag, comm, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Issend buf=buf count=%d datatype=%s dest=%d tag=%d comm=%s request=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, tag, comm_name, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Isend(void *buf,int count,MPI_Datatype datatype,int dest,int tag,MPI_Comm comm,MPI_Request *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Isend)(buf, count, datatype, dest, tag, comm, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Isend buf=buf count=%d datatype=%s dest=%d tag=%d comm=%s request=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, tag, comm_name, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Irecv(void *buf,int count,MPI_Datatype datatype,int source,int tag,MPI_Comm comm,MPI_Request *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Irecv)(buf, count, datatype, source, tag, comm, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Irecv buf=buf count=%d datatype=%s source=%d tag=%d comm=%s request=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, source, tag, comm_name, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Send(void *buf,int count,MPI_Datatype datatype,int dest,int tag,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Send)(buf, count, datatype, dest, tag, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Send buf=buf count=%d datatype=%s dest=%d tag=%d comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, tag, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Send_init(void *buf,int count,MPI_Datatype datatype,int dest,int tag,MPI_Comm comm,MPI_Request *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Send_init)(buf, count, datatype, dest, tag, comm, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Send_init buf=buf count=%d datatype=%s dest=%d tag=%d comm=%s request=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, tag, comm_name, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Sendrecv(void *sendbuf,int sendcount,MPI_Datatype sendtype,int dest,int sendtag,void *recvbuf,int recvcount,MPI_Datatype recvtype,int source,int recvtag,MPI_Comm comm,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Sendrecv)(sendbuf, sendcount, sendtype, dest, sendtag, recvbuf, recvcount, recvtype, source, recvtag, comm, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Sendrecv sendbuf=sendbuf sendcount=%d sendtype=%s dest=%d sendtag=%d recvbuf=recvbuf recvcount=%d recvtype=%s source=%d recvtag=%d comm=%s status=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, sendcount, sendtype, dest, sendtag, recvcount, recvtype, source, recvtag, comm_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Sendrecv_replace(void *buf,int count,MPI_Datatype datatype,int dest,int sendtag,int source,int recvtag,MPI_Comm comm,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Sendrecv_replace)(buf, count, datatype, dest, sendtag, source, recvtag, comm, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Sendrecv_replace buf=buf count=%d datatype=%s dest=%d sendtag=%d source=%d recvtag=%d comm=%s status=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, sendtag, source, recvtag, comm_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Ssend(void *buf,int count,MPI_Datatype datatype,int dest,int tag,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Ssend)(buf, count, datatype, dest, tag, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Ssend buf=buf count=%d datatype=%s dest=%d tag=%d comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, tag, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Ssend_init(void *buf,int count,MPI_Datatype datatype,int dest,int tag,MPI_Comm comm,MPI_Request *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Ssend_init)(buf, count, datatype, dest, tag, comm, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Ssend_init buf=buf count=%d datatype=%s dest=%d tag=%d comm=%s request=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, tag, comm_name, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Rsend(void *buf,int count,MPI_Datatype datatype,int dest,int tag,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Rsend)(buf, count, datatype, dest, tag, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Rsend buf=buf count=%d datatype=%s dest=%d tag=%d comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, tag, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Rsend_init(void *buf,int count,MPI_Datatype datatype,int dest,int tag,MPI_Comm comm,MPI_Request *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Rsend_init)(buf, count, datatype, dest, tag, comm, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Rsend_init buf=buf count=%d datatype=%s dest=%d tag=%d comm=%s request=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, tag, comm_name, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Bsend(void *buf,int count,MPI_Datatype datatype,int dest,int tag,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Bsend)(buf, count, datatype, dest, tag, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Bsend buf=buf count=%d datatype=%s dest=%d tag=%d comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, tag, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Bsend_init(void *buf,int count,MPI_Datatype datatype,int dest,int tag,MPI_Comm comm,MPI_Request *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Bsend_init)(buf, count, datatype, dest, tag, comm, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Bsend_init buf=buf count=%d datatype=%s dest=%d tag=%d comm=%s request=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, tag, comm_name, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Start(MPI_Request *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Start)(request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Start request=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Recv(void *buf,int count,MPI_Datatype datatype,int source,int tag,MPI_Comm comm,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Recv)(buf, count, datatype, source, tag, comm, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Recv buf=buf count=%d datatype=%s source=%d tag=%d comm=%s status=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, source, tag, comm_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Recv_init(void *buf,int count,MPI_Datatype datatype,int source,int tag,MPI_Comm comm,MPI_Request *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Recv_init)(buf, count, datatype, source, tag, comm, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Recv_init buf=buf count=%d datatype=%s source=%d tag=%d comm=%s request=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, source, tag, comm_name, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Allreduce(void *sendbuf,void *recvbuf,int count,MPI_Datatype datatype,MPI_Op op,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Allreduce)(sendbuf, recvbuf, count, datatype, op, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Allreduce sendbuf=sendbuf recvbuf=recvbuf count=%d datatype=%s op=%ld comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, op, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Allgather(void *sendbuf,int  sendcount,MPI_Datatype sendtype,void *recvbuf,int recvcount,MPI_Datatype recvtype,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Allgather)(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Allgather sendbuf=sendbuf sendcount=%d sendtype=%s recvbuf=recvbuf recvcount=%d recvtype=%s comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, sendcount, sendtype, recvcount, recvtype, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Allgatherv(void *sendbuf,int sendcount,MPI_Datatype sendtype,void *recvbuf,int *recvcount,int *displs,MPI_Datatype recvtype,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Allgatherv)(sendbuf, sendcount, sendtype, recvbuf, recvcount, displs, recvtype, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Allgatherv sendbuf=sendbuf sendcount=%d sendtype=%s recvbuf=recvbuf recvcount=recvcount displs=displs recvtype=%s comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, sendcount, sendtype, recvtype, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Alltoall(void *sendbuf,int sendcount,MPI_Datatype sendtype,void *recvbuf,int recvcount,MPI_Datatype recvtype,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Alltoall)(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Alltoall sendbuf=sendbuf sendcount=%d sendtype=%s recvbuf=recvbuf recvcount=%d recvtype=%s comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, sendcount, sendtype, recvcount, recvtype, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Alltoallv(void *sendbuf,int *sendcounts,int *sdispls,MPI_Datatype sendtype,void *recvbuf,int *recvcounts,int *rdispls,MPI_Datatype recvtype,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Alltoallv)(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Alltoallv sendbuf=sendbuf sendcounts=sendcounts sdispls=sdispls sendtype=%s recvbuf=recvbuf recvcounts=recvcounts rdispls=rdispls recvtype=%s comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, sendtype, recvtype, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Alltoallw(void *sendbuf,int *sendcounts,int *sdispls,MPI_Datatype *sendtypes,void *recvbuf,int *recvcounts,int *rdispls,MPI_Datatype *recvtypes,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Alltoallw)(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Alltoallw sendbuf=sendbuf sendcounts=sendcounts sdispls=sdispls sendtypes=%ld recvbuf=recvbuf recvcounts=recvcounts rdispls=rdispls recvtypes=%ld comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, sendtypes, recvtypes, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Barrier(MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Barrier)(comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Barrier comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Gather(void *sendbuf,int sendcount,MPI_Datatype sendtype,void *recvbuf,int recvcount,MPI_Datatype recvtype,int root,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Gather)(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Gather sendbuf=sendbuf sendcount=%d sendtype=%s recvbuf=recvbuf recvcount=%d recvtype=%s root=%d comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, sendcount, sendtype, recvcount, recvtype, root, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Gatherv(void *sendbuf,int sendcount,MPI_Datatype sendtype,void *recvbuf,int *recvcounts,int *displs,MPI_Datatype recvtype,int root,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Gatherv)(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Gatherv sendbuf=sendbuf sendcount=%d sendtype=%s recvbuf=recvbuf recvcounts=recvcounts displs=displs recvtype=%s root=%d comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, sendcount, sendtype, recvtype, root, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Scatter(void *sendbuf,int sendcount,MPI_Datatype sendtype,void *recvbuf,int recvcount,MPI_Datatype recvtype,int root,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Scatter)(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Scatter sendbuf=sendbuf sendcount=%d sendtype=%s recvbuf=recvbuf recvcount=%d recvtype=%s root=%d comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, sendcount, sendtype, recvcount, recvtype, root, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Scatterv(void *sendbuf,int *sendcounts,int *displs,MPI_Datatype sendtype,void *recvbuf,int recvcount,MPI_Datatype recvtype,int root,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Scatterv)(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Scatterv sendbuf=sendbuf sendcounts=sendcounts displs=displs sendtype=%s recvbuf=recvbuf recvcount=%d recvtype=%s root=%d comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, sendtype, recvcount, recvtype, root, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Wait(MPI_Request *request,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Wait)(request, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Wait request=%ld status=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, request, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Waitall(int count,MPI_Request *array_of_requests,MPI_Status *array_of_statuses)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Waitall)(count, array_of_requests, array_of_statuses);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Waitall count=%d array_of_requests=%ld array_of_statuses=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, array_of_requests, array_of_statuses);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Waitany(int count,MPI_Request *array_of_requests,int *index,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Waitany)(count, array_of_requests, index, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Waitany count=%d array_of_requests=%ld index=index status=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, array_of_requests, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Waitsome(int incount,MPI_Request *array_of_requests,int *outcount,int *array_of_indices,MPI_Status *array_of_statuses)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Waitsome)(incount, array_of_requests, outcount, array_of_indices, array_of_statuses);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Waitsome incount=%d array_of_requests=%ld outcount=outcount array_of_indices=array_of_indices array_of_statuses=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, incount, array_of_requests, array_of_statuses);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Bcast(void *buffer,int count,MPI_Datatype datatype,int root,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Bcast)(buffer, count, datatype, root, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Bcast buffer=buffer count=%d datatype=%s root=%d comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, root, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Reduce(void *sendbuf,void *recvbuf,int count,MPI_Datatype datatype,MPI_Op op,int root,MPI_Comm comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Reduce)(sendbuf, recvbuf, count, datatype, op, root, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Reduce sendbuf=sendbuf recvbuf=recvbuf count=%d datatype=%s op=%ld root=%d comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, op, root, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_close(MPI_File *fh)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_close)(fh);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_close fh=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, *fh);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_iread_at(MPI_File fh,MPI_Offset offset,void *buf,int count,MPI_Datatype datatype,__D_MPI_REQUEST *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_iread_at)(fh, offset, buf, count, datatype, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_iread_at fh=%ld offset=%ld buf=buf count=%d datatype=%s request=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, offset, count, datatype_name, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_iread(MPI_File fh,void  *buf,int  count,MPI_Datatype  datatype,__D_MPI_REQUEST  *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_iread)(fh, buf, count, datatype, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_iread fh=%ld buf=buf count=%d datatype=%s request=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_iread_shared(MPI_File fh,void *buf,int count,MPI_Datatype datatype,__D_MPI_REQUEST *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_iread_shared)(fh, buf, count, datatype, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_iread_shared fh=%ld buf=buf count=%d datatype=%s request=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_iwrite_at(MPI_File fh,MPI_Offset offset,void *buf,int count,MPI_Datatype datatype,__D_MPI_REQUEST *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_iwrite_at)(fh, offset, buf, count, datatype, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_iwrite_at fh=%ld offset=%ld buf=buf count=%d datatype=%s request=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, offset, count, datatype_name, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_iwrite(MPI_File fh,void *buf,int count,MPI_Datatype datatype,__D_MPI_REQUEST *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_iwrite)(fh, buf, count, datatype, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_iwrite fh=%ld buf=buf count=%d datatype=%s request=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_iwrite_shared(MPI_File fh,void *buf,int count,MPI_Datatype datatype,__D_MPI_REQUEST *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_iwrite_shared)(fh, buf, count, datatype, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_iwrite_shared fh=%ld buf=buf count=%d datatype=%s request=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name, request);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_open(MPI_Comm comm,char *filename,int amode,MPI_Info info,MPI_File *fh)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_open)(comm, filename, amode, info, fh);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_open comm=%s filename=%ld amode=%d info=%ld fh=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, comm_name, filename, amode, info, *fh);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_read_all_begin(MPI_File fh,void *buf,int count,MPI_Datatype datatype)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_read_all_begin)(fh, buf, count, datatype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_all_begin fh=%ld buf=buf count=%d datatype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_read_all(MPI_File fh,void *buf,int count,MPI_Datatype datatype,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_read_all)(fh, buf, count, datatype, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_all fh=%ld buf=buf count=%d datatype=%s status=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_read_at_all(MPI_File fh,MPI_Offset offset,void *buf,int count,MPI_Datatype datatype,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_read_at_all)(fh, offset, buf, count, datatype, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_at_all fh=%ld offset=%ld buf=buf count=%d datatype=%s status=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, offset, count, datatype_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_read_at_all_begin(MPI_File fh,MPI_Offset offset,void *buf,int count,MPI_Datatype datatype)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_read_at_all_begin)(fh, offset, buf, count, datatype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_at_all_begin fh=%ld offset=%ld buf=buf count=%d datatype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, offset, count, datatype_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_read_at(MPI_File fh,MPI_Offset offset,void *buf,int count,MPI_Datatype datatype,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_read_at)(fh, offset, buf, count, datatype, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_at fh=%ld offset=%ld buf=buf count=%d datatype=%s status=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, offset, count, datatype_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_read(MPI_File fh,void *buf,int count,MPI_Datatype datatype,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_read)(fh, buf, count, datatype, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read fh=%ld buf=buf count=%d datatype=%s status=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_read_ordered_begin(MPI_File fh,void *buf,int count,MPI_Datatype datatype)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_read_ordered_begin)(fh, buf, count, datatype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_ordered_begin fh=%ld buf=buf count=%d datatype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_read_ordered(MPI_File fh,void *buf,int count,MPI_Datatype datatype,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_read_ordered)(fh, buf, count, datatype, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_ordered fh=%ld buf=buf count=%d datatype=%s status=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_read_shared(MPI_File fh,void *buf,int count,MPI_Datatype datatype,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_read_shared)(fh, buf, count, datatype, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_shared fh=%ld buf=buf count=%d datatype=%s status=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_set_view(MPI_File fh,MPI_Offset disp,MPI_Datatype etype,MPI_Datatype filetype,char *datarep,MPI_Info info)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(etype, etype_name, &result_len);

		if (result_len == 0) {
			sprintf(etype_name, "%ld", etype);
		}
		PMPI_Type_get_name(filetype, filetype_name, &result_len);

		if (result_len == 0) {
			sprintf(filetype_name, "%ld", filetype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_set_view)(fh, disp, etype, filetype, datarep, info);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_set_view fh=%ld disp=%ld etype=%s filetype=%s datarep=%ld info=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, disp, etype_name, filetype_name, datarep, info);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_sync(MPI_File fh)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_sync)(fh);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_sync fh=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_write_all_begin(MPI_File fh,void *buf,int count,MPI_Datatype datatype)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_write_all_begin)(fh, buf, count, datatype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_all_begin fh=%ld buf=buf count=%d datatype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_write_all(MPI_File fh,void *buf,int count,MPI_Datatype datatype,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_write_all)(fh, buf, count, datatype, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_all fh=%ld buf=buf count=%d datatype=%s status=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_write_at_all_begin(MPI_File fh,MPI_Offset offset,void *buf,int count,MPI_Datatype datatype)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_write_at_all_begin)(fh, offset, buf, count, datatype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_at_all_begin fh=%ld offset=%ld buf=buf count=%d datatype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, offset, count, datatype_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_write_at_all(MPI_File fh,MPI_Offset offset,void *buf,int count,MPI_Datatype datatype,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_write_at_all)(fh, offset, buf, count, datatype, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_at_all fh=%ld offset=%ld buf=buf count=%d datatype=%s status=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, offset, count, datatype_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_write_at(MPI_File fh,MPI_Offset offset,void *buf,int count,MPI_Datatype datatype,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_write_at)(fh, offset, buf, count, datatype, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_at fh=%ld offset=%ld buf=buf count=%d datatype=%s status=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, offset, count, datatype_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_write(MPI_File fh,void *buf,int count,MPI_Datatype datatype,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_write)(fh, buf, count, datatype, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write fh=%ld buf=buf count=%d datatype=%s status=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_write_ordered_begin(MPI_File fh,void *buf,int count,MPI_Datatype datatype)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_write_ordered_begin)(fh, buf, count, datatype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_ordered_begin fh=%ld buf=buf count=%d datatype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_write_ordered(MPI_File fh,void *buf,int count,MPI_Datatype datatype,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_write_ordered)(fh, buf, count, datatype, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_ordered fh=%ld buf=buf count=%d datatype=%s status=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_write_shared(MPI_File fh,void *buf,int count,MPI_Datatype datatype,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%ld", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_write_shared)(fh, buf, count, datatype, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_shared fh=%ld buf=buf count=%d datatype=%s status=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_read_all_end(MPI_File fh,void *buf,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_read_all_end)(fh, buf, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_all_end fh=%ld buf=buf status=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_read_at_all_end(MPI_File fh,void *buf,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_read_at_all_end)(fh, buf, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_at_all_end fh=%ld buf=buf status=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_read_ordered_end(MPI_File fh,void *buf,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_read_ordered_end)(fh, buf, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_ordered_end fh=%ld buf=buf status=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_write_all_end(MPI_File fh,void *buf,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_write_all_end)(fh, buf, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_all_end fh=%ld buf=buf status=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_write_at_all_end(MPI_File fh,void *buf,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_write_at_all_end)(fh, buf, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_at_all_end fh=%ld buf=buf status=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_write_ordered_end(MPI_File fh,void *buf,MPI_Status *status)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_write_ordered_end)(fh, buf, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_ordered_end fh=%ld buf=buf status=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, status);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_set_size(MPI_File fh,MPI_Offset size)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_set_size)(fh, size);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_set_size fh=%ld size=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, size);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_seek(MPI_File fh,MPI_Offset offset,int whence)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_seek)(fh, offset, whence);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_seek fh=%ld offset=%ld whence=%d \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, offset, whence);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_seek_shared(MPI_File fh,MPI_Offset offset,int whence)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_seek_shared)(fh, offset, whence);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_seek_shared fh=%ld offset=%ld whence=%d \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, offset, whence);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_preallocate(MPI_File fh,MPI_Offset size)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_preallocate)(fh, size);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_preallocate fh=%ld size=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, size);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_set_atomicity(MPI_File fh,int flag)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_set_atomicity)(fh, flag);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_set_atomicity fh=%ld flag=%d \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, flag);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Type_commit(MPI_Datatype *datatype)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Type_commit)(datatype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
sprintf(datatype_name, "%ld", *datatype);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Type_commit datatype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, datatype_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Type_contiguous(int count,MPI_Datatype oldtype,MPI_Datatype *newtype)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(oldtype, oldtype_name, &result_len);

		if (result_len == 0) {
			sprintf(oldtype_name, "%ld", oldtype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Type_contiguous)(count, oldtype, newtype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
sprintf(newtype_name, "%ld", *newtype);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Type_contiguous count=%d oldtype=%s newtype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, oldtype_name, newtype_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Type_create_darray(int size,int rank,int ndims,int array_of_gsizes[],int array_of_distribs[],int array_of_dargs[],int array_of_psizes[],int order,MPI_Datatype oldtype,MPI_Datatype *newtype)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(oldtype, oldtype_name, &result_len);

		if (result_len == 0) {
			sprintf(oldtype_name, "%ld", oldtype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Type_create_darray)(size, rank, ndims, array_of_gsizes, array_of_distribs, array_of_dargs, array_of_psizes, order, oldtype, newtype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
sprintf(newtype_name, "%ld", *newtype);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Type_create_darray size=%d rank=%d ndims=%d array_of_gsizes=%d array_of_distribs=%d array_of_dargs=%d array_of_psizes=%d order=%d oldtype=%s newtype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, size, rank, ndims, array_of_gsizes, array_of_distribs, array_of_dargs, array_of_psizes, order, oldtype_name, newtype_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Type_create_hindexed(int count,int array_of_blocklengths[],MPI_Aint array_of_displacements[],MPI_Datatype oldtype,MPI_Datatype *newtype)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(oldtype, oldtype_name, &result_len);

		if (result_len == 0) {
			sprintf(oldtype_name, "%ld", oldtype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Type_create_hindexed)(count, array_of_blocklengths, array_of_displacements, oldtype, newtype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
sprintf(newtype_name, "%ld", *newtype);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Type_create_hindexed count=%d array_of_blocklengths=%d array_of_displacements=%ld oldtype=%s newtype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, array_of_blocklengths, array_of_displacements, oldtype_name, newtype_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Type_create_hvector(int count,int blocklength,MPI_Aint stride,MPI_Datatype oldtype,MPI_Datatype *newtype)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(oldtype, oldtype_name, &result_len);

		if (result_len == 0) {
			sprintf(oldtype_name, "%ld", oldtype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Type_create_hvector)(count, blocklength, stride, oldtype, newtype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
sprintf(newtype_name, "%ld", *newtype);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Type_create_hvector count=%d blocklength=%d stride=%ld oldtype=%s newtype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, blocklength, stride, oldtype_name, newtype_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Type_create_indexed_block(int count,int blocklength,int array_of_displacements[],MPI_Datatype oldtype,MPI_Datatype *newtype)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(oldtype, oldtype_name, &result_len);

		if (result_len == 0) {
			sprintf(oldtype_name, "%ld", oldtype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Type_create_indexed_block)(count, blocklength, array_of_displacements, oldtype, newtype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
sprintf(newtype_name, "%ld", *newtype);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Type_create_indexed_block count=%d blocklength=%d array_of_displacements=%d oldtype=%s newtype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, blocklength, array_of_displacements, oldtype_name, newtype_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Type_create_resized(MPI_Datatype oldtype,MPI_Aint lb,MPI_Aint extent,MPI_Datatype *newtype)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(oldtype, oldtype_name, &result_len);

		if (result_len == 0) {
			sprintf(oldtype_name, "%ld", oldtype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Type_create_resized)(oldtype, lb, extent, newtype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
sprintf(newtype_name, "%ld", *newtype);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Type_create_resized oldtype=%s lb=%ld extent=%ld newtype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, oldtype_name, lb, extent, newtype_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Type_create_struct(int count,int array_of_blocklengths[],MPI_Aint array_of_displacements[],MPI_Datatype array_of_types[],MPI_Datatype *newtype)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Type_create_struct)(count, array_of_blocklengths, array_of_displacements, array_of_types, newtype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
sprintf(newtype_name, "%ld", *newtype);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Type_create_struct count=%d array_of_blocklengths=%d array_of_displacements=%ld array_of_types=%s newtype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, array_of_blocklengths, array_of_displacements, array_of_types, newtype_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Type_create_subarray(int ndims,int array_of_sizes[],int array_of_subsizes[],int array_of_starts[],int order,MPI_Datatype oldtype,MPI_Datatype *newtype)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(oldtype, oldtype_name, &result_len);

		if (result_len == 0) {
			sprintf(oldtype_name, "%ld", oldtype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Type_create_subarray)(ndims, array_of_sizes, array_of_subsizes, array_of_starts, order, oldtype, newtype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
sprintf(newtype_name, "%ld", *newtype);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Type_create_subarray ndims=%d array_of_sizes=%d array_of_subsizes=%d array_of_starts=%d order=%d oldtype=%s newtype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, ndims, array_of_sizes, array_of_subsizes, array_of_starts, order, oldtype_name, newtype_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Type_dup(MPI_Datatype type,MPI_Datatype *newtype)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Type_dup)(type, newtype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
sprintf(newtype_name, "%ld", *newtype);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Type_dup type=%s newtype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, type, newtype_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Type_free(MPI_Datatype *datatype)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Type_free)(datatype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
sprintf(datatype_name, "%ld", *datatype);
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Type_free datatype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, datatype_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Startall(int count,MPI_Request *array_of_requests)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Startall)(count, array_of_requests);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Startall count=%d array_of_requests=%ld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, array_of_requests);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Comm_rank(MPI_Comm comm,int *rank)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Comm_rank)(comm, rank);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Comm_rank comm=%s rank=rank \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Comm_size(MPI_Comm comm,int *size)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Comm_get_name(comm, comm_name, &result_len);
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Comm_size)(comm, size);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = sprintf(rec_buffer + written_bytes, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Comm_size comm=%s size=size \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, comm_name);
	read_func(sc, rec_buffer);
	write_or_compress(sc);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

