#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

float * creating_matrix (float * matrix, int matrix_width);
int display_matrix (float * matrix, int matrix_width);
float * transposition (float * matrix, float * output_matrix, int matrix_width, int block_width);

/* function to create an array for the matrix with random numbers */
float * creating_matrix (float * matrix, int matrix_width) {
  int i, j = 0;
  srand(time(NULL));
  for(i = 0; i < matrix_width; i++){
    for(j = 0; j < matrix_width; j++){
      matrix[i*matrix_width + j] = ((float)rand() / (float)RAND_MAX * 100.0f);
    }
  }
  return matrix;
}

/* function for displaying matrices */
int display_matrix (float * matrix, int matrix_width) {
  for (int i = 0; i < matrix_width; i++) {
    for(int j = 0; j < matrix_width; j++) {
      printf("| %5.2f |", matrix[i * matrix_width + j]);
    }
    printf("\n");
  }
  printf("\n");
  return 0;
}

/* function to transpose a matrix */
float * transposition (float * matrix, float * output_matrix, int matrix_width, int block_width) {
  int i, j = 0;
  for(i = 0; i < matrix_width; i += block_width) {
    for(j = 0; j < matrix_width; j += block_width) {
      for(int k = i; k < i + block_width; ++k) {
        for(int l = j; l < j + block_width; ++l) {
          output_matrix[k + l*matrix_width] = matrix[l + k*matrix_width]; //8192 2 - 0.84s 4 - 0.73s
          //output_matrix[l*matrix_width + k] = matrix[l + k*matrix_width]; //8192 2 - 0.83s 4 - 0.71s
          //output_matrix[l*matrix_width + k] = matrix[k*matrix_width + l]; //8192 2 - 0.84s
          //output_matrix[matrix_width*l + k] = matrix[matrix_width*k + l]; //8192 2 - 0.84s
          //output_matrix[k + matrix_width*l] = matrix[l + matrix_width*k]; //8192 2 - 0.87s
        }
      }
    }
  }
  return output_matrix;
}

int main(int argc, char **argv) {

  struct timeval tv1, tv2;

  int matrix_width = atoi(argv[1]);
  int block_width = atoi(argv[2]);

  /* checking the number of arguments */
  if (argc != 3) {
    fprintf(stderr, "Wrong number of command-line arguments. \n Usage: ./transp.c <matrix size> <block size>\n");
    return -1;
  }

  /* Check if two arguments are numbers of power of 2. */
  if((((matrix_width > 0) && !(matrix_width & (matrix_width - 1))) == 0)
  || (((block_width > 0) && !(block_width & (block_width - 1))) == 0)) {
    fprintf(stderr, "Error: WAIT It is not a power of 2.\n");
    return -1;
  }

  /* Check if block size is greater than matrix size */
  if(matrix_width < block_width) {
    fprintf(stderr, "Error: WAIT The block size cannot be greater than the matrix size.\n");
    return -1;
  }

  /* Dynamically allocating memory spaces for input matrix */
  float * matrix = (float *)malloc(sizeof(float) * matrix_width * matrix_width);

  /* creating matrix array with random numbers */
  matrix = creating_matrix(matrix, matrix_width);

  /* print out the original matrix */
  printf("INPUT MATRIX:\n");
  //display_matrix(matrix, matrix_width);

  /* Dynamically allocating memory spaces for the transposed matrix */
  float * output_matrix = (float *)malloc(sizeof(float) * matrix_width * matrix_width);

  gettimeofday(&tv1, NULL);

  /* transposition of the matrix */
  output_matrix = transposition(matrix, output_matrix, matrix_width, block_width);

  gettimeofday(&tv2, NULL);
  /* print out the transposed matrix */
  printf("TRANSPOSED MATRIX:\n");
  //display_matrix(output_matrix, matrix_width);

  //printf("Total time = %f\n", (double)(tv2.tv_usec - tv1.tv_usec)/1000000 + (double)(tv2.tv_usec - tv1.tv_usec));
  /* In second */
  printf("Total time = %ld seconds\n", (tv2.tv_sec - tv1.tv_sec));
  /* In microsecond */
  printf("Total time = %f microseconds\n", (double)(tv2.tv_usec - tv1.tv_usec)/1000000 + (double)(tv2.tv_sec - tv1.tv_sec));

  /* free memories */
  free(matrix);
  free(output_matrix);

  return 0;
}
