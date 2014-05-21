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

RECORDER_EXTERN_DECL(PMPI_Ibsend, int, (void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request));
RECORDER_EXTERN_DECL(PMPI_Irsend, int, (void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request));
RECORDER_EXTERN_DECL(PMPI_Issend, int, (void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request));
RECORDER_EXTERN_DECL(PMPI_Isend, int, (void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request));
RECORDER_EXTERN_DECL(PMPI_Irecv, int, (void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request));
RECORDER_EXTERN_DECL(PMPI_Send, int, (void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm));
RECORDER_EXTERN_DECL(PMPI_Send_init, int, (void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request));
RECORDER_EXTERN_DECL(PMPI_Sendrecv, int, (void *sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Status *status));
RECORDER_EXTERN_DECL(PMPI_Sendrecv_replace, int, (void *buf, int count, MPI_Datatype datatype, int dest, int sendtag, int source, int recvtag, MPI_Comm comm, MPI_Status *status));
RECORDER_EXTERN_DECL(PMPI_Ssend, int, (void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm));
RECORDER_EXTERN_DECL(PMPI_Ssend_init, int, (void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request));
RECORDER_EXTERN_DECL(PMPI_Rsend, int, (void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm));
RECORDER_EXTERN_DECL(PMPI_Rsend_init, int, (void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request));
RECORDER_EXTERN_DECL(PMPI_Bsend, int, (void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm));
RECORDER_EXTERN_DECL(PMPI_Bsend_init, int, (void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request));
RECORDER_EXTERN_DECL(PMPI_Start, int, (MPI_Request *request));
RECORDER_EXTERN_DECL(PMPI_Recv, int, (void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status));
RECORDER_EXTERN_DECL(PMPI_Recv_init, int, (void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request));
RECORDER_EXTERN_DECL(PMPI_Allreduce, int, (void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm));
RECORDER_EXTERN_DECL(PMPI_Allgather, int, (void *sendbuf, int  sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm));
RECORDER_EXTERN_DECL(PMPI_Allgatherv, int, (void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int *recvcount, int *displs, MPI_Datatype recvtype, MPI_Comm comm));
RECORDER_EXTERN_DECL(PMPI_Alltoall, int, (void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm));
RECORDER_EXTERN_DECL(PMPI_Alltoallv, int, (void *sendbuf, int *sendcounts, int *sdispls, MPI_Datatype sendtype, void *recvbuf, int *recvcounts, int *rdispls, MPI_Datatype recvtype, MPI_Comm comm));
RECORDER_EXTERN_DECL(PMPI_Alltoallw, int, (void *sendbuf, int *sendcounts, int *sdispls, MPI_Datatype *sendtypes, void *recvbuf, int *recvcounts, int *rdispls, MPI_Datatype *recvtypes, MPI_Comm comm));
RECORDER_EXTERN_DECL(PMPI_Barrier, int, (MPI_Comm comm));
RECORDER_EXTERN_DECL(PMPI_Gather, int, (void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm));
RECORDER_EXTERN_DECL(PMPI_Gatherv, int, (void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int *recvcounts, int *displs, MPI_Datatype recvtype, int root, MPI_Comm comm));
RECORDER_EXTERN_DECL(PMPI_Scatter, int, (void *sendbuf, int sendcount, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm));
RECORDER_EXTERN_DECL(PMPI_Scatterv, int, (void *sendbuf, int *sendcounts, int *displs, MPI_Datatype sendtype, void *recvbuf, int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm));
RECORDER_EXTERN_DECL(PMPI_Wait, int, (MPI_Request *request, MPI_Status *status));
RECORDER_EXTERN_DECL(PMPI_Waitall, int, (int count, MPI_Request *array_of_requests, MPI_Status *array_of_statuses));
RECORDER_EXTERN_DECL(PMPI_Waitany, int, (int count, MPI_Request *array_of_requests, int *index, MPI_Status *status));
RECORDER_EXTERN_DECL(PMPI_Waitsome, int, (int incount, MPI_Request *array_of_requests, int *outcount, int *array_of_indices, MPI_Status *array_of_statuses));
RECORDER_EXTERN_DECL(PMPI_Bcast, int, (void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm));
RECORDER_EXTERN_DECL(PMPI_Reduce, int, (void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm));
RECORDER_EXTERN_DECL(PMPI_File_close, int, (MPI_File *fh));
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
RECORDER_EXTERN_DECL(PMPI_File_read_all_end, int, (MPI_File fh, void *buf, MPI_Status *status));
RECORDER_EXTERN_DECL(PMPI_File_read_at_all_end, int, (MPI_File fh, void *buf, MPI_Status *status));
RECORDER_EXTERN_DECL(PMPI_File_read_ordered_end, int, (MPI_File fh, void *buf, MPI_Status *status));
RECORDER_EXTERN_DECL(PMPI_File_write_all_end, int, (MPI_File fh, void *buf, MPI_Status *status));
RECORDER_EXTERN_DECL(PMPI_File_write_at_all_end, int, (MPI_File fh, void *buf, MPI_Status *status));
RECORDER_EXTERN_DECL(PMPI_File_write_ordered_end, int, (MPI_File fh, void *buf, MPI_Status *status));
RECORDER_EXTERN_DECL(PMPI_File_set_size, int, (MPI_File fh, MPI_Offset size));
RECORDER_EXTERN_DECL(PMPI_File_seek, int, (MPI_File fh, MPI_Offset offset, int whence));
RECORDER_EXTERN_DECL(PMPI_File_seek_shared, int, (MPI_File fh, MPI_Offset offset, int whence));
RECORDER_EXTERN_DECL(PMPI_File_preallocate, int, (MPI_File fh, MPI_Offset size));
RECORDER_EXTERN_DECL(PMPI_File_set_atomicity, int, (MPI_File fh, int flag));
RECORDER_EXTERN_DECL(PMPI_Type_commit, int, (MPI_Datatype *datatype));
RECORDER_EXTERN_DECL(PMPI_Type_contiguous, int, (int count, MPI_Datatype oldtype, MPI_Datatype *newtype));
RECORDER_EXTERN_DECL(PMPI_Type_create_darray, int, (int size, int rank, int ndims, int array_of_gsizes[], int array_of_distribs[], int array_of_dargs[], int array_of_psizes[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype));
RECORDER_EXTERN_DECL(PMPI_Type_create_hindexed, int, (int count, int array_of_blocklengths[], MPI_Aint array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype));
RECORDER_EXTERN_DECL(PMPI_Type_create_hvector, int, (int count, int blocklength, MPI_Aint stride, MPI_Datatype oldtype, MPI_Datatype *newtype));
RECORDER_EXTERN_DECL(PMPI_Type_create_indexed_block, int, (int count, int blocklength, int array_of_displacements[], MPI_Datatype oldtype, MPI_Datatype *newtype));
RECORDER_EXTERN_DECL(PMPI_Type_create_resized, int, (MPI_Datatype oldtype, MPI_Aint lb, MPI_Aint extent, MPI_Datatype *newtype));
RECORDER_EXTERN_DECL(PMPI_Type_create_struct, int, (int count, int array_of_blocklengths[], MPI_Aint array_of_displacements[], MPI_Datatype array_of_types[], MPI_Datatype *newtype));
RECORDER_EXTERN_DECL(PMPI_Type_create_subarray, int, (int ndims, int array_of_sizes[], int array_of_subsizes[], int array_of_starts[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype));
RECORDER_EXTERN_DECL(PMPI_Type_dup, int, (MPI_Datatype type, MPI_Datatype *newtype));
RECORDER_EXTERN_DECL(PMPI_Type_free, int, (MPI_Datatype *datatype));
RECORDER_EXTERN_DECL(PMPI_Startall, int, (int count, MPI_Request *array_of_requests));
RECORDER_EXTERN_DECL(PMPI_Comm_rank, int, (MPI_Comm comm, int *rank));
RECORDER_EXTERN_DECL(PMPI_Comm_size, int, (MPI_Comm comm, int *size));
RECORDER_EXTERN_DECL(PMPI_Finalize, int, ());
RECORDER_EXTERN_DECL(PMPI_Init, int, (int *argc, char ***argv));
RECORDER_EXTERN_DECL(PMPI_Init_thread, int, (int *argc, char ***argv, int required, int *provided));
RECORDER_EXTERN_DECL(PMPI_Wtime, int, ());
RECORDER_EXTERN_DECL(PMPI_Scan, int, (void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm));
RECORDER_EXTERN_DECL(PMPI_Op_create, int, (MPI_User_function *function, int commute, MPI_Op *op));
RECORDER_EXTERN_DECL(PMPI_Op_free, int, (MPI_Op *op));

#else

#define RECORDER_MPI_CALL(func) func

#endif

#endif
