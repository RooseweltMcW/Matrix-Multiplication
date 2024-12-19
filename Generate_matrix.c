#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <direct.h>
#include <errno.h> //For EEXIST
#include <time.h> //For clock_t,clock() & CLOCKS_PER_SEC
#include <stdio.h>
#include <string.h> // for strcmp
#include "Matrix_multiply.c"
//base folder directory to store all the test cases
int test_case_file=1;
char base_folder[256]="Unit_test";
// snprintf(base_folder, sizeof(base_folder), "Unit_test");


// Create directory function that checks and creates the parent directory first
void create_directory(const char *name) {
    // Check if the base folder exists, create it if not
    if (_mkdir(base_folder) == 0) {
        printf("Base directory created: %s\n", base_folder);
    } else if (errno == EEXIST) {
        printf("Base directory already exists: %s\n", base_folder);
    } else {
        printf("Failed to create base directory: %s\n", base_folder);
        perror("Error");
        return;
    }

    // Now try creating the test case subfolder
    if (_mkdir(name) == 0) {
        printf("Directory created: %s\n", name);
    } else if (errno == EEXIST) {
        printf("Directory already exists: %s\n", name);
    } else {
        printf("Failed to create directory: %s\n", name);
        perror("Error");
    }
}



// Function to dynamically allocate 
int **allocate_matrix(int row,int col) {
    int **matrix = (int **)malloc(row * sizeof(int *));
    for (int i = 0; i < row; i++) {
        matrix[i] = (int *)malloc(col * sizeof(int));
    }
    return matrix;
}

void write_matrix_file(const char *filename, int **matrix,int rows,int cols) {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d ", matrix[i][j]); 
        }
        fprintf(file, "\n");
    }
    fclose(file);
}
void free_matrix(int **matrix, int row,int col) {
    for (int i = 0; i < row; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
void generate_test_case(int A_row,int A_col,int B_row,int B_col){
     // Initialize the random number generator

    int **A_matrix = allocate_matrix(A_row,A_col);
    int **B_matrix = allocate_matrix(B_row,B_col);
    int **C_matrix = allocate_matrix(A_row,B_col);
    char folder[256];
    char path[256];

    // Create a subfolder for this test case
    snprintf(folder, sizeof(folder), "%s/unit_%02d", base_folder, test_case_file++);
    create_directory(folder); // Create the directory (implement create_directory to use mkdir)
    // Fill matrices A with random values
    for (int i = 0; i < A_row; i++) {
        for (int j = 0; j < A_col; j++) {
            A_matrix[i][j] = rand() % 10;
        }
    }
    // Fill matrices B with random values
    for (int i = 0; i < B_row; i++) {
        for (int j = 0; j < B_col; j++) {
            B_matrix[i][j] = rand() % 10;
        }
    }
    int C_row=A_row;
    int C_col=B_col;
    // Perform matrix multiplication
    matrix_multiply_ijk(A_matrix, B_matrix, C_matrix, C_row,C_col);

    // Write A.txt, B.txt, and C.txt inside the subfolder
    snprintf(path, sizeof(path), "%s/A.txt", folder);
    write_matrix_file(path, A_matrix, A_row,A_col);

    snprintf(path, sizeof(path), "%s/B.txt", folder);
    write_matrix_file(path, B_matrix, B_row,B_col);

    snprintf(path, sizeof(path), "%s/C.txt", folder);
    write_matrix_file(path, C_matrix, C_row,C_col);

    // Free allocated memory
    free_matrix(A_matrix, A_row,A_col);
    free_matrix(B_matrix, B_row,B_col);
    free_matrix(C_matrix,C_row,C_col);

}

void clock_to_time_str(clock_t clock_time, char *time_str, size_t len) {
    // Convert clock_t to seconds
    double time_in_seconds = ((double)clock_time) / CLOCKS_PER_SEC;

    // Format the time string as required (seconds to string)
    snprintf(time_str, len, "%.6f", time_in_seconds);
}


void execute_test_case(const char *folder, int A_row, int A_col, int B_row, int B_col) {
    // Construct file paths for A.txt, B.txt, and C.txt
    char a_file[256], b_file[256], c_file[256];
    snprintf(a_file, sizeof(a_file), "%s/A.txt", folder);
    snprintf(b_file, sizeof(b_file), "%s/B.txt", folder);
    snprintf(c_file, sizeof(c_file), "%s/C.txt", folder);

    // Validate matrix dimensions for multiplication
    if (A_col != B_row) {
        fprintf(stderr, "Error: Dimension mismatch for matrix multiplication. A_col (%d) != B_row (%d).\n", A_col, B_row);
        return;
    }

    int C_row = A_row, C_col = B_col;

    // Allocate matrices and validate memory allocation
    int **A = allocate_matrix(A_row, A_col);
    int **B = allocate_matrix(B_row, B_col);
    int **C_txt = allocate_matrix(C_row, C_col);
    int **C_result = allocate_matrix(C_row, C_col);

    // Read matrices from files
    read_matrix(a_file, A, A_row, A_col);
    read_matrix(b_file, B, B_row, B_col);
    read_matrix(c_file, C_txt, C_row, C_col);

    const char *methods[] = {"ijk", "ikj", "jik", "jki", "kij", "kji"};

    // Loop through methods
    for (int i = 0; i < 6; i++) {
        clock_t start, end;
        double time_taken;

        // Record start time
        start = clock();

        // Choose the method based on the string match
        if (strcmp(methods[i], "ijk") == 0) {
            matrix_multiply_ijk(A, B, C_result, A_row, B_col);
        } else if (strcmp(methods[i], "ikj") == 0) {
            matrix_multiply_ikj(A, B, C_result, A_row, B_col);
        } else if (strcmp(methods[i], "jik") == 0) {
            matrix_multiply_jik(A, B, C_result, A_row, B_col);
        } else if (strcmp(methods[i], "jki") == 0) {
            matrix_multiply_jki(A, B, C_result, A_row, B_col);
        } else if (strcmp(methods[i], "kij") == 0) {
            matrix_multiply_kij(A, B, C_result, A_row, B_col);
        } else if (strcmp(methods[i], "kji") == 0) {
            matrix_multiply_kji(A, B, C_result, A_row, B_col);
        }

        // Record end time
        end = clock();

        // Calculate and display the time taken for multiplication
        time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Convert start and end times to formatted strings
        char start_time_str[100], end_time_str[100];
        clock_to_time_str(start, start_time_str, sizeof(start_time_str));
        clock_to_time_str(end, end_time_str, sizeof(end_time_str));

        // Log the test results
        log_test_result(folder, start_time_str, end_time_str, time_taken, methods[i]);
    }

    // Compare the result matrix with the expected matrix (C_txt)
    if (compare_matrix(C_txt, C_result, C_row, C_col)) {
        printf("Test Passed\n");
    } else {
        fprintf(stderr, "Test FAILED: Result matrix does not match expected matrix.\n");
    }

    // Free allocated matrices
    free_matrix(A, A_row, A_col);
    free_matrix(B, B_row, B_col);
    free_matrix(C_txt, C_row, C_col);
    free_matrix(C_result, C_row, C_col);
}
