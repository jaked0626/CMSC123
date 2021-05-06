#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *mystrcat(char *s, char *t) {
  // YOUR CODE HERE
  // replace "" with appropriate return value
  return "";
}

int main(int argc, char *argv[]) {
  char *rv = mystrcat("hello", " world");
  printf("mystrcat(\"hello\", \" world\"): %s\n", rv);
  free(rv);   // assumes mystrcat calls malloc

  // 2nd arg is the empty string
  rv = mystrcat("hello", "");
  printf("mystrcat(\"hello\", \"\"): %s\n", rv);
  free(rv);

  //  1st arg is the empty string
  rv = mystrcat("", " world");
  printf("mystrcat(\"\", \" world\"): %s \n", rv);
  free(rv);

  // both args are empty
  rv = mystrcat("", "");
  printf("mystrcat(\"\", \"\"): %s\n", rv);
  free(rv); 
  return 0;
}
