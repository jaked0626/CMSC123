/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013 (original code)
 * Matthew Wachs, 2016 (port to C)
 *
 * Process a single 1.usa.gov click, collecting some basic information
 * from the click and aggregating it using the USAGovClickData struct.
 *
 */

#ifndef USAGOVCLICKTASK_H_
#define USAGOVCLICKTASK_H_

#include "USAGovClick.h"
#include "USAGovClickData.h"

typedef struct USAGovClickTask {
	// The click to be processed in this task
	USAGovClick* click;

	// A reference to the aggregate data (which will be
	// modified using the contents of the click)
	USAGovClickData* data;

	// Artificial duration of the task
	// (the task will sleep for this many milliseconds before
	// it completes its work)
	int duration;
} USAGovClickTask;

// Constructor
USAGovClickTask* task_init(USAGovClick* click, USAGovClickData* data, int duration);

// Destructor
void task_free(USAGovClickTask* t);

// Processes the data in the click.
void task_run(USAGovClickTask* t);

#endif /* USAGOVCLICKTASK_H_ */
