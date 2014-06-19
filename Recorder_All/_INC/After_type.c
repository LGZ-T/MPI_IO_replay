

#endif

int MPI_Init(int *argc, char ***argv)
{
    int ret;

#ifdef RECORDER_PRELOAD
    resolve_mpi_symbols();
#endif

    ret = RECORDER_MPI_CALL(PMPI_Init)(argc, argv);
    if(ret != MPI_SUCCESS)
    {
        return(ret);
    }

    recorder_mpi_initialize(argc, argv);

    return(ret);
}

int MPI_Init_thread (int *argc, char ***argv, int required, int *provided)
{
    int ret;

    ret = RECORDER_MPI_CALL(PMPI_Init_thread)(argc, argv, required, provided);
    if (ret != MPI_SUCCESS)
    {
        return(ret);
    }

    recorder_mpi_initialize(argc, argv);

    return(ret);
}

int MPI_Finalize(void)
{
    int ret;

        recorder_shutdown(0);
    ret = RECORDER_MPI_CALL(PMPI_Finalize)();

    return(ret);
}

