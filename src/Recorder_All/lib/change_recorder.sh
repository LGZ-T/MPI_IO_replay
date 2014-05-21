#! /bin/bash

./func-to-decl.py
./Type_and_Extern_Generator.py
cp init-compress.c recorder-mpi-init-finalize-compress.c
cp new_recorder-dynamic.h ../recorder-dynamic.h
cd generator
./MPI_wrapper_generator_compress.py
cp sample_output.c ../recorder-mpi-io-compress.c
cd ../..
make clean
export LANG=C
make
