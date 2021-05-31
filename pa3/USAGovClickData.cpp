/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013 (original code)
 * Matthew Wachs, 2016 (port to C)
 *
 * USAGovClickData is a simple struct that aggregates data
 * about multiple 1.usa.gov clicks.
 *
 * See USAGovClickData.h for details
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "USAGovClickData.h"

USAGovClickData* data_init() {
    USAGovClickData* t = (USAGovClickData*)malloc(sizeof(USAGovClickData));
    
    t->numClicks = 0;
    t->numNew = 0;
    
    /*** GRADER COMMENT: You should initialize the mutex here with pthread_mutex_init()
     *   PENALTY: -4 pts */ 
    return t;
}

void data_free(USAGovClickData* t) {
    free(t);
}

void data_update(USAGovClickData*t, USAGovClick* click) {
    pthread_mutex_lock(&t->m);
    t->numClicks++;
    if (!click->known) {
		t->numNew++;
    }
    pthread_mutex_unlock(&t->m); // added lock to update function 
}
