/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013 (original code)
 * Matthew Wachs, 2016 (port to C)
 *
 * Read click data stored in a text file.
 *
 * See USAGovClickFileReader.h for details
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "USAGovClickFileReader.h"

USAGovClickFileReader* filereader_init(FILE* f) {
    USAGovClickFileReader* t = (USAGovClickFileReader*)malloc(sizeof(USAGovClickFileReader));
    t->f = f;
    return t;
}

void filereader_free(USAGovClickFileReader* t) {
    free(t);
}

bool filereader_done(USAGovClickFileReader* t) {
	// If the EOF is reached, we have no more clicks.
    return feof(t->f);
}

USAGovClick* filereader_next(USAGovClickFileReader* t) {
	// Read in one line, and parse it (using the USAGovClick class)
	char line[10000];
    fgets(line, 10000, t->f);
	USAGovClick* click;

    click = click_init(line);

	return click;
}
