MPI_IO_replay
=============

Replay MPI I/O operation according to the input trace file.

Build
------

   $ mkdir build; cd build;
   $ cmake ..
   $ make

.. note::
   Important File

   The ``Recorder_All/func_list`` defines the wrapper function to process

Run
----

   $ LD_PRELOAD="librecorder-compress.so" mpirun -np <#> <prog>
