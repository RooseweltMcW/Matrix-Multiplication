#!/bin/bash

# Compile the program
gcc driver.c -o matmul -O2

# CSV Output File
output_file="results.csv"
echo "Size,ijk_time" > $output_file

# Matrix sizes from 100 to 500 in steps of 20
for size in $(seq 100 20 500); do
    echo "Running test for size $size"

    A="Unit_test/unit_${size}/A.txt"
    B="Unit_test/unit_${size}/B.txt"
    C="Unit_test/unit_${size}/C.txt"

    # Run the driver program and capture time
    time_output=$(./matmul $A $B $C $size | grep "Time (ijk):" | awk '{print $3}')

    # Append results to CSV
    echo "$size,$time_output" >> $output_file
done

echo "Tests complete. Results saved in $output_file."
