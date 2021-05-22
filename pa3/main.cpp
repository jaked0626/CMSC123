/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013 (original code)
 * Matthew Wachs, 2016 (port to C)
 *
 * Process the 1.usa.gov click data (http://www.usa.gov/About/developer-resources/1usagov.shtml)
 * using a thread pool.
 *
 * This file is the entry point into the program. When run, the program
 * reads a file with click data.
 *
 * It accepts the following command-line parameters:
 *
 *  -f FILE: File with JSON representation of clicks, as returned by
 *           the live stream.
 *
 *  -t THREADS: Number of threads to use in the thread pool.
 *
 *  -d DURATION: Artificially make the tasks in the thread pool run
 *               for this long (in milliseconds)
 *
 *  -i INTERVAL: Artificially introduce an interval (in milliseconds)
 *               between reading each new click.
 *
 *  -v: Verbose mode. Prints out more messages to the console.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>
#include "USAGovClickFileReader.h"
#include "USAGovClickData.h"
#include "USAGovClick.h"
#include "USAGovClickTask.h"
#include "ThreadPool.h"

#ifdef __MACH__
#ifndef CLOCK_MONOTONIC
//  emulate Linux-only API on old versions of macOS
//  (new versions have this built in)
//  based on http://stackoverflow.com/questions/5167269/clock-gettime-alternative-in-mac-os-x
#include <mach/mach_time.h>
#define ORWL_NANO (+1.0E-9)
#define ORWL_GIGA UINT64_C(1000000000)

static double orwl_timebase = 0.0;
static uint64_t orwl_timestart = 0;

#define CLOCK_MONOTONIC 0

void clock_gettime(int _, struct timespec *t) {
    // be more careful in a multithreaded environement
    if (!orwl_timestart) {
        mach_timebase_info_data_t tb = { 0 };
        mach_timebase_info(&tb);
        orwl_timebase = tb.numer;
        orwl_timebase /= tb.denom;
        orwl_timestart = mach_absolute_time();
    }
    double diff = (mach_absolute_time() - orwl_timestart) * orwl_timebase;
    t->tv_sec = diff * ORWL_NANO;
    t->tv_nsec = diff - (t->tv_sec * ORWL_GIGA);
}
#endif
#endif

const char* USAGE = "-f FILE [-t THREADS] [-d DURATION] [-i INTERVAL] [-v]";

int main(int argc, char* argv[])
{
	// For parsing command-line options
	int opt;
	// Should we be verbose?
	bool verbose = false;
	// File with click data
    char* file = NULL;
	FILE* f;
	// Number of threads
	int nthreads = 1;
	// Duration of each task (milliseconds)
	int duration = 0;
	// Interval between tasks (milliseconds)
	int interval = 0;
	// Number of tasks dropped by the thread pool
	int dropped = 0;
	// Click reader
    USAGovClickFileReader* reader;
	// Data struct
	USAGovClickData* data = data_init();

	// Parse command-line options
    while ((opt = getopt(argc, argv, "f:t:d:i:vh")) != -1) {
		switch (opt)
		{
			case 'f':
				file = optarg;
				break;
			case 't':
				nthreads = atoi(optarg);
				break;
			case 'd':
				duration = atoi(optarg);
				break;
			case 'i':
				interval = atoi(optarg);
				break;
			case 'v':
				verbose = true;
				break;
			default:
                fprintf(stderr, "Usage: %s %s\n", argv[0], USAGE);
                fprintf(stderr, "ERROR: Unknown option -%c\n", opt);
				exit(1);
		}
    }
    
	if (file == NULL)
	{
        fprintf(stderr, "Usage: %s %s\n", argv[0], USAGE);
        fprintf(stderr, "ERROR: Must specify the -f option\n");
		exit(1);
	}

	// Create the reader
    f = fopen(file, "r");
    if (f == NULL) {
        fprintf(stderr, "cannot open file %s\n", file);
        exit(1);
    }
    reader = filereader_init(f);

	struct timespec start, finish;
	double elapsed;
	clock_gettime(CLOCK_MONOTONIC, &start);

	// Create thread pool
	ThreadPool* pool = pool_init(nthreads);

	int n = 0;
    while (!filereader_done(reader)) {
		USAGovClick* click = filereader_next(reader);
		USAGovClickTask* task = task_init(click, data, duration);

        if (pool_schedule(pool, task)) {
			if (verbose)
                printf("Task %d scheduled.\n", n + 1);
		}
		else
		{
			dropped++;
			if(verbose)
                printf("Task %d NOT scheduled.\n", n + 1);
            task_free(task);
		}

		n++;

        if (interval > 0) {
            usleep(interval * 1000); /* ms to us */
        }
	}
	pool_stop(pool);

	clock_gettime(CLOCK_MONOTONIC, &finish);

	elapsed = (finish.tv_sec - start.tv_sec);
	elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

	if (verbose)
	{
        printf("\n\nRunning time: %f\n", elapsed);
        printf("Received %d clicks.\n", n);
        printf("Dropped %d clicks.\n", dropped);
        printf("Processed %d clicks.\n", data->numClicks);

        printf("%d of the clicks were from new users\n", data->numNew);
	}
	else
	{
        printf("%s,%d,%f,%d,%d\n", file, nthreads, elapsed, n, dropped);
	}
    
    fclose(f);
    pool_free(pool);
    filereader_free(reader);
    data_free(data);

    return 0;
}
