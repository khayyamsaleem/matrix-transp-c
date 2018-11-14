#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {

  int matrix_width = atoi(argv[1]);
  int block_width = atoi(argv[2]);

  if (argc != 3) {
    fprintf(stderr, "Wrong number of command-line arguments. \n Usage: ./transp.c <arg1> <arg2>\n");
    return -1;
  }

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

  printf("*********input matrix*********\n");
  for (i = 0; i < matrix_width; i++) {
    for(j = 0; j < matrix_width; j++) {
      printf("%*.*f ", 5, 2, matrix[i * matrix_width + j]);
    }
    printf("\n");
  }
  printf("\n");

  float * output_matrix = (float *)malloc(sizeof(float) * matrix_width * matrix_width);

  for(i = 0; i < matrix_width; i += block_width) {
    for(j = 0; j < matrix_width; j+= block_width) {
      for(int k = i; k < i + block_width; ++k) {
        for(int l = j; l < j + block_width; ++l) {
          output_matrix[k + l*matrix_width] = matrix[l + k*matrix_width];
        }
      }
    }
  }

  printf("*********transposed matrix*********\n");
  for (i = 0; i < matrix_width; i++) {
    for(j = 0; j < matrix_width; j++) {
      printf("%*.*f ", 5, 2, output_matrix[i * matrix_width + j]);
    }
    printf("\n");
  }

  printf("\n");

  free(matrix);
  free(output_matrix);

  return 0;
}
