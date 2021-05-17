#include <stdlib.h>
#include "matrix.h"
#include "thread_manager.h"

// Parses user supplied arguments
void parse_args(int argc, char **argv, char **mat_a_file, char **mat_b_file, char **mat_c_file)
{
    if (argc == 4)
    {
        *mat_a_file = argv[1];
        *mat_b_file = argv[2];
        *mat_c_file = argv[3];
    }
    else
    {
        *mat_a_file = "a.txt";
        *mat_b_file = "b.txt";
        *mat_c_file = "c.out";
    }
}

int main(int argc, char **argv)
{
    Mat mat_a, mat_b, mat_c;
    char *mat_a_file, *mat_b_file, *mat_c_file;

    parse_args(argc, argv, &mat_a_file, &mat_b_file, &mat_c_file);
    read_mat(mat_a_file, &mat_a);
    read_mat(mat_b_file, &mat_b);

    if (mat_a.cols != mat_b.rows)
    {
        perror("invalid matrix sizes");
        exit(EXIT_FAILURE);
    }

    mat_c.rows = mat_a.rows;
    mat_c.cols = mat_b.cols;
    // mat_c.data = (int *)malloc(sizeof(int) * mat_c.rows * mat_c.cols);
    init_mat(&mat_c);

    test_mat_mul(&mat_a, &mat_b, &mat_c, multiply_one_thread, "Thread per Matrix Multiplication");
    test_mat_mul(&mat_a, &mat_b, &mat_c, rowwise_thread, "Thread per Row Multiplication");
    test_mat_mul(&mat_a, &mat_b, &mat_c, elementwise_thread, "Thread per Element Multiplication");

    export_mat(mat_c_file, &mat_c);
    cleanup(&mat_a, &mat_b, &mat_c);
    return 0;
}