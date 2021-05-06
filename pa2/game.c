/* CS 123
 * Basic Game Theory: Reducing Games
 *
 * Data structure for representing games.
 *
 * DO NOT MODIFY THIS FILE.
 *
 *
 * Anne Rogers
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include "double_table.h"
#include "util.h"
#include "game.h"

#define TOLERANCE 10e-6

/* mk_game: load a game from the data in the specified directory */
game_t mk_game(char *dirname) {
  char filename[strlen(dirname) + strlen("/player1.txt") + 1];
  sprintf(filename, "%s/player1.txt", dirname);
  double_table_t player1 = mk_double_table(filename);

  sprintf(filename,"%s/player2.txt", dirname);
  double_table_t player2 = mk_double_table(filename);

  if ((player1->n != player2->n) ||
      (player1->m != player2->m)) {
    printf("Fatal error: %s player1 and player2 do not have the same shape",
                      dirname);
    exit(0);
  }

  //  game_t g = (game_t) ck_malloc(sizeof(struct game_s));
  game_t g = (game_t) ck_malloc(sizeof(*g));
  g->n = player1->n;
  g->m = player1->m;
  g->orig_n = player1->n;
  g->orig_m = player1->m;
  g->player1 = player1->data;
  g->player2 = player2->data;
  
  // note that we are only freeing the struct that holds
  // n, m and a pointer to player's data.  We are not freeing
  // the data associated with the player.
  free(player1);
  free(player2);

  return g;
}

/* free_game: free the memory associated with the specified game */
void free_game(game_t g) {
  free_2d((void **) g->player1, g->orig_n);
  free_2d((void **) g->player2, g->orig_n);
  free(g);
}

/* remove_row_game:
 *  game_t g: the game
 *  int row_num: the row to be removed
 *
 * Remove the specified row from the specified game.  The rows
 * following the specified row are shifted to fill the gap.
 */
void remove_row_game(game_t g, int row_num) {
  assert(g != NULL);
  int n = g->n;
  assert(row_num < n);

  // shift valid rows left
  double *row1 = g->player1[row_num];
  double *row2 = g->player2[row_num];
  for (int i = row_num; i < g->n-1; i++) {
    g->player1[i] = g->player1[i+1];
    g->player2[i] = g->player2[i+1];
  }

  // decrease the number of valid rows
  g->n = n-1;

  // save row for later disposal
  g->player1[n-1] = row1;
  g->player2[n-1] = row2;
}



/* remove_col_game:
 *  game_t g: the game
 *  int col_num: the column to be removed
 *
 * Remove the specified column from the specified game.  The columns
 * following the specified column are shifted to fill the gap.
 */
void remove_col_game(game_t g, int col_num) {
  assert(g != NULL);
  int m = g->m;
  assert(col_num < m);

  for (int i = 0; i < g->n; i++) {
    // shift all values in the row left by 1
    for (int j = col_num; j < g->m-1; j++) {
      g->player1[i][j] = g->player1[i][j+1];
      g->player2[i][j] = g->player2[i][j+1];
    }
  }

  // decrease the number of columns
  g->m = m-1;
}



/* print: print the game */
void print_game(game_t g) {
  int n = g->n;
  int m = g->m;

  for (int i = 0; i < n; i++) {
    printf("\t");
    for (int j = 0; j < m; j++) {
      printf("(%f, %f)\t", g->player1[i][j], g->player2[i][j]);
    }
    printf("\n");
  }
}

/* are_equal:
 *   Game g0: a game
 *   Game g1: another game
 *
 *   Returns: true if the two games are the same and
 *     false otherwise.
 */
bool are_equal_game(game_t g0, game_t g1) {
  // are the games the same shape?
  if ((g0->n != g1->n) ||
      (g0->m != g1->m)) {
    return false;
  }

  for (int i = 0; i < g0->n; i++) {
    for (int j = 0; j < g0->m; j++) {
      // do the entries match for both players?
      if (fabs(g0->player1[i][j] - g1->player1[i][j]) > TOLERANCE ||
          fabs(g0->player2[i][j] - g1->player2[i][j]) > TOLERANCE)
        return false;
    }
  }

  return true;
}

