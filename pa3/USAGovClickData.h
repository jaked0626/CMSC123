/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013 (original code)
 * Matthew Wachs, 2016 (port to C)
 *
 * USAGovClickData is a simple struct that aggregates data
 * about multiple 1.usa.gov clicks.
 *
 */

#ifndef USAGOVCLICKDATA_H_
#define USAGOVCLICKDATA_H_

#include <pthread.h>
#include "USAGovClick.h"

typedef struct USAGovClickData {
	// Total number of clicks
	int numClicks;

	// Number of clicks from new users
	int numNew;

	// enable locking
	pthread_mutex_t m;

} USAGovClickData;

// Constructor
USAGovClickData* data_init();

// Destructor
void data_free(USAGovClickData* t);

// Take a single click and update the aggregate data accordingly
void data_update(USAGovClickData* data, USAGovClick* click);

#endif /* USAGOVCLICKDATA_H_ */
