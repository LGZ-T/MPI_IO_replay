/* 
 * This file is generated automaticaly by a wrapper generator,
 * Do not edit it manually.
 * define neccessary variables below
 */

#define _GNU_SOURCE
#include <mpi.h>
#include "simple_compress.h"
SimpleCompress *sc;

struct timespec tm1, tm2, tm3, tm4, compute_time, mpi_time, this_func_time;
struct timespec compute_time_all, mpi_time_all, recorder_time_all;
struct timespec write_time_all, read_time_all;
int ret, result_len, array_size, s_offset;
char comm_name[100], newcomm_name[100], etype_name[100], filetype_name[100], datatype_name[100], oldtype_name[100], newtype_name[100], temp_datatype_name[100];
#define AS 300000
char array_of_requests_arraystore[AS], array_of_gsizes_arraystore[AS], array_of_distribs_arraystore[AS], array_of_dargs_arraystore[AS], array_of_psizes_arraystore[AS], array_of_sizes_arraystore[AS], array_of_subsizes_arraystore[AS], array_of_starts_arraystore[AS], array_of_blocklengths_arraystore[AS], array_of_displacements_arraystore[AS], array_of_types_arraystore[AS];
#define BUFFER_SIZE 4096
const int threshold = BUFFER_SIZE * 0.9;
int bytes, written_bytes;
char rec_buffer[4096];

#include <mpi.h>
MPI_Datatype* temp_datatype;
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
FILE *__auxiliaryfh;	// store the overall time info of each program and the speed of the machine

struct timespec ts;
struct timespec begin, end;

struct timespec recorder_wtime(void)
{
	clock_gettime(CLOCK_MONOTONIC, &ts);

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

    begin = recorder_wtime();

    RECORDER_MPI_CALL(PMPI_Comm_size)(MPI_COMM_WORLD, &nprocs);
    RECORDER_MPI_CALL(PMPI_Comm_rank)(MPI_COMM_WORLD, &rank);

    char *logfile_name;
    char *logdir_name;
    logfile_name=(char*)malloc(PATH_MAX);
    logdir_name=(char*)malloc(PATH_MAX);
    char cuser[L_cuserid] = {0};
    cuserid(cuser);

