/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013 (original code)
 * Matthew Wachs, 2016 (port to C)
 *
 * An implementation of the thread pool pattern.
 * This file contains the implementation of the worker threads
 *
 */

#ifndef WORKERTHREAD_H_
#define WORKERTHREAD_H_

#include <pthread.h>
#include "USAGovClickTask.h"

/* declared in another file */
struct ThreadPool;

typedef struct WorkerThread {
	// The worker thread includes a reference to the
	// thread pool to be able to access its queue
	// and check whether there are any tasks to work on.
	struct ThreadPool* pool;

	// The actual thread
	pthread_t thd;
} WorkerThread;

// Constructor
WorkerThread* worker_init(struct ThreadPool* pool);

// Destructor
void worker_free(WorkerThread* t);

// Start the thread
void worker_start(WorkerThread* t);

// The function that will be run by the thread.
void* worker_run(void* tv);

#endif /* WORKERTHREAD_H_ */
