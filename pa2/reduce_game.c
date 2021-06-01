/* CS 123, Spring 2021
 * Basic game theory: Reducing Games
 *
 * Reduce games using iterative elimination.
 *
 * Jake Underland
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "reduce_game.h"

/* compare_rows: compares two rows and returns the index of 
 *   the strictly dominated row if there is one, -1 if there isn't.
 *   double **player1: a 2d-array
 *   int i: index of a row
 *   int j: index of a row
 *   int ncol: number of columns
 */
int compare_rows(double **player1, int row_i, int row_j, int ncol) {
  int res;
  int u;
  int l;
  if (player1[row_i][0] > player1[row_j][0]) {
    res = row_j;
    u = row_i; // check if row i is strictly greater than row j
    l = row_j;
  } else if (player1[row_i][0] < player1[row_j][0]) {
    res = row_i;
    u = row_j; // check if row j is strictly greater than row i
    l = row_i;
  } else {
    res = -1; // no rows to be deleted
    return res;
  }
  for (int x = 1; x < ncol; x++) {
    if (player1[u][x] <= player1[l][x]){
      res = -1;
      break;
    }
  }
  return res;
}


/* iterate_rows: iterates through rows and eliminates strictly 
 *  dominated rows
 *  game_t g: game 
 */
void iterate_rows(game_t g) {
  int i = 0;
  while(i < (g->n - 1)) {
    int j = i + 1;
    while(j < g->n) {
      int x = compare_rows(g->player1, i, j, g->m);
      if (x == i) {
        remove_row_game(g, x);
        i--; // decrement i since rows move up
        break; // break loop of j, move to next i
        //GRADER: Well done trying the slightly harder approach of
        //removing all columns and rows in a single pass. 
      }
      else if (x == j) {
        remove_row_game(g, x);
        continue;
        // move to next row without updating value of j
        // because removal shifts j forward
      }
      j++;
    }
    i++;
  }
}


/* compare_cols: compares two cols and returns the index of 
 *   the strictly dominated col if there is one, -1 if there isn't.
 *   double **player2: a 2d-array
 *   int i: index of a col
 *   int j: index of a col
 *   int nrow: number of rows
 */
int compare_cols(double **player2, int col_i, int col_j, int nrow) {
  int res;
  int u;
  int l;
  if (player2[0][col_i] > player2[0][col_j]) {
    res = col_j;
    u = col_i; // check if col i is strictly greater than col j
    l = col_j;
  } else if (player2[0][col_i] < player2[0][col_j]) {
    res = col_i;
    u = col_j; // check if col j is strictly greater than col i
    l = col_i;
  } else {
    res = -1; // no cols to be deleted
    return res;
  }
  for (int x = 1; x < nrow; x++) {
    if (player2[x][u] <= player2[x][l]){
      res = -1;
      break;
    }
  }
  return res;
}


/* iterate_cols: iterates through cols and eliminates strictly 
 *  dominated cols
 *  game_t g: game 
 */
void iterate_cols(game_t g) {
  int i = 0;
  while(i < (g->m - 1)) {
    int j = i + 1;
    while(j < g->m) {
      int x = compare_cols(g->player2, i, j, g->n);
      if (x == i) {
        remove_col_game(g, x);
        i--; // decrement i since cols move up
        break; // break loop of j, move i to next col
      }
      else if (x == j) {
        remove_col_game(g, x);
        continue;
        // move to next col without updating value of j
        // because removal shifts j forward
      }
      j++;
    }
    i++;
  }
}

/*
 * one_sweep: makes one sweep of rows and columns and eliminates
 *  dominated ones. 
 *  game_t g: game
 */
void one_sweep (game_t g) {
  iterate_rows(g);
  iterate_cols(g);
  //print_game(g);
}

/* reduce: iteratively reduce rows and columns until no changes occur.
 *  game_t g: the game
 *
 *  Modifies the game, if there are rows or columns that can be reduced.
 */
void reduce(game_t g) {
  int old_m = -1;  // check for change in cols. If there is, redo sweep.
  while (g->m != old_m) {
    old_m = g->m;
    one_sweep(g);
  }
}