	time_t tt = time(NULL);
	struct tm *h = localtime(&tt);
    sprintf(logdir_name,"%s_%s_%02d%02d%02d",cuser, __progname, h->tm_mon, h->tm_mday, h->tm_hour);
    int status;
    status = mkdir(logdir_name, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    sprintf(logfile_name,"%s/log.%d",logdir_name,rank);
    __recorderfh=fopen(logfile_name,"w");

    char *aux_file_name = (char*)malloc(PATH_MAX);
    sprintf(aux_file_name, "%s/aux.%d", logdir_name, rank);
    __auxiliaryfh = fopen(aux_file_name, "w");

    printf(" logfile_name %s ,recorderfh %d\n",logfile_name,__recorderfh);

	// initialize sc
	create_sc_by_filename(&sc, logfile_name);

    free(logfile_name);
    free(logdir_name);

    tm4 = recorder_wtime();

    return;
}

void recorder_shutdown(int timing_flag)
{
	end = recorder_wtime();
	struct timespec all = end - begin;

	delete_sc(sc);
	fflush(__recorderfh);
    fclose(__recorderfh);

    struct timespec start_time = recorder_wtime();
    for (int i=0; i<1000000000; i++)
    	;
	struct timespec end_time = recorder_wtime();
	struct timespec loop_time = end_time - start_time;
	long nano = loop_time.tv_nsec + loop_time.tv_sec * 1000000000;
	double ratio = (double)nano / 1000000000;

	fprintf(__auxiliaryfh, "Ratio=%lf\n", ratio);
	fprintf(__auxiliaryfh, "Compute_time=%ld.%.9ld MPI_Call_time=%ld.%.9ld Recorder_time=%ld.%.9ld Read_time=%ld.%.9ld Write_time=%ld.%.9ld\n", compute_time_all, mpi_time_all, recorder_time_all, read_time_all, write_time_all);
	fprintf(__auxiliaryfh, "All_time=%ld.%09ld", all.tv_sec, all.tv_nsec);
	fclose(__auxiliaryfh);

    return;
}
int MPI_Comm_free(MPI_Comm *comm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Comm_free)(comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
sprintf(comm_name, "%lu", *comm);
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Comm_free comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, comm_name);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Comm_dup(MPI_Comm comm,MPI_Comm *newcomm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Comm_get_name(comm, comm_name, &result_len);

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Comm_dup)(comm, newcomm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
sprintf(newcomm_name, "%lu", *newcomm);
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Comm_dup comm=%s newcomm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, comm_name, newcomm_name);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Comm_split(MPI_Comm comm,int color,int key,MPI_Comm *newcomm)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Comm_get_name(comm, comm_name, &result_len);

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Comm_split)(comm, color, key, newcomm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
sprintf(newcomm_name, "%lu", *newcomm);
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Comm_split comm=%s color=%d key=%d newcomm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, comm_name, color, key, newcomm_name);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Ibsend(void *buf,int count,MPI_Datatype datatype,int dest,int tag,MPI_Comm comm,MPI_Request *request)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
PMPI_Type_get_name(datatype, datatype_name, &result_len);

		if (result_len == 0) {
			sprintf(datatype_name, "%lu", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Ibsend)(buf, count, datatype, dest, tag, comm, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Ibsend buf=buf count=%d datatype=%s dest=%d tag=%d comm=%s request=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, tag, comm_name, *request);
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
			sprintf(datatype_name, "%lu", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Irsend)(buf, count, datatype, dest, tag, comm, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Irsend buf=buf count=%d datatype=%s dest=%d tag=%d comm=%s request=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, tag, comm_name, *request);
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
			sprintf(datatype_name, "%lu", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Issend)(buf, count, datatype, dest, tag, comm, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Issend buf=buf count=%d datatype=%s dest=%d tag=%d comm=%s request=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, tag, comm_name, *request);
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
			sprintf(datatype_name, "%lu", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Isend)(buf, count, datatype, dest, tag, comm, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Isend buf=buf count=%d datatype=%s dest=%d tag=%d comm=%s request=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, tag, comm_name, *request);
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
			sprintf(datatype_name, "%lu", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Irecv)(buf, count, datatype, source, tag, comm, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Irecv buf=buf count=%d datatype=%s source=%d tag=%d comm=%s request=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, source, tag, comm_name, *request);
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
			sprintf(datatype_name, "%lu", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Send)(buf, count, datatype, dest, tag, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Send buf=buf count=%d datatype=%s dest=%d tag=%d comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, tag, comm_name);
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
			sprintf(datatype_name, "%lu", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Send_init)(buf, count, datatype, dest, tag, comm, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Send_init buf=buf count=%d datatype=%s dest=%d tag=%d comm=%s request=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, tag, comm_name, *request);
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

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Sendrecv)(sendbuf, sendcount, sendtype, dest, sendtag, recvbuf, recvcount, recvtype, source, recvtag, comm, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Sendrecv sendbuf=sendbuf sendcount=%d sendtype=%s dest=%d sendtag=%d recvbuf=recvbuf recvcount=%d recvtype=%s source=%d recvtag=%d comm=%s status=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, sendcount, sendtype, dest, sendtag, recvcount, recvtype, source, recvtag, comm_name, status);
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
			sprintf(datatype_name, "%lu", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Sendrecv_replace)(buf, count, datatype, dest, sendtag, source, recvtag, comm, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Sendrecv_replace buf=buf count=%d datatype=%s dest=%d sendtag=%d source=%d recvtag=%d comm=%s status=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, sendtag, source, recvtag, comm_name, status);
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
			sprintf(datatype_name, "%lu", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Ssend)(buf, count, datatype, dest, tag, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Ssend buf=buf count=%d datatype=%s dest=%d tag=%d comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, tag, comm_name);
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
			sprintf(datatype_name, "%lu", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Ssend_init)(buf, count, datatype, dest, tag, comm, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Ssend_init buf=buf count=%d datatype=%s dest=%d tag=%d comm=%s request=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, tag, comm_name, *request);
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
			sprintf(datatype_name, "%lu", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Rsend)(buf, count, datatype, dest, tag, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Rsend buf=buf count=%d datatype=%s dest=%d tag=%d comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, tag, comm_name);
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
			sprintf(datatype_name, "%lu", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Rsend_init)(buf, count, datatype, dest, tag, comm, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Rsend_init buf=buf count=%d datatype=%s dest=%d tag=%d comm=%s request=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, tag, comm_name, *request);
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
			sprintf(datatype_name, "%lu", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Bsend)(buf, count, datatype, dest, tag, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Bsend buf=buf count=%d datatype=%s dest=%d tag=%d comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, tag, comm_name);
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
			sprintf(datatype_name, "%lu", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Bsend_init)(buf, count, datatype, dest, tag, comm, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Bsend_init buf=buf count=%d datatype=%s dest=%d tag=%d comm=%s request=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, dest, tag, comm_name, *request);
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
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Start request=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, *request);
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
			sprintf(datatype_name, "%lu", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Recv)(buf, count, datatype, source, tag, comm, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Recv buf=buf count=%d datatype=%s source=%d tag=%d comm=%s status=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, source, tag, comm_name, status);
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
			sprintf(datatype_name, "%lu", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Recv_init)(buf, count, datatype, source, tag, comm, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Recv_init buf=buf count=%d datatype=%s source=%d tag=%d comm=%s request=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, source, tag, comm_name, *request);
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
			sprintf(datatype_name, "%lu", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Allreduce)(sendbuf, recvbuf, count, datatype, op, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Allreduce sendbuf=sendbuf recvbuf=recvbuf count=%d datatype=%s op=%lu comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, op, comm_name);
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

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Allgather)(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Allgather sendbuf=sendbuf sendcount=%d sendtype=%s recvbuf=recvbuf recvcount=%d recvtype=%s comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, sendcount, sendtype, recvcount, recvtype, comm_name);
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

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Allgatherv)(sendbuf, sendcount, sendtype, recvbuf, recvcount, displs, recvtype, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Allgatherv sendbuf=sendbuf sendcount=%d sendtype=%s recvbuf=recvbuf recvcount=recvcount displs=displs recvtype=%s comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, sendcount, sendtype, recvtype, comm_name);
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

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Alltoall)(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Alltoall sendbuf=sendbuf sendcount=%d sendtype=%s recvbuf=recvbuf recvcount=%d recvtype=%s comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, sendcount, sendtype, recvcount, recvtype, comm_name);
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

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Alltoallv)(sendbuf, sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Alltoallv sendbuf=sendbuf sendcounts=sendcounts sdispls=sdispls sendtype=%s recvbuf=recvbuf recvcounts=recvcounts rdispls=rdispls recvtype=%s comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, sendtype, recvtype, comm_name);
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

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Alltoallw)(sendbuf, sendcounts, sdispls, sendtypes, recvbuf, recvcounts, rdispls, recvtypes, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Alltoallw sendbuf=sendbuf sendcounts=sendcounts sdispls=sdispls sendtypes=%lu recvbuf=recvbuf recvcounts=recvcounts rdispls=rdispls recvtypes=%lu comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, sendtypes, recvtypes, comm_name);
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

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Barrier)(comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Barrier comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, comm_name);
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

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Gather)(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Gather sendbuf=sendbuf sendcount=%d sendtype=%s recvbuf=recvbuf recvcount=%d recvtype=%s root=%d comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, sendcount, sendtype, recvcount, recvtype, root, comm_name);
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

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Gatherv)(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Gatherv sendbuf=sendbuf sendcount=%d sendtype=%s recvbuf=recvbuf recvcounts=recvcounts displs=displs recvtype=%s root=%d comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, sendcount, sendtype, recvtype, root, comm_name);
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

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Scatter)(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Scatter sendbuf=sendbuf sendcount=%d sendtype=%s recvbuf=recvbuf recvcount=%d recvtype=%s root=%d comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, sendcount, sendtype, recvcount, recvtype, root, comm_name);
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

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Scatterv)(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Scatterv sendbuf=sendbuf sendcounts=sendcounts displs=displs sendtype=%s recvbuf=recvbuf recvcount=%d recvtype=%s root=%d comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, sendtype, recvcount, recvtype, root, comm_name);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Wait(MPI_Request *request,MPI_Status *status)
{
	MPI_Request real_request = *request;
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Wait)(request, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Wait request=%lu status=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, real_request, status);
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
array_size = count;
s_offset += sprintf(array_of_requests_arraystore+s_offset, "%d-", array_size);
for(int i=0; i<array_size; i++) {
	s_offset += sprintf(array_of_requests_arraystore+s_offset, "%lu", *(array_of_requests+i));
	s_offset += sprintf(array_of_requests_arraystore+s_offset, "-");
}
s_offset = 0;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Waitall)(count, array_of_requests, array_of_statuses);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Waitall count=%d array_of_requests=%s array_of_statuses=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, array_of_requests_arraystore, *array_of_statuses);
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
array_size = count;
s_offset += sprintf(array_of_requests_arraystore+s_offset, "%d-", array_size);
for(int i=0; i<array_size; i++) {
	s_offset += sprintf(array_of_requests_arraystore+s_offset, "%lu", *(array_of_requests+i));
	s_offset += sprintf(array_of_requests_arraystore+s_offset, "-");
}
s_offset = 0;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Waitany)(count, array_of_requests, index, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Waitany count=%d array_of_requests=%s index=index status=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, array_of_requests_arraystore, status);
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
			sprintf(datatype_name, "%lu", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Bcast)(buffer, count, datatype, root, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Bcast buffer=buffer count=%d datatype=%s root=%d comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, root, comm_name);
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
			sprintf(datatype_name, "%lu", datatype);
		}
		PMPI_Comm_get_name(comm, comm_name, &result_len);

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Reduce)(sendbuf, recvbuf, count, datatype, op, root, comm);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Reduce sendbuf=sendbuf recvbuf=recvbuf count=%d datatype=%s op=%lu root=%d comm=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, datatype_name, op, root, comm_name);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_File_close(MPI_File *fh)
{
	MPI_File real_fh = *fh;
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_close)(fh);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_close fh=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, real_fh);
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
			sprintf(datatype_name, "%lu", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_iread_at)(fh, offset, buf, count, datatype, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	read_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_iread_at fh=%lu offset=%lld buf=buf count=%d datatype=%s request=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, offset, count, datatype_name, request);
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
			sprintf(datatype_name, "%lu", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_iread)(fh, buf, count, datatype, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	read_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_iread fh=%lu buf=buf count=%d datatype=%s request=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name, request);
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
			sprintf(datatype_name, "%lu", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_iread_shared)(fh, buf, count, datatype, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	read_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_iread_shared fh=%lu buf=buf count=%d datatype=%s request=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name, request);
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
			sprintf(datatype_name, "%lu", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_iwrite_at)(fh, offset, buf, count, datatype, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	write_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_iwrite_at fh=%lu offset=%lld buf=buf count=%d datatype=%s request=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, offset, count, datatype_name, request);
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
			sprintf(datatype_name, "%lu", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_iwrite)(fh, buf, count, datatype, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	write_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_iwrite fh=%lu buf=buf count=%d datatype=%s request=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name, request);
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
			sprintf(datatype_name, "%lu", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_iwrite_shared)(fh, buf, count, datatype, request);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	write_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_iwrite_shared fh=%lu buf=buf count=%d datatype=%s request=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name, request);
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

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_open)(comm, filename, amode, info, fh);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_open comm=%s filename=%s amode=%d info=%lu fh=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, comm_name, filename, amode, info, *fh);
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
			sprintf(datatype_name, "%lu", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_read_all_begin)(fh, buf, count, datatype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	read_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_all_begin fh=%lu buf=buf count=%d datatype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name);
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
			sprintf(datatype_name, "%lu", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_read_all)(fh, buf, count, datatype, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	read_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_all fh=%lu buf=buf count=%d datatype=%s status=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name, status);
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
			sprintf(datatype_name, "%lu", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_read_at_all)(fh, offset, buf, count, datatype, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	read_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_at_all fh=%lu offset=%lld buf=buf count=%d datatype=%s status=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, offset, count, datatype_name, status);
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
			sprintf(datatype_name, "%lu", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_read_at_all_begin)(fh, offset, buf, count, datatype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	read_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_at_all_begin fh=%lu offset=%lld buf=buf count=%d datatype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, offset, count, datatype_name);
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
			sprintf(datatype_name, "%lu", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_read_at)(fh, offset, buf, count, datatype, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	read_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_at fh=%lu offset=%lld buf=buf count=%d datatype=%s status=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, offset, count, datatype_name, status);
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
			sprintf(datatype_name, "%lu", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_read)(fh, buf, count, datatype, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	read_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read fh=%lu buf=buf count=%d datatype=%s status=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name, status);
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
			sprintf(datatype_name, "%lu", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_read_ordered_begin)(fh, buf, count, datatype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	read_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_ordered_begin fh=%lu buf=buf count=%d datatype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name);
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
			sprintf(datatype_name, "%lu", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_read_ordered)(fh, buf, count, datatype, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	read_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_ordered fh=%lu buf=buf count=%d datatype=%s status=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name, status);
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
			sprintf(datatype_name, "%lu", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_read_shared)(fh, buf, count, datatype, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	read_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_shared fh=%lu buf=buf count=%d datatype=%s status=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name, status);
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
			sprintf(etype_name, "%lu", etype);
		}
		PMPI_Type_get_name(filetype, filetype_name, &result_len);

		if (result_len == 0) {
			sprintf(filetype_name, "%lu", filetype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_set_view)(fh, disp, etype, filetype, datarep, info);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_set_view fh=%lu disp=%lld etype=%s filetype=%s datarep=%s info=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, disp, etype_name, filetype_name, datarep, info);
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
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_sync fh=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh);
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
			sprintf(datatype_name, "%lu", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_write_all_begin)(fh, buf, count, datatype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	write_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_all_begin fh=%lu buf=buf count=%d datatype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name);
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
			sprintf(datatype_name, "%lu", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_write_all)(fh, buf, count, datatype, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	write_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_all fh=%lu buf=buf count=%d datatype=%s status=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name, status);
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
			sprintf(datatype_name, "%lu", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_write_at_all_begin)(fh, offset, buf, count, datatype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	write_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_at_all_begin fh=%lu offset=%lld buf=buf count=%d datatype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, offset, count, datatype_name);
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
			sprintf(datatype_name, "%lu", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_write_at_all)(fh, offset, buf, count, datatype, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	write_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_at_all fh=%lu offset=%lld buf=buf count=%d datatype=%s status=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, offset, count, datatype_name, status);
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
			sprintf(datatype_name, "%lu", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_write_at)(fh, offset, buf, count, datatype, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	write_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_at fh=%lu offset=%lld buf=buf count=%d datatype=%s status=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, offset, count, datatype_name, status);
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
			sprintf(datatype_name, "%lu", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_write)(fh, buf, count, datatype, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	write_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write fh=%lu buf=buf count=%d datatype=%s status=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name, status);
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
			sprintf(datatype_name, "%lu", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_write_ordered_begin)(fh, buf, count, datatype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	write_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_ordered_begin fh=%lu buf=buf count=%d datatype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name);
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
			sprintf(datatype_name, "%lu", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_write_ordered)(fh, buf, count, datatype, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	write_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_ordered fh=%lu buf=buf count=%d datatype=%s status=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name, status);
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
			sprintf(datatype_name, "%lu", datatype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_File_write_shared)(fh, buf, count, datatype, status);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	write_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_shared fh=%lu buf=buf count=%d datatype=%s status=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, count, datatype_name, status);
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
	read_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_all_end fh=%lu buf=buf status=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, status);
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
	read_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_at_all_end fh=%lu buf=buf status=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, status);
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
	read_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_read_ordered_end fh=%lu buf=buf status=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, status);
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
	write_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_all_end fh=%lu buf=buf status=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, status);
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
	write_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_at_all_end fh=%lu buf=buf status=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, status);
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
	write_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_write_ordered_end fh=%lu buf=buf status=%lu \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, status);
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
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_set_size fh=%lu size=%lld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, size);
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
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_seek fh=%lu offset=%lld whence=%d \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, offset, whence);
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
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_seek_shared fh=%lu offset=%lld whence=%d \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, offset, whence);
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
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_preallocate fh=%lu size=%lld \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, size);
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
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_File_set_atomicity fh=%lu flag=%d \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, fh, flag);
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
sprintf(datatype_name, "%lu", *datatype);
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Type_commit datatype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, datatype_name);
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
			sprintf(oldtype_name, "%lu", oldtype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Type_contiguous)(count, oldtype, newtype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
sprintf(newtype_name, "%lu", *newtype);
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Type_contiguous count=%d oldtype=%s newtype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, oldtype_name, newtype_name);
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
			sprintf(oldtype_name, "%lu", oldtype);
		}
		array_size = ndims;
