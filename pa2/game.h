#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

typedef struct game_s {
  int n;             // number of rows
  int m;             // number of columns
  double **player1;  // payoffs for player 1
  double **player2;  // payoffs for player 2
  int orig_n;        // do not change after initialized
  int orig_m;        // do not change after initialized
} *game_t;

/* mk_game: load a game from the specified directory */
game_t mk_game(char *dirname);

/* free_game: free the memory associated with the specified game */
void free_game(game_t g);

/* print_game: print the contents of the specified game to the screen */
void print_game(game_t g);


/* remove_row_game: remove the specified row from the specified game.
 * The rows following the specified row are shifted to fill the gap.
 */
void remove_row_game(game_t g, int row_num);


/* remove_col_game: remove the specified column from the specified
 * game.  The columns following the specified column are shifted to fill
 * the gap.
 */
void remove_col_game(game_t g, int col_num);


/* are_equal_game: returns true if g0 and g1 have the same shape and payoffs for each
 *  player and false otherwise.  Used only by test code. 
 */
bool are_equal_game(game_t g0, game_t g1);



#endif
