/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013 (original code)
 * Matthew Wachs, 2016 (port to C)
 *
 * An implementation of the thread pool pattern.
 * This file contains the implementation of the worker threads
 *
 * See WorkerThread.h for details.
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "ThreadPool.h"
#include "WorkerThread.h"

WorkerThread* worker_init(ThreadPool* pool) {
    WorkerThread* t = (WorkerThread*)malloc(sizeof(WorkerThread));
    
    t->pool = pool;

    return t;
}

void worker_free(WorkerThread* t) {
    free(t);
}

void worker_start(WorkerThread* t) {
	// Create the thread and make it run the run() function
    pthread_create(&t->thd, NULL, worker_run, (void*)t);
}

void* worker_run(void* tv) {
    WorkerThread* t = (WorkerThread*)tv;
    
    /* YOUR CODE GOES HERE */
    
    return NULL;
}