s_offset += sprintf(array_of_gsizes_arraystore+s_offset, "%d-", array_size);
for(int i=0; i<array_size; i++) {
	s_offset += sprintf(array_of_gsizes_arraystore+s_offset, "%d", *(array_of_gsizes+i));
	s_offset += sprintf(array_of_gsizes_arraystore+s_offset, "-");
}
s_offset = 0;
s_offset += sprintf(array_of_distribs_arraystore+s_offset, "%d-", array_size);
for(int i=0; i<array_size; i++) {
	s_offset += sprintf(array_of_distribs_arraystore+s_offset, "%d", *(array_of_distribs+i));
	s_offset += sprintf(array_of_distribs_arraystore+s_offset, "-");
}
s_offset = 0;
s_offset += sprintf(array_of_dargs_arraystore+s_offset, "%d-", array_size);
for(int i=0; i<array_size; i++) {
	s_offset += sprintf(array_of_dargs_arraystore+s_offset, "%d", *(array_of_dargs+i));
	s_offset += sprintf(array_of_dargs_arraystore+s_offset, "-");
}
s_offset = 0;
s_offset += sprintf(array_of_psizes_arraystore+s_offset, "%d-", array_size);
for(int i=0; i<array_size; i++) {
	s_offset += sprintf(array_of_psizes_arraystore+s_offset, "%d", *(array_of_psizes+i));
	s_offset += sprintf(array_of_psizes_arraystore+s_offset, "-");
}
s_offset = 0;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Type_create_darray)(size, rank, ndims, array_of_gsizes, array_of_distribs, array_of_dargs, array_of_psizes, order, oldtype, newtype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
sprintf(newtype_name, "%lu", *newtype);
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Type_create_darray size=%d rank=%d ndims=%d array_of_gsizes=%s array_of_distribs=%s array_of_dargs=%s array_of_psizes=%s order=%d oldtype=%s newtype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, size, rank, ndims, array_of_gsizes_arraystore, array_of_distribs_arraystore, array_of_dargs_arraystore, array_of_psizes_arraystore, order, oldtype_name, newtype_name);
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
			sprintf(oldtype_name, "%lu", oldtype);
		}
		array_size = count;
