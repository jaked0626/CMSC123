/*
 * CMSC 12300 - Computer Science with Applications 3
 * Borja Sotomayor, 2013 (original code)
 * Matthew Wachs, 2016 (port to C)
 *
 * Read click data stored in a text file.
 *
 */

#ifndef USAGOVCLICKFILEREADER_H_
#define USAGOVCLICKFILEREADER_H_

#include <stdio.h>
#include <stdbool.h>
#include "USAGovClick.h"

typedef struct USAGovClickFileReader {
	// Input file. Reading one line
	// from this file yields one click
	// (in JSON)
	FILE* f;
} USAGovClickFileReader;

// Constructor
// Parameter: The input stream with the click data.
USAGovClickFileReader* filereader_init(FILE* f);

// Destructor
void filereader_free(USAGovClickFileReader* fr);

// This function must return true once the reader has no
// more clicks to provide
bool filereader_done(USAGovClickFileReader* r);

// Returns the next click in the source.
USAGovClick* filereader_next(USAGovClickFileReader* r);

#endif /* USAGOVCLICKFILEREADER_H_ */
