#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "double_table.h"
#include "util.h"

/* mk_double_table: load a table of doubles from the specified file */
double_table_t mk_double_table(char *filename) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "mk_double_table: Unable to open file %s\n", filename);
    exit(1);
  }

  int n = -1;
  if (fscanf(f, "%d", &n) != 1) {
    fprintf(stderr, "Bad format in %s: expected int at line %d", filename, 1);
    exit(0);
  }

  int m = -1;
  if (fscanf(f, "%d", &m) != 1) {
    fprintf(stderr, "Bad format in %s: expected int at line %d", filename, 2);
    exit(0);
  }

  double **data = (double **) ck_malloc(n*sizeof(data[0]));
  for (int i = 0; i < n; i++) {
    data[i] = ck_malloc(m*sizeof(data[0][0]));
    for (int j = 0; j < m; j++) {
      double d;
      if (fscanf(f, "%lf", &d) != 1) {
        fprintf(stderr, "Bad format in %s: expected double at line %d", filename, i);  
        exit(0);
      }
      data[i][j] = d;
    }
  }

  
  fclose(f);

  double_table_t table = (double_table_t) ck_malloc(sizeof(*table));
  table->n = n;
  table->m = m;
  table->data = data;

  return table;
}

/* free_double_table: free the space associated with the specified table */
void free_double_table(double_table_t t) {
  assert(t != NULL);
  assert(t->data != NULL);
  for (int i = 0; i < t->n; i++) {
    assert(t->data[i] != NULL);
    free(t->data[i]);
  }
  free(t->data);
  free(t);
}

/* print_double_table: print the contents of the specified table to the screen */
void print_double_table(double_table_t t) {
  assert(t != NULL);
  assert(t->data);
  for (int i = 0; i < t->n; i++) {
    for (int j = 0; j < t->m; j++) {
      printf("%f ", t->data[i][j]);
    }
    printf("\n");
  }
}
