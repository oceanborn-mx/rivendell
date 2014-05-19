// matrix2D.cpp
// Permite ingresar una matriz de m x n
// y luego la escribe en un archivo
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "IllegalSizeException.h"   // IllegalSizeException class
using namespace std;

// matrix structure
typedef struct {
   int n_rows;       // number of rows
   int n_cols;       // number of columns
   double **matrix;  // n_rows x n_cols matrix
} Matrix2D;

// prototypes
Matrix2D* inputMatrix2D(void);
Matrix2D* matrixMultiplication(Matrix2D*, Matrix2D*);
Matrix2D* upperTriangularMatrix(Matrix2D*);
int matrix2DToDisk(Matrix2D*);
int freeMatrix2D(Matrix2D*);

int main() {
   Matrix2D *matrix_A_ptr;          // matriz a ingresar por el usuario
   Matrix2D *matrix_B_ptr;          // matriz a ingresar por el usuario
   Matrix2D *matrix_AB_ptr;         // matrix multiplication result
   Matrix2D *matrix_L_ptr;          // matrix L (upper)

   matrix_A_ptr = inputMatrix2D();  // enter the first matrix
   matrix_B_ptr = inputMatrix2D();  // enter the second matrix

   // matrix multiplication
   try {
      matrix_AB_ptr = matrixMultiplication(matrix_A_ptr, matrix_B_ptr);

      matrix2DToDisk(matrix_AB_ptr);   // write the matrix into a disk file

      freeMatrix2D(matrix_AB_ptr);     // release allocated memory
   }  // end try
   catch (IllegalSizeException &illegalSizeException) {
      cout << "Exception occurred: " << illegalSizeException.what() << endl;
   }  // end catch

   try {
      matrix_L_ptr = upperTriangularMatrix(matrix_A_ptr);

      matrix2DToDisk(matrix_L_ptr);

      freeMatrix2D(matrix_L_ptr);
   }  // end try
   catch (IllegalSizeException &illegalSizeException) {
      cout << "Exception occurred: " << illegalSizeException.what() << endl;
   }  // end catch

   // freeing memory allocaded dynamically
   freeMatrix2D(matrix_A_ptr);
   freeMatrix2D(matrix_B_ptr);
   
   // zero pointers after free to avoid reuse
   matrix_A_ptr = NULL;
   matrix_B_ptr = NULL;
   matrix_AB_ptr = NULL;
   matrix_L_ptr = NULL;
}  // end main

// captura los elementos de la matriz
Matrix2D* inputMatrix2D(void) {
   Matrix2D *matrix_in_ptr;

   // dynamic memory allocation
   matrix_in_ptr = (Matrix2D*)calloc(1, sizeof(Matrix2D));

   // end-user interface
   cout << "Numero de renglones de la matriz: ";
   cin >> matrix_in_ptr->n_rows;
   cout << "Numero de columnas de la matriz: ";
   cin >> matrix_in_ptr->n_cols;

   // dynamic memory allocation
   matrix_in_ptr->matrix = (double**)calloc(matrix_in_ptr->n_rows,
                                            sizeof(double*));

   for (size_t k = 0; k < matrix_in_ptr->n_rows; ++k) {
      matrix_in_ptr->matrix[k] = (double*)calloc(matrix_in_ptr->n_cols,
                                                 sizeof(double));
   }  // end for

   // enter the matrix
   for (size_t m = 0; m < matrix_in_ptr->n_rows; ++m) {
      for (size_t n = 0; n < matrix_in_ptr->n_cols; ++n) {
         cout << "elemento [" << m << "][" << n << "]: ";
         cin >> matrix_in_ptr->matrix[m][n];
      }  // end for
   }  // end for

   return matrix_in_ptr;
}  // end of function inputMatrix2D

