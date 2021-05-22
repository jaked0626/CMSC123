/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013 (original code)
 * Matthew Wachs, 2016 (port to C)
 *
 * An implementation of the thread pool pattern.
 *
 * A thread pool is created with a fixed number of threads
 * and a queue with a size limit. Initially, the queue
 * will be empty and the threads will be idle (waiting
 * for tasks to arrive). While waiting, they should not
 * busy-wait; they should sleep until the queue becomes
 * non-empty.
 *
 * As tasks arrive, they are placed on the queue, and
 * claimed by the next idle thread.
 *
 * If all the threads are busy, this just means the task
 * will have to wait in the queue until it is run. However.
 * if the queue reaches its limit, any new tasks will be
 * rejected.
 *
 */

#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include <stdbool.h>
#include <pthread.h>
#include "USAGovClickTask.h"

// Length of queue of tasks
// If backlog grows to more than this, start dropping tasks
// instead of queueing them
#define MAX_TASKS 10

/* declared in another file, but used here */
struct WorkerThread;

// Maintain a queue of tasks
typedef struct QueueEntry QueueEntry;

struct QueueEntry {
    USAGovClickTask* task;
    QueueEntry* next;
};

typedef struct TaskQueue {
    unsigned int length;
    QueueEntry *head, *tail;
} TaskQueue;

// The thread pool
typedef struct ThreadPool {
	// The number of worker threads
	unsigned int numWorkers;

	// The worker threads
    struct WorkerThread** workers;

	// The task queue
    // Use queue_enqueue, queue_dequeue, and queue_length to manipulate
    TaskQueue* q;

	// A mutex to control access to the queue
	pthread_mutex_t m;

	// Condition variable to notify idling threads when the
	// queue goes from empty to non-empty
	pthread_cond_t cvQueueNonEmpty;
} ThreadPool;

// Constructor
ThreadPool* pool_init(int numThreads);

// Destructor
void pool_free(ThreadPool* t);

// Schedules a single task. Returns true if the task was scheduled,
// and false otherwise.
bool pool_schedule(ThreadPool* t, USAGovClickTask *task);

// Get the number of items in the queue contained in this pool
unsigned int queue_length(TaskQueue* q);

// Remove the frontmost item from the queue
// and return it
USAGovClickTask* queue_dequeue(TaskQueue* q);

// add this item to the end of the queue
void queue_enqueue(TaskQueue* q, USAGovClickTask* task);

// Stop the thread pool. This joins all the threads.
void pool_stop(ThreadPool* t);

#endif /* THREADPOOL_H_ */
