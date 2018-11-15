#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* function to create an array for the matrix with random numbers */
float * creating_matrix (float * matrix, int matrix_width, int matrix_height) {
  int i, j = 0;
  srand(time(NULL));
  for(i = 0; i < matrix_height; i++){
    for(j = 0; j < matrix_width; j++){
      matrix[i*matrix_width + j] = ((float)rand() / (float)RAND_MAX * 100.0f);
    }
  }
  return matrix;
}

float * transposition (float * matrix, float * output_matrix, int matrix_width, int matrix_height, int block_width) {
  for(int i = 0; i < matrix_height; i += block_width) {
    for(int j = 0; j < matrix_width; j += block_width) {
      if ((i + block_width <= matrix_height) && (j + block_width <= matrix_width)) {
        for(int k = i; k < i + block_width; ++k) {
          for(int l = j; l < j + block_width; ++l) {
            output_matrix[k + l*matrix_height] = matrix[l + k*matrix_width];
          }
        }
      } else {
        for(int k = i; k < matrix_height; ++k) {
          for(int l = j; l < matrix_width; ++l) {
            output_matrix[k + l*matrix_height] = matrix[l + k*matrix_width];
          }
        }
      }
    }
  }
  return output_matrix;
}

int main(int argc, char **argv) {

  int matrix_height = atoi(argv[1]);
  int matrix_width = atoi(argv[2]);
  int block_width = atoi(argv[3]);

  /* checking the number of arguments */
  if (argc != 4) {
    fprintf(stderr, "Wrong number of command-line arguments. \n Usage: ./transpif.c <arg1> <arg2>\n");
    return -1;
  }

  /* Check if the block size is a power of 2. */
  if((((block_width > 0) && !(block_width & (block_width - 1))) == 0)) {
    fprintf(stderr, "Error: WAIT It is not a power of 2.\n");
    return -1;
  }

  /* Check if block size is greater than matrix size */
  if(matrix_width < block_width || matrix_height < block_width) {
    fprintf(stderr, "Error: WAIT The block size cannot be greater than the matrix size.\n");
    return -1;
  }

  /* Allocating memories for the matrix */
  float * matrix = (float *)malloc(sizeof(float) * matrix_height * matrix_width);

  /* Generating N x M matrix with random numbers */
  matrix = creating_matrix(matrix, matrix_width, matrix_height);

  /* print out the original matrix */
  printf("*********input matrix*********\n");
  for(int i = 0; i < matrix_height; i++) {
    for(int j = 0; j < matrix_width; j++) {
      printf("%*.*f | ", 5, 2, matrix[i * matrix_width + j]);
    }
    printf("\n");
  }
  printf("\n");

  /* Dynamically allopcating memory spaces for the transposed matrix */
  float * output_matrix = (float *)malloc(sizeof(float) * matrix_height * matrix_width);

  /* transposition of the matrix */
  output_matrix = transposition(matrix, output_matrix, matrix_width, matrix_height, block_width);

  /* print out the transposed matrix */
  printf("*********transposed matrix*********\n");
  for(int i = 0; i < matrix_width; i++) {
    for(int j = i*matrix_height; j < (i*matrix_height) + matrix_height; j++) {
      printf("%5.2f | ", output_matrix[j]);
    }
    printf("\n");
  }
  printf("\n");

  free(matrix);
  free(output_matrix);

  return 0;
}