// escribe la matriz a un archivo de disco
int matrix2DToDisk(Matrix2D *matrixPtr) {
   FILE *file_ptr;   // disk file

   // opening the file
   file_ptr = (FILE*)fopen("Matrix.txt", "w");

   if (file_ptr == NULL) {
      cout << "Error en la apertura del archivo!";
      exit(0);
   }  // end if

   // writing the file
   for (size_t rows = 0; rows < matrixPtr->n_rows; ++rows) {
      for (size_t cols = 0; cols < matrixPtr->n_cols; ++cols) {
         fprintf(file_ptr, "%7.2f\t", 
                 matrixPtr->matrix[rows][cols]);
      }  // end for
      fprintf(file_ptr, "\n");
   }  // end for

   // closing the file
   fclose(file_ptr);

   return 0;   // exito en la escritura
}  // end of function matrix2DToDisk

// Matrix multiplication algorithm
Matrix2D* matrixMultiplication(Matrix2D* matrixA, Matrix2D* matrixB) {
   Matrix2D *matrixAB;  // matrix product

   // checking proper size
   if (matrixA->n_cols != matrixB->n_rows)
      throw IllegalSizeException(); // terminate function

   // dynamic memory allocation
   matrixAB = (Matrix2D*)calloc(1, sizeof(Matrix2D));

   // sizing matrix A*B
   matrixAB->n_rows = matrixA->n_rows;
   matrixAB->n_cols = matrixB->n_cols;

   // dynamic memory allocation
   matrixAB->matrix = (double**)calloc(matrixAB->n_rows, sizeof(double*));

   for (size_t k = 0; k < matrixAB->n_rows; ++k) {
      matrixAB->matrix[k] = (double*)calloc(matrixAB->n_cols, sizeof(double));
   }  // end for

   // raw algorithm
   for (size_t i = 0; i < matrixA->n_rows; ++i) {
      for (size_t j = 0; j < matrixB->n_cols; ++j) {
         for (size_t k = 0; k < matrixA->n_cols; ++k) {
            matrixAB->matrix[i][j] += matrixA->matrix[i][k] * matrixB->matrix[k][j];
         }  // end for
      }  // end for
   }  // end for

   return matrixAB;
}  // end of matrixMultiplication function

// LU Matrix factorization
Matrix2D* upperTriangularMatrix(Matrix2D* matrixF) {
   Matrix2D *matrixU;   // upper matrix

   // checking proper size
   if (matrixF->n_rows != matrixF->n_cols)
      throw IllegalSizeException(); // terminate function

   // dynamic allocation memory
   matrixU = (Matrix2D*)calloc(1, sizeof(Matrix2D));

   // sizing matrix U
   matrixU->n_rows = matrixF->n_rows;
   matrixU->n_cols = matrixF->n_cols;

   // dynamic memory allocation
   matrixU->matrix = (double**)calloc(matrixU->n_rows, sizeof(double*));

   for (size_t k = 0; k < matrixU->n_rows; ++k) {
      matrixU->matrix[k] = (double*)calloc(matrixU->n_cols, sizeof(double));
   }  // end for

   // TODO: Optimize assigment, if possible
   for (size_t i = 0; i < matrixU->n_rows; ++i) {
      for (size_t j = 0; j < matrixU->n_cols; ++j) {
         matrixU->matrix[i][j] = matrixF->matrix[i][j];
      }  // end for
   }  // end for

   // raw algorithm
   for (size_t k = 0; k < (matrixU->n_rows - 1); ++k) {
      for (size_t i = 1 + k; i < matrixU->n_rows; ++i) {

         double temp = matrixU->matrix[i][k];   // hold the scale factor
         
         for (size_t j = 0 + k; j < matrixU->n_cols; ++j) {
            matrixU->matrix[i][j] -= (temp / matrixU->matrix[k][k]) * matrixU->matrix[k][j];
         }  // end for
      }  // end for
   }  // end for

   return matrixU;
}  // end of luMatrixFactorization function

// release the memory allocated dynamically
int freeMatrix2D(Matrix2D* matrixPtr) {

   // the most nested is released firts
   for (size_t k = 0; k < matrixPtr->n_rows; ++k) {
      free(matrixPtr->matrix[k]);
   }  // end for
   free(matrixPtr->matrix);
   free(matrixPtr);

   return 0;   // exito en la liberacion de memoria
}  // end of function freeMatrix2D
