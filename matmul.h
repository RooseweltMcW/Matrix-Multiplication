#ifndef MATMUL_H
#define MATMUL_H

// Function declarations
void create_directory(const char *dir);
void matrix_multiply(int **A, int **B, int **C, int size, char loop_order);
int compare_matrix(int **A, int **B, int row, int col);
void read_matrix(const char *filename, int **matrix, int size);
void free_matrix(int **matrix, int size);
void write_matrix_to_file(const char *filename,int **matrix, int rows, int cols);
void write_matrix_result_to_file(const char *filename, int **matrix, int rows, int cols);
void generate_test_case(const char *folder, int size);
int **allocate_matrix(int size);
void run_test_case(const char *folder, int size, const char *test_name);
void log_test_result(const char *filename, const char *test_name, const char *start_time, const char *end_time, double time_spent);
#endif // MATMUL_H
