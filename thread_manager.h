#ifndef THREAD_MANGER_H
#define THREAD_MANGER_H
#include <pthread.h>
#include <stdlib.h>
#include "matrix.h"
#include <sys/time.h>

// Thread argument struct
typedef struct
{
    const Mat *mat_a, *mat_b;
    Mat *mat_c;
    int i;
    int j;
} ElementArgs;

// Worker functions
// ------------------

// Thread worker function that calculates each element in the i, j location
void *calculate_element(void *arg);

// Thread worker function that calculates each element in the i_th row
void *calculate_row(void *arg);

// Calculates the matrix product in only one thread
void *one_thread(void *args);


// Invokers
// --------
// All invokers manage creating threads and passing arguments for the workers

void elementwise_thread(const Mat *mat_a, const Mat *mat_b, Mat *mat_c);
void rowwise_thread(const Mat *mat_a, const Mat *mat_b, Mat *mat_c); 
void multiply_one_thread(const Mat *mat_a, const Mat *mat_b, Mat *mat_c);

// Tester
// ------

// A unified interface to run all tests. Matrix pointers and the function of choice and test name are supplied
// The function calculates the time of execution for each test
void test_mat_mul(const Mat *mat_a, const Mat *mat_b, Mat *mat_c,
                    void (*func)(const Mat *, const Mat *, Mat *), char *test_name);

#endif