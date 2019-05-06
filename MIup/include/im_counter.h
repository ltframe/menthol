/** \file
 * \brief Processing Counter
 *
 * See Copyright Notice in im_lib.h
 */

#ifndef __IM_COUNTER_H
#define __IM_COUNTER_H

#if	defined(__cplusplus)
extern "C" {
#endif


/** \defgroup counter Counter 
 * \par
 * Used to notify the application that a step in the loading, saving or processing operation has been performed.
 * \par
 * See \ref im_counter.h
 * \ingroup util */

/** Counter callback, informs the progress of the operation to the client. \n
 * Counter id identifies different counters. \n
 * Progress in a count reports a value from 0 to 1000 always, proportional to total value and increment. 
 * If -1 indicates that Begin was called, 1001 indicates that End was called. \n
 * If returns 0 the client should abort the operation. \n
 * Noticed that if the counter is aborted, the callback will still be called one last time at 1001.
 * Text is NULL most of the time, but contains a title in Begin (progress==-1)
 * and a message in the start of a count (progress==0).
 * \ingroup counter */
typedef int (*imCounterCallback)(int counter, void* cb_user_data, const char* text, int progress);

/** Changes the counter callback. Returns old callback. \n
 * User data is changed only if not NULL.
 * \ingroup counter */
imCounterCallback imCounterSetCallback(void* cb_user_data, imCounterCallback counter_func);

/** Returns true if the counter callback is set.
 * When the callback is NULL the counter is inactive and all functions do nothing.
 * \ingroup counter */
int imCounterHasCallback(void);

/** Begins a new count. \n
 * Calls the callback with "-1" and text=title. \n     
 * This is to be used by the operations. Returns a new counter Id. \n
 * Several counters can coexist at the same time, as part of a sequence with sub-counter 
 * or simultaneous counter in multi-thread applications.
 * \ingroup counter */
int imCounterBegin(const char* title);

/** Ends a count. \n
 * Calls the callback with "1001", text=null, and releases the counter. \n
 * \ingroup counter */
void imCounterEnd(int counter);

/** Increments a count. Must set the total first. \n
 * Calls the callback, text=message if it is the first increment for the count. \n
 * Returns 0 if the callback aborted, 1 if returns normally.
 * \ingroup counter */
int imCounterInc(int counter);

/** Set a specific count. Must set the total first. \n
 * Calls the callback, text=message if it is the first increment for the count. \n
 * Returns 0 if the callback aborted, 1 if returns normally.
 * \ingroup counter */
int imCounterIncTo(int counter, int count);

/** Sets the total increments of a count. \n
 * Must be set at least one time. \n
 * Notice that if total is set more than one time counter should simply restart.
 * \ingroup counter */
void imCounterTotal(int counter, int total, const char* message);

/** Sets an additional user data in the counter.
 * Used to save the lock in multi-threaded configurations.
 * \ingroup counter */
void* imCounterGetUserData(int counter);

/** Returns the additional user data in the counter.
 * \ingroup counter */
void imCounterSetUserData(int counter, void* userdata);


#if defined(__cplusplus)
}
#endif

#endif
