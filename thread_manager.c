#include "thread_manager.h"

void *calculate_element(void *arg)
{
    ElementArgs *index = (ElementArgs *)arg;
    const Mat *mat_a = index->mat_a;
    const Mat *mat_b = index->mat_b;
    Mat *mat_c = index->mat_c;
    int i = index->i, j = index->j;
    ELEM(mat_c, i, j) = 0;

    for (int k = 0; k < mat_a->cols; k++)
        ELEM(mat_c, i, j) += ELEM(mat_a, i, k) * ELEM(mat_b, k, j);
    return NULL;
}

void elementwise_thread(const Mat *mat_a, const Mat *mat_b, Mat *mat_c)
{
    // Allocate array of product size threads and ElementAtgs to the size of threads
    pthread_t *threads = (pthread_t *)malloc(sizeof(pthread_t) * mat_c->rows * mat_c->cols);
    ElementArgs *args = (ElementArgs *)malloc(sizeof(ElementArgs) * mat_c->rows * mat_c->cols);
    for (int i = 0; i < mat_c->rows; i++)
    {
        for (int j = 0; j < mat_c->cols; j++)
        {
            // initialize the args to the worker function
            int index = i * mat_c->cols + j;
            args[index].mat_a = mat_a;
            args[index].mat_b = mat_b;
            args[index].mat_c = mat_c;
            args[index].i = i;
            args[index].j = j;
            // Create thread
            pthread_create(threads + index, NULL, calculate_element, (void *)&args[index]);
        }
    }
    printf("[*] Created %d threads...\n", mat_c->rows * mat_c->cols);

    // Join all threads
    for (int i = 0, s = mat_c->rows * mat_c->cols; i < s; i++)
        pthread_join(threads[i], NULL);

    // deallocate threads and args
    free(threads);
    free(args);
}

void *calculate_row(void *arg)
{
    ElementArgs *index = (ElementArgs *)arg;
    const Mat *mat_a = index->mat_a;
    const Mat *mat_b = index->mat_b;
    Mat *mat_c = index->mat_c;
    int row = index->i;

    for (int j = 0; j < mat_c->cols; j++)
    {
        ELEM(mat_c, row, j) = 0;
        for (int k = 0; k < mat_a->cols; k++)
            ELEM(mat_c, row, j) += ELEM(mat_a, row, k) * ELEM(mat_b, k, j);
    }
    return NULL;
}


void rowwise_thread(const Mat *mat_a, const Mat *mat_b, Mat *mat_c)
{
    // Allocate array of product row size of threads and ElementArgs
    pthread_t *threads = (pthread_t *)malloc(sizeof(pthread_t) * mat_c->rows);
    ElementArgs *args = (ElementArgs *)malloc(sizeof(ElementArgs) * mat_c->rows);

    for (int i = 0; i < mat_c->rows; i++)
    {
        // Initialize args
        args[i].mat_a = mat_a;
        args[i].mat_b = mat_b;
        args[i].mat_c = mat_c;
        args[i].i = i;
        // create threads
        pthread_create(threads + i, NULL, calculate_row, (void *)&args[i]);
    }

    printf("[*] Created %d threads...\n", mat_c->rows);

    // join threads
    for (int i = 0; i < mat_c->rows; i++)
        pthread_join(threads[i], NULL);

    // deallocate threads and args
    free(threads);
    free(args);
}

void *one_thread(void *args)
{
    ElementArgs *index = (ElementArgs *)args;
    const Mat *mat_a = index->mat_a;
    const Mat *mat_b = index->mat_b;
    Mat *mat_c = index->mat_c;

    for (int i = 0; i < mat_c->rows; i++)
    {
        for (int j = 0; j < mat_c->cols; j++)
        {
            ELEM(mat_c, i, j) = 0;
            for (int k = 0; k < mat_a->cols; k++)
                ELEM(mat_c, i, j) += ELEM(mat_a, i, k) * ELEM(mat_b, k, j);
        }
    }
    return NULL;
}

void multiply_one_thread(const Mat *mat_a, const Mat *mat_b, Mat *mat_c)
{
    ElementArgs arg = {mat_a, mat_b, mat_c};
    pthread_t thread;

    pthread_create(&thread, NULL, one_thread, (void *)&arg);
    printf("[*] Created 1 thread...\n");
    pthread_join(thread, NULL);
}

void test_mat_mul(const Mat *mat_a, const Mat *mat_b, Mat *mat_c, void (*func)(const Mat *, const Mat *, Mat *), char *test_name)
{
    struct timeval start, stop;

    printf("[*] %s test\n", test_name);
    gettimeofday(&start, NULL);
    func(mat_a, mat_b, mat_c);
    gettimeofday(&stop, NULL);
    printf("[*] Seconds taken %lu\n", stop.tv_sec - start.tv_sec);
    printf("[*] Microseconds taken: %lu\n", stop.tv_usec - start.tv_usec);
    printf("-------------------------------------------------------\n");
}
