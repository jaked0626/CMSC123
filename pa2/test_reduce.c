#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "reduce_game.h"


/* test: run a single test using the files in directory/test<NUM> */
void test(char *dirname, int num) {
  // create the name of the directory with the original game
  char orig_filename[strlen(dirname) +strlen("/test") + 1 + strlen("/original") + 1];
  sprintf(orig_filename, "%s/test%d/original", dirname, num);
  game_t g = mk_game(orig_filename);

  // reduce the game
  reduce(g);

  // create the name of the directory with the reduced game
  char expected_filename[strlen(dirname) + strlen("/test") + 1 + strlen("/reduced") + 1];
  sprintf(expected_filename, "%s/test%d/reduced", dirname, num);
  game_t expected_g = mk_game(expected_filename);

  /* check and report result */
  printf("Test %s/test%d: ", dirname, num);
  if (!are_equal_game(g, expected_g)) {
    printf("Failed:\nExpected:\n");
    print_game(expected_g);
    printf("\nGot:\n");
    print_game(g);
  } else {
    printf("Success\n");
  }
    printf("\n");
  /* free the space associated with the games */
  free_game(g);
  free_game(expected_g);

}

int main(int argc, char **argv) {
  int num_tests = 7;
  if ((argc < 2) || (argc > 3)){
    printf("Usage: ./%s <Data Directory> [test number 0-%d]\n", argv[0], num_tests-1);
    exit(0);
  }

  if (argc == 3) {
    // do specified test
    int test_num = atoi(argv[2]);
    if ((test_num < 0) || (test_num >= num_tests)) {
      printf("Usage: ./%s <Data Directory> [test number 0-%d]\n", argv[0], num_tests-1);
      exit(0);
    }
    test(argv[1], atoi(argv[2]));
  } else {
    // do all tests
    for (int i = 0; i < num_tests; i++) 
      test(argv[1], i);
  }
}