s_offset += sprintf(array_of_blocklengths_arraystore+s_offset, "%d-", array_size);
for(int i=0; i<array_size; i++) {
	s_offset += sprintf(array_of_blocklengths_arraystore+s_offset, "%d", *(array_of_blocklengths+i));
	s_offset += sprintf(array_of_blocklengths_arraystore+s_offset, "-");
}
s_offset = 0;
s_offset += sprintf(array_of_displacements_arraystore+s_offset, "%d-", array_size);
for(int i=0; i<array_size; i++) {
	s_offset += sprintf(array_of_displacements_arraystore+s_offset, "%ld", *(array_of_displacements+i));
	s_offset += sprintf(array_of_displacements_arraystore+s_offset, "-");
}
s_offset = 0;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Type_create_hindexed)(count, array_of_blocklengths, array_of_displacements, oldtype, newtype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
sprintf(newtype_name, "%lu", *newtype);
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Type_create_hindexed count=%d array_of_blocklengths=%s array_of_displacements=%s oldtype=%s newtype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, array_of_blocklengths_arraystore, array_of_displacements_arraystore, oldtype_name, newtype_name);
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
			sprintf(oldtype_name, "%lu", oldtype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Type_create_hvector)(count, blocklength, stride, oldtype, newtype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
sprintf(newtype_name, "%lu", *newtype);
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Type_create_hvector count=%d blocklength=%d stride=%ld oldtype=%s newtype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, blocklength, stride, oldtype_name, newtype_name);
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
			sprintf(oldtype_name, "%lu", oldtype);
		}
		array_size = count;
