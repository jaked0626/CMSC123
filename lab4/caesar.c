#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

char shiftchar(char c, int shift) {
  // YOUR CODE HERE
  // replace `0` with correct return value
  return '0';
}

void encryptinplace(char *s, int shift) {
  // YOUR CODE HERE

}

char *encryptnewmemory(char *s, int shift) {
  // YOUR CODE HERE
  // replace malloc(1) with correct return value
  // included only to make sure code compiles and runs
  return malloc(1);
}


int main(int argc, char *argv[]) {
  // check lower case
  printf("shiftchar('a', -1)): %c\n", shiftchar('a', -1));
  printf("shiftchar('z', 3)): %c\n", shiftchar('z', 3));

  // check upper case
  printf("shiftchar('G', 1)): %c\n", shiftchar('G', 1));
  printf("shiftchar('Z', 3)): %c\n", shiftchar('Z', 3));

  // check non-letters
  printf("shiftchar('!', 3)): %c\n", shiftchar('!', 3));  
  printf("\n\n");

  char *message = strdup("Hello World!");
  printf("\n\nmessage    : %s\n", message);
  encryptinplace(message, 5); // this changes message
  printf("ciphertext : %s\n", message);
  free(message);   // free space we got from strdup

  message = strdup("Hello World!");
  char *ciphertext = encryptnewmemory(message, 5);
  printf("\n\nMessage should be unchanged\n");
  printf("message    : %s\n", message);
  printf("ciphertext : %s\n", ciphertext);
  free(message);    // free space we got from strdup
  free(ciphertext);  // free space we got from encryptnewmemory

  message = strdup("M! K fobi pkcd, iod kd dswoc pbecdbkdsxq vkxqekqo.");
  ciphertext = encryptnewmemory(message, -10);
  printf("\n\nMessage should be unchanged\n");
  printf("message    : %s\n", message);
  printf("ciphertext : %s\n", ciphertext);
  free(message);    // free space we got from strdup
  free(ciphertext);  // free space we got from encryptnewmemory
  return 0;
}
