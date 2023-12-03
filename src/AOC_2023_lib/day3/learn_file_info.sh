#!/bin/bash

# Provide the path to your file
file_path="input"

# Read the file and store line length and count
while IFS= read -r line; do
    # Determine line length
    current_line_length=${#line}

    # Check if the length is greater than the maximum
    if ((current_line_length > max_line_length)); then
        max_line_length=$current_line_length
    fi

    # Increment line count
    ((line_count++))
done < "$file_path"

# increment line length to account for newline character at the end of each line
((max_line_length++))
((max_line_length++))

# Print the results
echo "Maximum line length: $max_line_length"
echo "Total number of lines: $line_count"