s_offset += sprintf(array_of_displacements_arraystore+s_offset, "%d-", array_size);
for(int i=0; i<array_size; i++) {
	s_offset += sprintf(array_of_displacements_arraystore+s_offset, "%d", *(array_of_displacements+i));
	s_offset += sprintf(array_of_displacements_arraystore+s_offset, "-");
}
s_offset = 0;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Type_create_indexed_block)(count, blocklength, array_of_displacements, oldtype, newtype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
sprintf(newtype_name, "%lu", *newtype);
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Type_create_indexed_block count=%d blocklength=%d array_of_displacements=%s oldtype=%s newtype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, blocklength, array_of_displacements_arraystore, oldtype_name, newtype_name);
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
			sprintf(oldtype_name, "%lu", oldtype);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Type_create_resized)(oldtype, lb, extent, newtype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
sprintf(newtype_name, "%lu", *newtype);
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Type_create_resized oldtype=%s lb=%ld extent=%ld newtype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, oldtype_name, lb, extent, newtype_name);
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
array_size = count;
s_offset += sprintf(array_of_blocklengths_arraystore+s_offset, "%d-", array_size);
for(int i=0; i<array_size; i++) {
	s_offset += sprintf(array_of_blocklengths_arraystore+s_offset, "%d", *(array_of_blocklengths+i));
	s_offset += sprintf(array_of_blocklengths_arraystore+s_offset, "-");
}
s_offset = 0;
s_offset += sprintf(array_of_displacements_arraystore+s_offset, "%d-", array_size);
for(int i=0; i<array_size; i++) {
	s_offset += sprintf(array_of_displacements_arraystore+s_offset, "%ld", *(array_of_displacements+i));
	s_offset += sprintf(array_of_displacements_arraystore+s_offset, "-");
}
s_offset = 0;
s_offset += sprintf(array_of_types_arraystore+s_offset, "%d-", array_size);
for(int i=0; i<array_size; i++) {
temp_datatype = (array_of_types+i);sprintf(temp_datatype_name, "%lu", *temp_datatype);
	s_offset += sprintf(array_of_types_arraystore+s_offset, "%s", temp_datatype_name);
	s_offset += sprintf(array_of_types_arraystore+s_offset, "-");
}
s_offset = 0;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Type_create_struct)(count, array_of_blocklengths, array_of_displacements, array_of_types, newtype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
sprintf(newtype_name, "%lu", *newtype);
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Type_create_struct count=%d array_of_blocklengths=%s array_of_displacements=%s array_of_types=%s newtype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, array_of_blocklengths_arraystore, array_of_displacements_arraystore, array_of_types_arraystore, newtype_name);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

