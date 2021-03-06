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
    ThreadPool* pool = t->pool;
    while(!pool->stop){
        pthread_mutex_lock(&pool->m);
        while (queue_length(pool->q) <= 0 && !pool->stop) { // queue is empty
            pthread_cond_wait(&pool->cvQueueNonEmpty,
                            &pool->m); 
            if(pool->stop) {
                pthread_mutex_unlock(&pool->m);
                return NULL; // exits function when pool_stop is called
            }
        }
        USAGovClickTask* task = queue_dequeue(pool->q); // pool is locked
        pthread_mutex_unlock(&pool->m);
        task_run(task);
    }
    return NULL;
}
