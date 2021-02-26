//============================================================================//
// ex010: dense representation of a matrix                                    //
//============================================================================//
#include <stdio.h>
#include <stdlib.h>

void printMatrix(int**, int, int);
void transpose(int**, int, int);

void main() {

  int i, j;
  int **matrix;
  matrix = malloc(6 * sizeof(*matrix));
  for(i=0; i<6; i++) {
    matrix[i] = malloc(6 * sizeof(**matrix));
    for(j=0; j<6; j++) {
      matrix[i][j] = 0;
    }
  }

  matrix[0][0] = 15;
  matrix[0][3] = 22;
  matrix[0][5] = 15;
  matrix[1][1] = 11;
  matrix[1][2] = 3;
  matrix[2][3] = 6;
  matrix[4][0] = 91;
  matrix[5][2] = 28;

  printMatrix(matrix, 6, 6);
  transpose(matrix, 6, 6);
  printMatrix(matrix, 6, 6);

  for(i=0; i<6; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

void printMatrix(int **m, int rows, int cols) {
  
  int i, j;
  for(i=0; i<rows; i++) {
    for(j=0; j<cols; j++) {
      printf("%3d ", m[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void transpose(int **m, int rows, int cols) {

  int i, j;
  int **temp;

  temp = malloc(rows * sizeof(*temp));
  for(i=0; i<rows; i++) {
    temp[i] = malloc(cols * sizeof(**temp));
    for(j=0; j<cols; j++) {
      temp[i][j] = m[i][j];
    }
  }

  for(i=0; i<rows; i++) {
    for(j=0; j<cols; j++) {
      m[i][j] = temp[j][i];
    }
  }

  for(i=0; i<rows; i++) {
    free(temp[i]);
  }
  free(temp);
}
  
   




