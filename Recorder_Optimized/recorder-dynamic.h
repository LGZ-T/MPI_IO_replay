/*
 *  (C) 2012 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */

#ifndef __RECORDER_DYNAMIC_H
#define __RECORDER_DYNAMIC_H

#ifdef RECORDER_PRELOAD

#include <dlfcn.h>
#include <stdlib.h>

#define RECORDER_MPI_CALL(func) __real_ ## func
//#define RECORDER_MPI_CALL(func)

#define RECORDER_EXTERN_DECL(name,ret,args) \
  extern ret (*__real_ ## name)args;

RECORDER_EXTERN_DECL(PMPI_File_close, int, (MPI_File *fh));
RECORDER_EXTERN_DECL(PMPI_File_set_size, int, (MPI_File fh, MPI_Offset size));
RECORDER_EXTERN_DECL(PMPI_File_iread_at, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST *request));
RECORDER_EXTERN_DECL(PMPI_File_iread, int, (MPI_File fh, void  *buf, int  count, MPI_Datatype  datatype, __D_MPI_REQUEST  *request));
RECORDER_EXTERN_DECL(PMPI_File_iread_shared, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST *request));
RECORDER_EXTERN_DECL(PMPI_File_iwrite_at, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST *request));
RECORDER_EXTERN_DECL(PMPI_File_iwrite, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST *request));
RECORDER_EXTERN_DECL(PMPI_File_iwrite_shared, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST *request));
RECORDER_EXTERN_DECL(PMPI_File_open, int, (MPI_Comm comm, char *filename, int amode, MPI_Info info, MPI_File *fh));
RECORDER_EXTERN_DECL(PMPI_File_read_all_begin, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype));
RECORDER_EXTERN_DECL(PMPI_File_read_all, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_EXTERN_DECL(PMPI_File_read_at_all, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_EXTERN_DECL(PMPI_File_read_at_all_begin, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype));
RECORDER_EXTERN_DECL(PMPI_File_read_at, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_EXTERN_DECL(PMPI_File_read, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_EXTERN_DECL(PMPI_File_read_ordered_begin, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype));
RECORDER_EXTERN_DECL(PMPI_File_read_ordered, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_EXTERN_DECL(PMPI_File_read_shared, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_EXTERN_DECL(PMPI_File_set_view, int, (MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, char *datarep, MPI_Info info));
RECORDER_EXTERN_DECL(PMPI_File_sync, int, (MPI_File fh));
RECORDER_EXTERN_DECL(PMPI_File_write_all_begin, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype));
RECORDER_EXTERN_DECL(PMPI_File_write_all, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_EXTERN_DECL(PMPI_File_write_at_all_begin, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype));
RECORDER_EXTERN_DECL(PMPI_File_write_at_all, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_EXTERN_DECL(PMPI_File_write_at, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_EXTERN_DECL(PMPI_File_write, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_EXTERN_DECL(PMPI_File_write_ordered_begin, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype));
RECORDER_EXTERN_DECL(PMPI_File_write_ordered, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_EXTERN_DECL(PMPI_File_write_shared, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
RECORDER_EXTERN_DECL(PMPI_Finalize, int, ());
RECORDER_EXTERN_DECL(PMPI_Init, int, (int *argc, char ***argv));
RECORDER_EXTERN_DECL(PMPI_Init_thread, int, (int *argc, char ***argv, int required, int *provided));

RECORDER_EXTERN_DECL(PMPI_Wtime, double, ());
RECORDER_EXTERN_DECL(PMPI_Allreduce, int, (void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm));
RECORDER_EXTERN_DECL(PMPI_Bcast, int, (void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm));
RECORDER_EXTERN_DECL(PMPI_Comm_rank, int, (MPI_Comm comm, int *rank));
RECORDER_EXTERN_DECL(PMPI_Comm_size, int, (MPI_Comm comm, int *size));
RECORDER_EXTERN_DECL(PMPI_Scan, int, (void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm));
RECORDER_EXTERN_DECL(PMPI_Type_commit, int, (MPI_Datatype *datatype));
RECORDER_EXTERN_DECL(PMPI_Type_contiguous, int, (int count, MPI_Datatype oldtype, MPI_Datatype *newtype));
RECORDER_EXTERN_DECL(PMPI_Type_extent, int, (MPI_Datatype datatype, MPI_Aint *extent));
RECORDER_EXTERN_DECL(PMPI_Type_free, int, (MPI_Datatype *datatype));
RECORDER_EXTERN_DECL(PMPI_Type_hindexed, int, (int count, int *array_of_blocklengths, MPI_Aint *array_of_displacements, MPI_Datatype oldtype, MPI_Datatype *newtype));
RECORDER_EXTERN_DECL(PMPI_Op_create, int, (MPI_User_function *function, int commute, MPI_Op *op));
RECORDER_EXTERN_DECL(PMPI_Op_free, int, (MPI_Op *op));
RECORDER_EXTERN_DECL(PMPI_Reduce, int, (void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm));
RECORDER_EXTERN_DECL(PMPI_Type_get_envelope, int, (MPI_Datatype datatype, int *num_integers, int *num_addresses, int *num_datatypes, int *combiner));
RECORDER_EXTERN_DECL(PMPI_Type_size, int, (MPI_Datatype datatype, int *size));

#else

#define RECORDER_MPI_CALL(func) func

#endif

#endif
