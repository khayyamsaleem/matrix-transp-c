#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {

  if (argc != 4) {
    fprintf(stderr, "Wrong number of command-line arguments. \n Usage: ./transpif.c <arg1> <arg2>\n");
    return -1;
  }

  int matrix_height = atoi(argv[1]);
  int matrix_width = atoi(argv[2]);
  int block_width = atoi(argv[3]);

  /* Check if the block size is a power of 2. */
  if((((block_width > 0) && !(block_width & (block_width - 1))) == 0)) {
    fprintf(stderr, "Error: WAIT It is not a power of 2.\n");
    return -1;
  }

  /* Allocating memories for the matrix */
  float * matrix = (float *)malloc(sizeof(float) * matrix_height * matrix_width);

  /* Generating N x M matrix with random numbers */
  int i, j = 0;
  srand(time(NULL));
  for(i = 0; i < matrix_height; i++){
    for(j = 0; j < matrix_width; j++){
      // matrix[i*matrix_width + j] = ((float)rand() / (float)RAND_MAX * 100)+10;
      matrix[i*matrix_width + j] = ((float)rand() / (float)RAND_MAX * 100.0f);
    }
  }

  for(i = 0; i < matrix_height * matrix_width; i++){
    printf("%f\n", matrix[i]);
  }

  printf("\n\n");

  float * output_matrix = (float *)malloc(sizeof(float) * matrix_height * matrix_width);

  for(i = 0; i < matrix_height; i += block_width) {
    for(j = 0; j < matrix_width; j+= block_width) {
      for(int k = i; k < i + block_width; ++k) {
        for(int l = j; l < j + block_width; ++l) {
          output_matrix[k + l*matrix_height] = matrix[l + k*matrix_width];
        }
      }
    }
  }

  i = 0;
  for(i = 0; i < matrix_height * matrix_width; i++){
    printf("%f\n", output_matrix[i]);
  }

  free(matrix);
  free(output_matrix);

  return 0;
}

/*
1. matrices = not really a power of 2
2. block size = a power of 2
3. three arguments: the height, width, bloci_width(power of 2)
4. Use if statements to verify that all memory accesses are legal.
5. Accessing the 500th element of a raw with 499 elements is wrong, even though it still falls within the memory allocated for the matrix.
*/
