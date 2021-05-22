/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013 (original code)
 * Matthew Wachs, 2016 (port to C)
 *
 * Process a single 1.usa.gov click, collecting some basic information
 * from the click and aggregating it using the USAGovClickData struct.
 *
 * See USAGovClickTask.h for details.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "USAGovClickTask.h"
#include "USAGovClickData.h"

USAGovClickTask* task_init(USAGovClick* click, USAGovClickData* data,
                           int duration) {
    USAGovClickTask* t = (USAGovClickTask*)malloc(sizeof(USAGovClickTask));
    t->click = click;
    t->data = data;
    t->duration = duration;

    return t;
}

void task_free(USAGovClickTask* t) {
    click_free(t->click);
    free(t);
}

void task_run(USAGovClickTask* t) {
    if (t->duration > 0) {
        usleep(t->duration * 1000); /* ms to us */
    }
	data_update(t->data, t->click);
}
