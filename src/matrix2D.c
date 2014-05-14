// matrix2D.c
// Permite ingresar una matriz de m x n
// y luego la escribe en un archivo
#include <stdio.h>
#include <stdlib.h>

// estructura de la matriz
typedef struct {
   int n_rows;       // numero de renglones
   int n_cols;       // numero de columnas
   double **matrix;  // matriz de n_rows x n_cols
} Matrix2D;

// prototipos
Matrix2D* inputMatrix2D(void);
int matrix2DToDisk(Matrix2D* matrixPtr);
int freeMatrix2D(Matrix2D* matrixPtr);

int main() {
   Matrix2D *matrix_A_ptr;          // matriz a ingresar por el usuario

   matrix_A_ptr = inputMatrix2D();  // ingresar la matriz

   matrix2DToDisk(matrix_A_ptr);    // escribe la matriz en disco

   freeMatrix2D(matrix_A_ptr);      // libera la memoria
}  // end main

// captura los elementos de la matriz
Matrix2D* inputMatrix2D(void) {
   Matrix2D *matrix_in_ptr;
   int k;
   int m;
   int n;

   // asignacion dinamica
   matrix_in_ptr = (Matrix2D*)calloc(1, sizeof(Matrix2D));

   // interfaz con el usuario
   printf("%s", "Numero de renglones de la matriz: ");
   scanf("%d", &matrix_in_ptr->n_rows);
   printf("%s", "Numero de columnas de la matriz: ");
   scanf("%d", &matrix_in_ptr->n_cols);

   // asignacion dinamica
   matrix_in_ptr->matrix = (double**)calloc(matrix_in_ptr->n_rows,
                                            sizeof(double*));

   for (k = 0; k < matrix_in_ptr->n_rows; ++k) {
      matrix_in_ptr->matrix[k] = (double*)calloc(matrix_in_ptr->n_cols,
                                                 sizeof(double));
   }  // end for

   // ingresar la matriz
   for (m = 0; m < matrix_in_ptr->n_rows; ++m) {
      for (n = 0; n < matrix_in_ptr->n_cols; ++n) {
         printf("elemento [%d][%d]: ", m, n);
         scanf("%lf", &matrix_in_ptr->matrix[m][n]);
      }  // end for
   }  // end for

   return matrix_in_ptr;
}  // end of function inputMatrix2D

// escribe la matriz a un archivo de disco
int matrix2DToDisk(Matrix2D *matrixPtr) {
   int rows;         // matrix rows
   int cols;         // matix columns
   FILE *file_ptr;   // archivo de disco

   // apertura del archivo
   file_ptr = (FILE*)fopen("Matrix.txt", "w");

   if (file_ptr == NULL) {
      printf("%s", "Error en la apertura!");
      exit(0);
   }  // end if

   // escritura del archivo
   //fprintf(file_ptr, "\n");

   for (rows = 0; rows < matrixPtr->n_rows; ++rows) {
      for (cols = 0; cols < matrixPtr->n_cols; ++cols) {
         fprintf(file_ptr, "%7.2f\t", 
                 matrixPtr->matrix[rows][cols]);
      }  // end for
      fprintf(file_ptr, "\n");
   }  // end for

   // cerrar el archivo
   fclose(file_ptr);

   return 0;   // exito en la escritura
}  // end of function matrix2DToDisk

// libera la memoria asignada dinamicamente
int freeMatrix2D(Matrix2D *matrixPtr) {
   int k;

   // se libera lo mas anidado primero
   for (k = 0; k < matrixPtr->n_rows; ++k) {
      free(matrixPtr->matrix[k]);
   }  // end for
   free(matrixPtr->matrix);
   free(matrixPtr);

   return 0;   // exito en la liberacion de memoria
}  // end of function freeMatrix2D
