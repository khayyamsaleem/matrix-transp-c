#include <stdio.h>

int main(int argc, char **argv) {

  if (argc != 3) {
    fprintf(stderr, "Wrong number of command-line arguments. \n Usage: ./transp.c <arg1> <arg2>\n");
    return -1;
  }

  return 0;
}

/*
1. the matrix should be transposed in square blocks
2. width = a power of 2
3. two argument: the width of the input matrix and the width of the block
  + no need to verify that they are powers of 2
4. 1D arrays by calling malloc() to allocate space for N x N x floats, where N is the width of the matrix
5. the element at row i and column j can ve accessed using A[i*N + j]
6. the input matrix should be initialized randomly using rand()
*/
