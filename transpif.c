#include <stdio.h>

int main(int argc, char **argv) {

  if (argc != 4) {
    fprintf(stderr, "Wrong number of command-line arguments. \n Usage: ./transpif.c <arg1> <arg2>\n");
    return -1;
  }

  return 0;
}

/*
1. matrices = not really a power of 2
2. block size = a power of 2
3. three arguments: the height, width, bloci_width(power of 2)
4. Use if statements to verify that all memory accesses are legal.
5. Accessing the 500th element of a raw with 499 elements is wrong, even though it still falls within the memory allocated for the matrix.
*/
