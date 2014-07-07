/* 
 * This file is generated automaticaly by a wrapper generator,
 * Do not edit it manually.
 * define neccessary variables below
 */

//#define _GNU_SOURCE
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

//#define _XOPEN_SOURCE 500
//#define _GNU_SOURCE /* for tdestroy() */

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

   ::begin = recorder_wtime();

   RECORDER_MPI_CALL(PMPI_Comm_size)(MPI_COMM_WORLD, &nprocs);
   RECORDER_MPI_CALL(PMPI_Comm_rank)(MPI_COMM_WORLD, &rank);

   char logfile_name[PATH_MAX] = {0};
   char logdir_name[PATH_MAX] = {0};
   char aux_file_name[PATH_MAX] = {0};
   char cuser[L_cuserid] = {0};
   cuserid(cuser);

   /** shouldn't be freed **/
   char* OutDir = getenv("RECORDER_OUTDIR");
   if(OutDir)
      snprintf(logdir_name, sizeof(logdir_name), "%s", OutDir);
   else
      snprintf(logdir_name, sizeof(logdir_name), "%s_%s_%lu", cuser, __progname, time(0));
   int status;
   status = mkdir(logdir_name, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
   sprintf(logfile_name,"%s/log.%d",logdir_name,rank);
   __recorderfh=fopen(logfile_name,"w");

   sprintf(aux_file_name, "%s/aux.%d", logdir_name, rank);
   __auxiliaryfh = fopen(aux_file_name, "w");

   printf(" logfile_name %s ,recorderfh %d\n",logfile_name,__recorderfh);

   // initialize sc
   create_sc_by_filename(&sc, logfile_name);

   tm4 = recorder_wtime();

   return;
}

void recorder_shutdown(int timing_flag)
{
   ::end = recorder_wtime();
   struct timespec all = ::end - ::begin;

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

#include "MPI_wrapper.cpp"
