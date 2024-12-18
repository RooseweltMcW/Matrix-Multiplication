#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matmul.c"
int main(int argc, char *argv[]) {
    srand(time(NULL));

    // Define start, increment, and end sizes for testing
    int start_size = 100;
    int increment = 20;
    int end_size = 500;

    // Create the "Unit_test" directory for storing all test cases
    printf("Attempting to create directory: Unit_test\n");
    create_directory("Unit_test");

    // Loop through matrix sizes from start_size to end_size
    for (int size = start_size; size <= end_size; size += increment) {
        // Construct the directory name for each test case
        char folder[256];
        snprintf(folder, sizeof(folder), "Unit_test/unit_%d", size);

        printf("Running test case: %s with size %d\n", folder, size);

        // Create the specific directory for this test case
        create_directory(folder);

        // Generate test case files A.txt, B.txt, and C.txt
        generate_test_case(folder, size);

        // Run the test case for this folder and size
        run_test_case(folder, size, "Matrix Multiplication Test");

    }

    // Print a message after all tests are completed
    printf("All tests completed.\n");

    return 0;
}
