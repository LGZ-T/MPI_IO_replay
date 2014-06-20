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

   $ src/compress <single log file> <output log file>
   
merge traces:

.. code:: bash

   $ src/lcs_trace <log_num> <compressed_log_dir> 

compressed_log_dir's filename should keep as compressed_log.*, you need create
a ``lcs`` folder at current work dir, then it would write output into this folder.
   
replay to a c code:

.. code:: bash

   $ src/replay <proc_num> <scale_rate> <single aux file> 

you need create a ``construct`` folder at first.

recompile the temp.c:

.. code:: bash

   $ mpicc -std=c99 -O0 temp.c 