int MPI_Type_struct(int count,int *array_of_blocklengths,MPI_Aint *array_of_displacements,MPI_Datatype *array_of_types,MPI_Datatype *newtype)
{
	/* tm1 is the length of time elapsed between the IO or MPI communication calls. It's spend in computing */
	tm1 = recorder_wtime();
	compute_time = tm1 - tm4;
	compute_time_all += compute_time;
array_size = count;
s_offset += sprintf(array_of_blocklengths_arraystore+s_offset, "%d-", array_size);
for(int i=0; i<array_size; i++) {
	s_offset += sprintf(array_of_blocklengths_arraystore+s_offset, "%d", *(array_of_blocklengths+i));
	s_offset += sprintf(array_of_blocklengths_arraystore+s_offset, "-");
}
s_offset = 0;
s_offset += sprintf(array_of_displacements_arraystore+s_offset, "%d-", array_size);
for(int i=0; i<array_size; i++) {
	s_offset += sprintf(array_of_displacements_arraystore+s_offset, "%ld", *(array_of_displacements+i));
	s_offset += sprintf(array_of_displacements_arraystore+s_offset, "-");
}
s_offset = 0;
s_offset += sprintf(array_of_types_arraystore+s_offset, "%d-", array_size);
for(int i=0; i<array_size; i++) {
temp_datatype = (array_of_types+i);sprintf(temp_datatype_name, "%lu", *temp_datatype);
	s_offset += sprintf(array_of_types_arraystore+s_offset, "%s", temp_datatype_name);
	s_offset += sprintf(array_of_types_arraystore+s_offset, "-");
}
s_offset = 0;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Type_struct)(count, array_of_blocklengths, array_of_displacements, array_of_types, newtype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
sprintf(newtype_name, "%lu", *newtype);
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Type_struct count=%d array_of_blocklengths=%s array_of_displacements=%s array_of_types=%s newtype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, array_of_blocklengths_arraystore, array_of_displacements_arraystore, array_of_types_arraystore, newtype_name);
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
			sprintf(oldtype_name, "%lu", oldtype);
		}
		array_size = ndims;
