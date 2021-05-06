#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>

/* utility routine that checks the return value from
 * malloc and generates an error if malloc returns NULL 
 */
void *ck_malloc(int size) {
  void *rv = malloc(size);
  if (rv == NULL) {
    fprintf(stderr, "malloc failed\n");
    exit(2);
  }
  return rv;
}

void *ck_realloc(void *data, int size) {
  void *rv = realloc(data, size);
  if (rv == NULL) {
    fprintf(stderr, "realloc failed\n");
    exit(2);
  }
  return rv;
}

/* free_2d: free the space associated with a an array of N arrays. */
void free_2d(void **data, int n) {
  for (int i = 0; i < n; i++)
    free(data[i]);
  free(data);
}

/* getText: return a string containing the contents of the 
 * specified file.   Fails and exits, if it runs out of space
 * to hold the file.
 */

char *get_text(FILE *f) {
  int c;
  int max = 100;    // current number of bytes in s
  char *s = (char *)ck_malloc(max);
  int len = 0;     // current length of the string represented by s

  while ((c = getc(f)) != EOF) {
    // compress runs of white space into one space
    if (isspace(c)) {
      if ((len > 0) && (s[len-1] != ' ')) {
	s[len] =' ';
	len++;
      }
    } else {
      s[len] = c;
      len++;
    }

    if (len >= max) {
      // allocate more space if necessary.
      max = max * 1.5;
      char *tmp = ck_realloc(s, max);
      s = tmp;

    }
  }

  // get rid of trailing space at the end of the string.
  if (s[len-1] == ' ') {
    s[len-1] = '\0';
  } else 
    s[len] = '\0';

  return s;
}
