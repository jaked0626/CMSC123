#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>

/* utility routine that checks the return value from
 * malloc and generates an error if malloc returns NULL 
 */
void *ck_malloc(int size);

/* utility routine that checks the return value from
 * realloc and generates an error if realloc returns NULL 
 */
void *ck_realloc(void *data, int size);

/* getText: return a string containing the contents of the 
 * specified file.   Fails and exits, if it runs out of space
 * to hold the file.
 */
char *get_text(FILE *f);

/* free_2d: free the space associated with an an array of N arrays. */
void free_2d(void **data, int n);

#endif