s_offset += sprintf(array_of_sizes_arraystore+s_offset, "%d-", array_size);
for(int i=0; i<array_size; i++) {
	s_offset += sprintf(array_of_sizes_arraystore+s_offset, "%d", *(array_of_sizes+i));
	s_offset += sprintf(array_of_sizes_arraystore+s_offset, "-");
}
s_offset = 0;
s_offset += sprintf(array_of_subsizes_arraystore+s_offset, "%d-", array_size);
for(int i=0; i<array_size; i++) {
	s_offset += sprintf(array_of_subsizes_arraystore+s_offset, "%d", *(array_of_subsizes+i));
	s_offset += sprintf(array_of_subsizes_arraystore+s_offset, "-");
}
s_offset = 0;
s_offset += sprintf(array_of_starts_arraystore+s_offset, "%d-", array_size);
for(int i=0; i<array_size; i++) {
	s_offset += sprintf(array_of_starts_arraystore+s_offset, "%d", *(array_of_starts+i));
	s_offset += sprintf(array_of_starts_arraystore+s_offset, "-");
}
s_offset = 0;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Type_create_subarray)(ndims, array_of_sizes, array_of_subsizes, array_of_starts, order, oldtype, newtype);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
sprintf(newtype_name, "%lu", *newtype);
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Type_create_subarray ndims=%d array_of_sizes=%s array_of_subsizes=%s array_of_starts=%s order=%d oldtype=%s newtype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, ndims, array_of_sizes_arraystore, array_of_subsizes_arraystore, array_of_starts_arraystore, order, oldtype_name, newtype_name);
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
sprintf(newtype_name, "%lu", *newtype);
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Type_dup type=%s newtype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, type, newtype_name);
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
sprintf(datatype_name, "%lu", *datatype);
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Type_free datatype=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, datatype_name);
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
array_size = count;
s_offset += sprintf(array_of_requests_arraystore+s_offset, "%d-", array_size);
for(int i=0; i<array_size; i++) {
	s_offset += sprintf(array_of_requests_arraystore+s_offset, "%lu", *(array_of_requests+i));
	s_offset += sprintf(array_of_requests_arraystore+s_offset, "-");
}
s_offset = 0;
	tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Startall)(count, array_of_requests);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Startall count=%d array_of_requests=%s \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, count, array_of_requests_arraystore);
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

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Comm_rank)(comm, rank);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Comm_rank comm=%s rank=rank \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, comm_name);
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

		if (result_len == 0) {
			sprintf(comm_name, "%lu", comm);
		}
			tm2 = recorder_wtime();
	ret = RECORDER_MPI_CALL(PMPI_Comm_size)(comm, size);
	tm3 = recorder_wtime();
	mpi_time = tm3 - tm2;
	mpi_time_all += mpi_time;
	bytes = fprintf(__recorderfh, "tm1=%ld.%.9ld tm2=%ld.%.9ld func=MPI_Comm_size comm=%s size=size \n",  compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec, comm_name);
	this_func_time = recorder_wtime() - tm1;
	recorder_time_all += this_func_time - mpi_time;
;	/* tm4 stands for the true exit moment of this function */
	tm4 = recorder_wtime();
	return ret;
}

