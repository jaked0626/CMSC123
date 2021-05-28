/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013 (original code)
 * Matthew Wachs, 2016 (port to C)
 *
 * An implementation of the thread pool pattern.
 *
 * See ThreadPool.h for details.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "ThreadPool.h"
#include "WorkerThread.h"

// Use the next three functions to manipulate the queue of tasks maintained in the pool
// These use a linked list to represent a queue.

unsigned int queue_length(TaskQueue* q) {
    return q->length;
}

USAGovClickTask* queue_dequeue(TaskQueue* q) {
    if (q->head == NULL) {
        fprintf(stderr, "pop from empty queue\n");
        exit(1);
    }
    
    QueueEntry* qe = q->head;
    USAGovClickTask* rv = qe->task;
    
    q->head = qe->next;
    if (q->tail == qe) {
        q->tail = NULL;
    }
    q->length--;
    free(qe);
    
    return rv;
}

void queue_enqueue(TaskQueue* q, USAGovClickTask* task) {
    if (q->length >= MAX_TASKS) {
        fprintf(stderr, "attempt to push to full queue\n");
        exit(1);
    }
    
    QueueEntry* qe = (QueueEntry*)malloc(sizeof(QueueEntry));
    qe->task = task;
    qe->next = NULL;
    
    if (q->tail == NULL) {
        q->head = q->tail = qe;
    } else {
        q->tail->next = qe;
        q->tail = qe;
    }
    q->length++;
}

ThreadPool* pool_init(int numWorkers) {
    int i;
    ThreadPool* t = (ThreadPool*)malloc(sizeof(ThreadPool));
    t->numWorkers = numWorkers;
    t->workers = (WorkerThread**)malloc(sizeof(WorkerThread*)*numWorkers);
    pthread_mutex_init(&t->m, NULL);
    pthread_cond_init(&t->cvQueueNonEmpty, NULL);
    t->stop = false;  // added boolean indicator for pool_stop
    
    t->q = (TaskQueue*)malloc(sizeof(TaskQueue));
    t->q->length = 0;
    t->q->head = t->q->tail = NULL;

    
    for (i = 0; i < numWorkers; i++) {
        t->workers[i] = worker_init(t);
        worker_start(t->workers[i]);
    }
    
    return t;
}

void pool_free(ThreadPool* t) {
    unsigned int i;
    for (i = 0; i < t->numWorkers; i++) {
        worker_free(t->workers[i]);
    }
    
    while (queue_length(t->q)) {
        USAGovClickTask* task = queue_dequeue(t->q);
        task_free(task);
    }
    free(t->q);
    
    free(t);
}

bool pool_schedule(ThreadPool* t, USAGovClickTask *task) {
	/* YOUR CODE GOES HERE */
    if (queue_length(t->q) >= MAX_TASKS) {
        return false; // drop task
    } else {
        pthread_mutex_lock(&t->m); // lock pool thread (queue) 
        queue_enqueue(t->q, task); // push to queue
        // conditional for if queue is empty?
        pthread_mutex_unlock(&t->m);
        pthread_cond_signal(&t->cvQueueNonEmpty);
        return true;
    }
}


void pool_stop(ThreadPool* t) {
	/* YOUR CODE GOES HERE */
    void* res;
    int i;
    t->stop = true;
    for (i = 0; i < t->numWorkers; i++) {
        pthread_cond_signal(&t->cvQueueNonEmpty);
    } // ensure each worker exits function (wakes up, stop = true, returns null) 
    for (i = 0; i < t->numWorkers; i++) {
        pthread_join(t->workers[i]->thd, &res);
    } // join to ensure all workers have exited before ending
}
