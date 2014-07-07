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

#include "Type_and_Extern.h"
