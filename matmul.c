#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <direct.h>
#include <errno.h> //For EEXIST
#include <time.h> //For clock_t,clock() & CLOCKS_PER_SEC
#include <stdio.h>
#include <string.h> // for strcmp

void matrix_multiply_ijk(int **A, int **B, int **C, int size) {
    // Initialize the result matrix to zero
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = 0;
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matrix_multiply_ikj(int **A, int **B, int **C, int size) {
    // Initialize the result matrix to zero
    for (int i = 0; i < size; i++) {
        for (int k = 0; k < size; k++) {
            for (int j = 0; j < size; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matrix_multiply_jik(int **A, int **B, int **C, int size) {
    // Initialize the result matrix to zero
    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size; i++) {
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matrix_multiply_jki(int **A, int **B, int **C, int size) {
    // Initialize the result matrix to zero
    for (int j = 0; j < size; j++) {
        for (int k = 0; k < size; k++) {
            for (int i = 0; i < size; i++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matrix_multiply_kij(int **A, int **B, int **C, int size) {
    // Initialize the result matrix to zero
    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matrix_multiply_kji(int **A, int **B, int **C, int size) {
    // Initialize the result matrix to zero
    for (int k = 0; k < size; k++) {
        for (int j = 0; j < size; j++) {
            for (int i = 0; i < size; i++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
void matrix_multiply(int **A, int **B, int **C, int size) {
    char *choice[] = {"ijk", "ikj", "jik", "jki", "kij", "kji"};
    
    for (int i = 0; i < 6; i++) {
        if (strcmp(choice[i], "ijk") == 0) {
            matrix_multiply_ijk(A, B, C, size);
        }
        else if (strcmp(choice[i], "ikj") == 0) {
            matrix_multiply_ikj(A, B, C, size);
        }
        else if (strcmp(choice[i], "jik") == 0) {
            matrix_multiply_jik(A, B, C, size);
        }
        else if (strcmp(choice[i], "jki") == 0) {
            matrix_multiply_jki(A, B, C, size);
        }
        else if (strcmp(choice[i], "kij") == 0) {
            matrix_multiply_kij(A, B, C, size);
        }
        else if (strcmp(choice[i], "kji") == 0) {
            matrix_multiply_kji(A, B, C, size);
        }
    }
}

void create_directory(const char *name) {
    if (_mkdir(name) == 0) {
        printf("Directory created: %s\n", name);
    } else if (errno == EEXIST) {
        printf("Directory already exists: %s\n", name);
    } else {
        printf("Failed to create directory: %s\n", name);
        perror("Error");  // This will print more details
    }
}



int compare_matrix(int **A, int **B, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (A[i][j] != B[i][j]) {
                printf("Mismatch at [%d][%d]: Matrix 1 = %d, Matrix 2 = %d\n", i, j, A[i][j], B[i][j]);
                return 0;
            }
        }
    }
    printf("Both matrices are the same\n");
    return 1;
}

// Function to read a matrix from a file
void read_matrix(const char *filename, int **matrix, int size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }
    fclose(file);
}

void free_matrix(int **matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to write a matrix to a file
void write_matrix_to_file(const char *filename,int **matrix, int rows, int cols) {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d ", matrix[i][j]);  // Random values [0-9]
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void write_matrix_result_to_file(const char *filename, int **matrix,int rows,int cols) {
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d ", matrix[i][j]);  // Random values [0-9]
        }
        fprintf(file, "\n");
    }
    fclose(file);
}
// Function to generate matrices and expected output
void generate_test_case(const char *folder, int size) {
    char path[256];
    int **A = malloc(size * sizeof(int *));
    int **B = malloc(size * sizeof(int *));
    int **C = malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        A[i] = malloc(size * sizeof(int));
        B[i] = malloc(size * sizeof(int));
        C[i] = malloc(size * sizeof(int));
    }

    // Fill matrices A and B with random values
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            A[i][j] = rand()%10 ;
            B[i][j] = rand()%10;
        }
    }
    matrix_multiply(A,B,C,size);
    // Write A.txt, B.txt, and C.txt
    snprintf(path, sizeof(path), "%s/A.txt", folder);
    write_matrix_to_file(path,A, size, size);

    snprintf(path, sizeof(path), "%s/B.txt", folder);
    write_matrix_to_file(path,B, size, size);

    snprintf(path, sizeof(path), "%s/C.txt", folder);
    write_matrix_result_to_file(path,C,size,size);

    // Free memory
    for (int i = 0; i < size; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
}
void log_test_result(const char *filename, const char *test_name, const char *start_time, const char *end_time, double time_spent) {
    FILE *report_file = fopen(filename, "a");  // Open in append mode
    if (report_file == NULL) {
        printf("Error opening report file for writing.\n");
        exit(1);
    }

    // Write a new row with test details
    fprintf(report_file, "\"%s\",\"%s\",\"%s\",\"%f\n", test_name, start_time, end_time, time_spent);

    fclose(report_file);
}
// Function to dynamically allocate a square matrix
int **allocate_matrix(int size) {
    int **matrix = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int *)malloc(size * sizeof(int));
    }
    return matrix;
}
void run_test_case(const char *folder, int size, const char *test_name) {
    char path[256];
    

    // Construct file paths for A.txt, B.txt, and C.txt
    snprintf(path, sizeof(path), "%s/A.txt", folder);
    char *A_file_path = strdup(path);  // Duplicate the string for later use
    snprintf(path, sizeof(path), "%s/B.txt", folder);
    char *B_file_path = strdup(path);
    snprintf(path, sizeof(path), "%s/C.txt", folder);
    char *C_file_path = strdup(path);

    // Allocate matrices
    int **A_text_matrix = allocate_matrix(size);
    int **B_text_matrix = allocate_matrix(size);
    int **result = allocate_matrix(size);          // Result of A x B
    int **C_text_matrix = allocate_matrix(size); // Expected matrix from C.txt

    // Capture the start time
    time_t start_time = time(NULL);
    struct tm *start_tm = localtime(&start_time);
    char start_time_str[100];


    // Read matrices A, B, and C_expected from files
    read_matrix(A_file_path, A_text_matrix, size);
    read_matrix(B_file_path, B_text_matrix, size);
    read_matrix(C_file_path, C_text_matrix, size);

    // Multiply matrices A and B to get C
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    matrix_multiply(A_text_matrix, B_text_matrix, result, size); // Using the ijk loop implementation
    end = clock();

    // Capture the end time
    time_t end_time = time(NULL);
    struct tm *end_tm = localtime(&end_time);
    char end_time_str[100];
    strftime(end_time_str, sizeof(end_time_str), "%H:%M:%S", end_tm);

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Matrix multiplication completed in %f seconds\n", cpu_time_used);

    // Log the test details into the CSV file
    // log_test_result(report_file, test_name, start_time_str, end_time_str, cpu_time_used);

    // Compare the result with the expected matrix
    if (compare_matrix(result, C_text_matrix, size, size)) {
        printf("Test PASSED: The result matches the expected matrix.\n");
    } else {
        printf("Test FAILED: The result does not match the expected matrix.\n");
    }

    // Free dynamically allocated memory
    free(A_file_path);
    free(B_file_path);
    free(C_file_path);
    free_matrix(A_text_matrix, size);
    free_matrix(B_text_matrix, size);
    free_matrix(result, size);
    free_matrix(C_text_matrix, size);
}