MPI_IO_replay
=============

Replay MPI I/O operation according to the input trace file.

Build
------

.. code:: bash

   $ mkdir build; cd build;
   $ cmake ..
   $ make

.. note::
   Important File

   The ``Recorder_All/func_list`` defines the wrapper function to process

Run
----

output trace:

.. code:: bash

   $ LD_PRELOAD="Recorder_All/librecorder-compress.so" mpirun -np [num] [prog]
   
compress trace:

.. code:: bash

   $ src/compress [log dir]
   
   
   

