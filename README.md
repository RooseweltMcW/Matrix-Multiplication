matrix multiplication project

overview
this project performs matrix multiplication tests. it generates matrices, runs tests, and stores the results in folders. a summary of the execution times is saved in a csv file.

how to use

requirements
- c compiler (e.g., gcc)
- bash shell (linux, macos, or windows with wsl/git bash)

steps
1. run the shell script:
   ```bash
   bash run_test.sh
   ```
   this will:
   - compile the program.
   - run tests with different matrix sizes.
   - save results in the `unit_test` folder.
   - generate a `report.csv` with execution times.

output
for each matrix size, a folder will be created inside `unit_test/`. each folder contains:
- `a.txt`: matrix a
- `b.txt`: matrix b
- `c.txt`: result of a × b
- `time.log`: time taken for the test

a `report.csv` file will summarize the execution times:
```
matrix_size,execution_time
100,0.0023
120,0.0038
```

customization
to change the matrix sizes, edit `driver.c`:
```c
int start_size = 100;
int increment = 20;
int end_size = 500;
```

troubleshooting
- ensure all files (`driver.c`, `matmul.c`, `matmul.h`) are in the same directory.
- if you have permission issues, run `chmod +x run_test.sh`.
- if you run out of memory, try reducing matrix sizes.

this setup automates matrix multiplication tests and records performance times.