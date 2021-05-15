#ifndef DOUBLE_TABLE_H
#define DOUBLE_TABLE_H

typedef struct double_table_s {
  int n;
  int m;
  double **data;
} *double_table_t;

/* mk_double_table: load a table of doubles from the specified file */
double_table_t mk_double_table(char *filename);

/* free_double_table: free the space associated with the specified table */
void free_double_table(double_table_t t);

/* print_double_table: print the contents of the specified table to stdout */
void print_double_table(double_table_t t);




#endif
