#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct matrix_s {
    unsigned int n, m;  /* n = # of rows, m = # of cols */
    int** elements;
};

typedef struct matrix_s* matrix_t;

void print_matrix(matrix_t mtx) {
    unsigned int i, j;
    for (i = 0; i < mtx->n; i++) {
        for (j = 0; j < mtx->m; j++) {
            printf("%d\t", mtx->elements[i][j]);
        }
        printf("\n");
    }
}

char* bool_str(bool b) {
    return b ? "true" : "false";
}


bool row_matches_col(matrix_t mtx) {
    // YOUR CODE HERE
}

bool col_palindrome(matrix_t mtx, unsigned int c) {
    // YOUR CODE HERE
}

void alternator(matrix_t mtx) {
    // YOUR CODE HERE
}

bool horiz_run(matrix_t mtx, unsigned int run) {
    // YOUR CODE HERE
}


int main(int argc, char** argv) {
    int row0[] = {11, 12, 13, 14, 15};
    int row1[] = {21, 22, 23, 24, 25};
    int row2[] = {31, 24, 24, 24, 35};
    int row3[] = {13, 23, 24, 24, 53};
    int row4[] = {51, 51, 53, 14, 55};
    int* elems[] = {row0, row1, row2, row3, row4};
    struct matrix_s mtxs = {5, 5, elems};
    matrix_t mtx = &mtxs;

    printf("row_matches_col: %s\n", bool_str(row_matches_col(mtx)));
    
    printf("col_palindrome (A): %s\n", bool_str(col_palindrome(mtx, 3)));
    printf("col_palindrome (B): %s\n", bool_str(col_palindrome(mtx, 4)));
    
    printf("horiz_run (3): %s\n", bool_str(horiz_run(mtx, 3)));
    printf("horiz_run (4): %s\n", bool_str(horiz_run(mtx, 4)));
    
    printf("alternator:\n");
    alternator(mtx);
    print_matrix(mtx);
    printf("\n");

    return 0;
}
