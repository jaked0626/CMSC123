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


bool compare_row_col(matrix_t mtx, int r, int c) {
    // compare row r and col c
    bool res = true;
    unsigned int k;
    unsigned int dim = mtx->n; // num of rows and cols, must be equal
    for (k = 0; k < dim; k++) {
        if (mtx->elements[r][k] != mtx->elements[k][c]){
            res = false;
            return res;
        }
    }
    return res;
}

bool row_matches_col(matrix_t mtx) {
    bool res = false;
    if (mtx->n != mtx->m) {
        return res;
    } else { 
        int i, j;
        for (i = 0; i < mtx->n; i++) {
            for (j = 0; j < mtx->m; j++) {
                if (compare_row_col(mtx, i, j)){
                    res = true;
                    return res;
                }
            }
        }
        return res;
    }
}

bool col_palindrome(matrix_t mtx, unsigned int c) {
    bool res = true;
    int tail = mtx->n - 1; // last index of col
    int i;
    for (i = 0; i < tail / 2; i++) {
        if (mtx->elements[i][c] != mtx->elements[tail - i][c]) {
            res = false;
            return res;
        }
    }
    return res;
}

void alternator(matrix_t mtx) {
    int i, j;
    for (i = 0; i < mtx->n; i++) {
        for (j = 0; j < mtx->m; j++) {
            if (i % 2 == j % 2) {
                mtx->elements[i][j] = 0;
            } else {
                mtx->elements[i][j] = 1;
            }
        }
    }
}

bool one_row_run (matrix_t mtx, unsigned int r, unsigned int run) {
    int i = 0;
    int num_col = mtx->m;
    bool res = false;
    while (i < num_col) {
        int current_run = 0;
        double run_val = mtx->elements[r][i];
        while (i < num_col && mtx->elements[r][i] == run_val) {
            current_run++;
            if (current_run >= run) {
                res = true;
                return res;
            }
            i++;
        }
    }
    return res;
}

bool horiz_run(matrix_t mtx, unsigned int run) {
    int i;
    bool res = false;
    for (i=0; i < mtx->n; i++) {
        if (one_row_run(mtx, i, run)){
            res = true;
            return res;
        }
    }
    return res;
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

    int row20[] = {1, 1, 1, 1};
    int row21[] = {1, 22, 23, 24};
    int row22[] = {1, 24, 24, 24};
    int row23[] = {1, 23, 24, 24};
    int row24[] = {1, 51, 53, 14};
    int* elems2[] = {row20, row21, row22, row23, row24};
    struct matrix_s mtxs2 = {5, 4, elems2};
    matrix_t mtx2 = &mtxs2;

    printf("row_matches_col: %s\n", bool_str(row_matches_col(mtx)));
    
    printf("col_palindrome (A): %s\n", bool_str(col_palindrome(mtx, 3)));
    printf("col_palindrome (B): %s\n", bool_str(col_palindrome(mtx, 4)));
    
    printf("horiz_run (3): %s\n", bool_str(horiz_run(mtx, 3)));
    printf("horiz_run (4): %s\n", bool_str(horiz_run(mtx, 4)));
    
    printf("alternator:\n");
    alternator(mtx);
    print_matrix(mtx);
    printf("\n");

    printf("row_matches_col: %s\n", bool_str(row_matches_col(mtx2)));
    
    printf("col_palindrome (A): %s\n", bool_str(col_palindrome(mtx2, 0)));
    printf("col_palindrome (B): %s\n", bool_str(col_palindrome(mtx2, 1)));
    
    printf("horiz_run (3): %s\n", bool_str(horiz_run(mtx2, 3)));
    printf("horiz_run (4): %s\n", bool_str(horiz_run(mtx2, 4)));
    
    printf("alternator:\n");
    alternator(mtx2);
    print_matrix(mtx2);
    printf("\n");

    return 0;
}
