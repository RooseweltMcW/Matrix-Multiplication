#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <direct.h>
#include <errno.h> //For EEXIST
#include <time.h> //For clock_t,clock() & CLOCKS_PER_SEC
#include <stdio.h>
#include <string.h> // for strcmp

void matrix_multiply_ijk(int **A, int **B, int **C, int row, int col) {
    // Initialize the result matrix to zero
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            C[i][j] = 0;
            for (int k = 0; k < row; k++) { // Iterate based on the shared dimension (assuming it matches row)
                // printf("Multiplying A[%d][%d] = %d with B[%d][%d] = %d\n", i, k, A[i][k], k, j, B[k][j]);
                C[i][j] += A[i][k] * B[k][j];
            }
            // printf("Result C[%d][%d] = %d\n", i, j, C[i][j]);
        }
    }
}



void matrix_multiply_ikj(int **A, int **B, int **C, int row, int col) {
    // Initialize the result matrix to zero
    for (int i = 0; i < row; i++) {
        for (int k = 0; k < row; k++) { // Iterate based on shared dimension (assuming square matrix)
            for (int j = 0; j < col; j++) {
                if (k == 0) C[i][j] = 0; // Reset result element once at the start
                // printf("Multiplying A[%d][%d] = %d with B[%d][%d] = %d\n", i, k, A[i][k], k, j, B[k][j]);
                C[i][j] += A[i][k] * B[k][j];
                // printf("Intermediate Result C[%d][%d] = %d\n", i, j, C[i][j]);
            }
        }
    }
}

void matrix_multiply_jik(int **A, int **B, int **C, int row, int col) {
    // Initialize the result matrix to zero
    for (int j = 0; j < col; j++) {
        for (int i = 0; i < row; i++) {
            C[i][j] = 0; // Reset result element
            for (int k = 0; k < row; k++) { // Iterate based on shared dimension
                // printf("Multiplying A[%d][%d] = %d with B[%d][%d] = %d\n", i, k, A[i][k], k, j, B[k][j]);
                C[i][j] += A[i][k] * B[k][j];
            }
            // printf("Result C[%d][%d] = %d\n", i, j, C[i][j]);
        }
    }
}


void matrix_multiply_jki(int **A, int **B, int **C, int row, int col) {
    // Initialize the result matrix to zero
    for (int j = 0; j < col; j++) {
        for (int k = 0; k < row; k++) { // Iterate based on shared dimension
            for (int i = 0; i < row; i++) {
                if (k == 0) C[i][j] = 0; // Reset result element once at the start
                // printf("Multiplying A[%d][%d] = %d with B[%d][%d] = %d\n", i, k, A[i][k], k, j, B[k][j]);
                C[i][j] += A[i][k] * B[k][j];
                // printf("Intermediate Result C[%d][%d] = %d\n", i, j, C[i][j]);
            }
        }
    }
}


void matrix_multiply_kij(int **A, int **B, int **C, int row, int col) {
    // Initialize the result matrix to zero
    for (int k = 0; k < row; k++) { // Iterate based on shared dimension
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (k == 0) C[i][j] = 0; // Reset result element once at the start
                // printf("Multiplying A[%d][%d] = %d with B[%d][%d] = %d\n", i, k, A[i][k], k, j, B[k][j]);
                C[i][j] += A[i][k] * B[k][j];
                // printf("Intermediate Result C[%d][%d] = %d\n", i, j, C[i][j]);
            }
        }
    }
}


void matrix_multiply_kji(int **A, int **B, int **C, int row, int col) {
    // Initialize the result matrix to zero
    for (int k = 0; k < row; k++) { // Iterate based on shared dimension
        for (int j = 0; j < col; j++) {
            for (int i = 0; i < row; i++) {
                if (k == 0) C[i][j] = 0; // Reset result element once at the start
                // printf("Multiplying A[%d][%d] = %d with B[%d][%d] = %d\n", i, k, A[i][k], k, j, B[k][j]);
                C[i][j] += A[i][k] * B[k][j];
                // printf("Intermediate Result C[%d][%d] = %d\n", i, j, C[i][j]);
            }
        }
    }
}


int compare_matrix(int **A, int **B, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (A[i][j] != B[i][j]) {
                printf("Mismatch at [%d][%d]: Matrix 1 = %d, Matrix 2 = %d\n", 
                        i, j, A[i][j], B[i][j]);
                return 0;
            }
        }
    }
    printf("Both matrices are the same\n");
    return 1;
}


// Function to read a matrix from a file
void read_matrix(const char *filename, int **matrix, int row,int col) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }
    fclose(file);
}

void write_headers(const char *filename) {
    // Check if the file exists
    FILE *report_file = fopen(filename, "r");  
    if (report_file == NULL) {  // File doesn't exist
        report_file = fopen(filename, "w");
        if (report_file == NULL) {
            printf("Error opening report file for writing headers.\n");
            exit(1);
        }
        // Write headers to the CSV file
        fprintf(report_file, "\"Test Name\",\"Start Time\",\"End Time\",\"Time Spent\",\"Method\"\n");
        printf("Headers written to %s\n", filename); // Inform that headers are written
    } else {
        printf("File %s already exists. Headers will not be written.\n", filename); // File exists, no headers written
    }
    fclose(report_file);
}

void log_test_result(const char *test_name, const char *start_time, const char *end_time, double time_spent,const char *method) {
    FILE *report_file = fopen("report.csv", "a");  // Open in append mode
    if (report_file == NULL) {
        printf("Error opening report file for writing.\n");
        exit(1);
    }

    // Write a new row with test details
    fprintf(report_file, "\"%s\",\"%s\",\"%s\",\"%f\",\"%s\"\n", test_name, start_time, end_time, time_spent, method);

    fclose(report_file);
}
