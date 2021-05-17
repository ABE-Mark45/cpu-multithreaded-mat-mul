#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>
#include <stdlib.h>
#define ELEM(MAT, i, j) MAT->data[i][j]    // Macro to access array element


// struct to hold matrix data
typedef struct
{
    int rows;
    int cols;
    int **data;     // pointers to row beginnings
    int *internal;  // Elements are stored in a sequential manner
} Mat;

// Allocates necessary memory for matrices
void init_mat(Mat* mat);
// Read matrix from file
void read_mat(char *file_name, Mat *mat);
// Write matrix to file
void export_mat( char *file_name, Mat *mat);
// Deallocates matrices data
void cleanup(Mat *mat_a, Mat *mat_b, Mat *mat_c);

#endif