#include "matrix.h"


void init_mat(Mat* mat)
{
    mat->internal = (int *) malloc(sizeof(int) * mat->rows * mat->cols);
    mat->data = (int **) malloc(sizeof(int*) * mat->rows);

    for(int i = 0; i < mat->rows; i++)
        mat->data[i] = &mat->internal[i * mat->cols];
}

void read_mat(char *file_name, Mat *mat)
{
    FILE *file = fopen(file_name, "r");

    if (!file)
    {
        perror("File does not exist");
        exit(EXIT_FAILURE);
    }

    // Reads the matrix row and column in the format specified
    if (fscanf(file, "row=%d col=%d", &mat->rows, &mat->cols) != 2 || mat->rows <= 0 || mat->cols <= 0)
    {
        perror("invalid format");
        exit(EXIT_FAILURE);
    }

    // Dynamically allocate memory data
    init_mat(mat);

    for(int i = 0; i < mat->rows;i++)
        for(int j = 0; j < mat->cols; j++)
            if(fscanf(file, "%d", &ELEM(mat, i, j)) != 1)
            {
                perror("Not enough elements in the file");
                exit(EXIT_FAILURE);
            }

    // close the file
    fclose(file);
}

// Write the matrix to the supplied file name
void export_mat( char *file_name, Mat *mat)
{
    FILE *file = fopen(file_name, "w");

    if (!file)
    {
        perror("File does not exist");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "row=%d col=%d\n", mat->rows, mat->cols);
    for (int i = 0; i < mat->rows; i++)
    {
        for (int j = 0; j < mat->cols; j++)
            fprintf(file, "%d\t", ELEM(mat, i, j));
        fprintf(file, "\n");
    }
    fclose(file);
}

// Deallocates matrix data
void cleanup(Mat *mat_a, Mat *mat_b, Mat *mat_c)
{
    free(mat_a->data);
    free(mat_a->internal);

    free(mat_b->data);
    free(mat_b->internal);

    free(mat_c->data);
    free(mat_c->internal);
}
