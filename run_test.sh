#!/bin/bash

# Set variables for the files
PROGRAM_NAME="matmul"
DRIVER_FILE="driver.c"
# MATMUL_FILE="matmul.c"
OUTPUT_DIR="results"
REPORT_FILE="test_report.csv"

# Create output directory if it doesn't exist
mkdir -p $OUTPUT_DIR

# Step 1: Compile the program
echo "Compiling the program..."
gcc $DRIVER_FILE -o $PROGRAM_NAME

# Check if compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed. Exiting."
    exit 1
fi
echo "Compilation successful!"