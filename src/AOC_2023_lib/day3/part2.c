#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 100
#define MAX_LINE_LENGTH 100
#define FILE_PATH "../src/AOC_2023_lib/day3/input"

// Function to calculate the gear ratio
long long calculateGearRatio(int num1, int num2)
{
        return (long long)num1 * num2;
}

// Function to check if a given position is valid in the array
int isValidPosition(int row, int col, int maxRows, int maxCols)
{
        return (row >= 0 && row < maxRows && col >= 0 && col < maxCols);
}

int day3_part2()
{

        FILE *file;
        char buffer[MAX_LINES][MAX_LINE_LENGTH];
        int line_count = 0;
        long long total_gear_ratio = 0;

        // Open the file for reading
        file = fopen(FILE_PATH, "r");
        if (file == NULL)
        {
                fprintf(stderr, "Error opening file\n");
                return 1;
        }

        // Read lines from the file
        while (fgets(buffer[line_count], sizeof(buffer[line_count]), file) != NULL)
        {
                // Remove newline character at the end
                buffer[line_count][strcspn(buffer[line_count], "\n")] = '\0';
                line_count++;

                // Check if the maximum number of lines is reached
                if (line_count >= MAX_LINES)
                {
                        fprintf(stderr, "Exceeded maximum number of lines\n");
                        break;
                }
        }

        // Close the file
        fclose(file);

        // Calculate total gear ratio
        for (int r = 0; r < line_count; r++)
        {
                for (int c = 0; c < strlen(buffer[r]); c++)
                {
                        if (buffer[r][c] != '*')
                        {
                                continue;
                        }

                        // Set to store adjacent positions
                        int cs[2][2] = {0};
                        int cs_count = 0;

                        for (int dr = -1; dr <= 1; dr++)
                        {
                                for (int dc = -1; dc <= 1; dc++)
                                {
                                        if (dr == 0 && dc == 0)
                                        {
                                                continue; // Skip the current position
                                        }

                                        int row = r + dr;
                                        int col = c + dc;

                                        // Check if the position is valid and contains a digit
                                        if (isValidPosition(row, col, line_count,
                                                            strlen(buffer[row]))
                                                            && isdigit(buffer[row][col]))
                                        {
                                                while (col > 0 && isdigit(buffer[row][col - 1]))
                                                {
                                                        col--;
                                                }
                                                cs[cs_count][0] = row;
                                                cs[cs_count][1] = col;
                                                cs_count++;
                                        }
                                }
                        }

                        if (cs_count != 2)
                        {
                                continue;
                        }

                        // Extract and calculate gear ratio
                        int ns[2] = {0};
                        for (int i = 0; i < cs_count; i++)
                        {
                                char s[MAX_LINE_LENGTH];
                                int cc = cs[i][1];
                                int j = 0;

                                while (cc < strlen(buffer[cs[i][0]]) && isdigit(buffer[cs[i][0]][cc]))
                                {
                                        s[j++] = buffer[cs[i][0]][cc++];
                                }

                                s[j] = '\0';
                                ns[i] = atoi(s);
                        }

                        // Add gear ratio to total
                        total_gear_ratio += calculateGearRatio(ns[0], ns[1]);
                }
        }

        // Print the total gear ratio
        printf("Total Gear Ratio: %lld\n", total_gear_ratio);

        return 0;
}
