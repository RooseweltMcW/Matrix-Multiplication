#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matmul.c"

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s <A.txt> <B.txt> <C.txt> <size>\n", argv[0]);
        return 1;
    }

    int size = atoi(argv[4]);
    int **A = allocate_matrix(size);
    int **B = allocate_matrix(size);
    int **C = allocate_matrix(size);
    int **C_expected = allocate_matrix(size);

    read_matrix(argv[1], A, size);
    read_matrix(argv[2], B, size);
    read_matrix(argv[3], C_expected, size);

    clock_t start, end;
    double cpu_time_used;

    // Measure time for ijk
    start = clock();
    matrix_multiply_ijk(A, B, C, size);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time (ijk): %f seconds\n", cpu_time_used);

    // Free memory
    free_matrix(A, size);
    free_matrix(B, size);
    free_matrix(C, size);
    free_matrix(C_expected, size);
    return 0;
}
