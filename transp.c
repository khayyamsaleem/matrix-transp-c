#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {

  if (argc != 3) {
    fprintf(stderr, "Wrong number of command-line arguments. \n Usage: ./transp.c <arg1> <arg2>\n");
    return -1;
  }

  int matrix_width = atoi(argv[1]);
  int block_width = atoi(argv[2]);

  /* Check if two arguments are numbers of power of 2. */
  if((((matrix_width > 0) && !(matrix_width & (matrix_width - 1))) == 0)
  || (((block_width > 0) && !(block_width & (block_width - 1))) == 0)) {
    fprintf(stderr, "Error: WAIT It is not a power of 2.\n");
    return -1;
  }
  if(matrix_width < block_width) {
    fprintf(stderr, "Error: WAIT The block size cannot be greater than the matrix size.\n");
    return -1;
  }

  float * matrix = (float *)malloc(sizeof(float) * matrix_width * matrix_width);

  int i, j = 0;
  srand(time(NULL));
  for(i = 0; i < matrix_width; i++){
    for(j = 0; j < matrix_width; j++){
      // matrix[i*matrix_width + j] = ((float)rand() / (float)RAND_MAX * 100)+10;
      matrix[i*matrix_width + j] = ((float)rand() / (float)RAND_MAX * 100.0f);
    }
  }

  for(i = 0; i < matrix_width * matrix_width; i++){
    printf("%f\n", matrix[i]);
  }

  printf("\n\n");

  float * output_matrix = (float *)malloc(sizeof(float) * matrix_width * matrix_width);

  for(i = 0; i < matrix_width; i += block_width) {
    for(j = 0; j < matrix_width; j+= block_width) {
      for(int k = i; k < i + block_width; ++k) {
        for(int l = j; l < j + block_width; ++l) {
          printf("i:%d, j:%d, k:%d, l:%d\n", i, j, k, l);
          output_matrix[k + l*matrix_width] = matrix[l + k*matrix_width];
          printf("matrix: %f -> output: %f\n", matrix[l + k*matrix_width], output_matrix[k + l*matrix_width]);
        }
      }
    }
  }

  printf("\n\n");

  i = 0;
  for(i = 0; i < matrix_width * matrix_width; i++){
    printf("%f\n", output_matrix[i]);
  }

  free(matrix);
  free(output_matrix);

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
