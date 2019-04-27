/** \file
 * \brief Image Processing
 *
 * See Copyright Notice in im_lib.h
 */

#ifndef __IM_PROCESS_H
#define __IM_PROCESS_H

#include "im_process_pnt.h"
#include "im_process_loc.h"
#include "im_process_glo.h"
#include "im_process_ana.h"

#if	defined(__cplusplus)
extern "C" {
#endif


/** \defgroup process Image Processing
 * \par
 * Several image processing functions based on the \ref imImage structure.
 * \par
 * You must link the application with "im_process.lib/.a/.so". 
 * In Lua call require"imlua_process". \n
 * Some complex operations use the \ref counter.\n
 * There is no check on the input/output image properties, 
 * check each function documentation before using it.
 * \par
 * To enable OpenMP support use the "im_process_omp.lib/.a/.so" libraries.
 * In Lua call require"imlua_process_omp". \n
 * Notice that multi-threading can be slower than single thread because of 
 * the overhead introduced by the threads configuration. \n
 * When using the "im_process_omp" library you can reduce that overhead 
 * by using the \ref imProcessOpenMPSetMinCount and \ref imProcessOpenMPSetNumThreads functions. 
 * But notice that this is not the same thing as using the library without support for OpenMP. \n
 * \par
 * The parallelization in im_process involves only loops, usually for all the pixels in the image.
 * To accomplish that we had to first isolate the \ref counter code, so the counting could also be done
 * in parallel. Then we made sure that all loops contain only local variables 
 * to avoid unnecessary shared variables that could lead to incorrect results. 
 * In a few places we use the "atomic" directive to be able to compute histograms and other counts. 
 * But min/max computation must be done in single thread
 * because of limitations in OpenMP support in C (in Fortran it would be easy to implement).
 * \par
 * For more information on OpenMP: \n
 * http://www.openmp.org 
 */


#if defined(__cplusplus)
}
#endif

#endif
