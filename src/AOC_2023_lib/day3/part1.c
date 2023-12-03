// https://adventofcode.com/2023/day/3

#include <stdio.h>
#include <alloca.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 140
#define MAX_LINE_LENGTH 142
#define FILE_PATH "../src/AOC_2023_lib/day3/input"

typedef unsigned char uint8_t;

int process_line(const char* current_line, const char* prev_line_up,
                 const char* next_line_down, const char* special_symbols);
int is_special_symbol(char c, const char* special_symbols);
uint8_t is_digit(char c);


int day3_part1()
{
        char special_symbols[] = {'#', '+', '$', '%',
                                  '&', '/', '(', ')', '=',
                                  '?', '!', '@', '*', '^',
                                  '~', '-', '_', ',', ';',
                                  ':','<', '>','|', '[',
                                  ']', '{', '}', '\0'};

        FILE *file;
        const char *lines[MAX_LINES];
        char buffer[MAX_LINE_LENGTH];
        int line_count = 0;

        // Open the file for reading
        file = fopen(FILE_PATH, "r");
        if (file == NULL)
        {
                fprintf(stderr, "Error opening file\n");
                return 1;
        }

        // Read lines from the file
        while (fgets(buffer, sizeof(buffer), file) != NULL)
        {
                // Remove newline character at the end
                buffer[strcspn(buffer, "\n")] = '\0';

                // Allocate memory for the line and copy the content
                lines[line_count] = strdup(buffer);

                if (lines[line_count] == NULL)
                {
                        fprintf(stderr, "Memory allocation error\n");
                        return 1;
                }

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

        // Print the stored lines for demonstration
//        for (int i = 0; i < line_count; i++)
//        {
//                printf("Line %d: %s\n", i + 1, lines[i]);
//        }

        int t_sum = 0;

        // line processing here
        for (int i = 0; i < line_count; i++)
        {
                // if lines is the first line then provide NULL provide string full of .

                char dots[MAX_LINE_LENGTH];
                for (int j = 0; j < MAX_LINE_LENGTH-2; j++)
                {
                        dots[j] = '.';
                }
                dots[MAX_LINE_LENGTH-2] = '\0';

                if (i == 0)
                {
                        t_sum += process_line(lines[i], dots, lines[i+1], special_symbols);
                        continue;
                }

                if (i == line_count-1)
                {
                        t_sum += process_line(lines[i], lines[i-1], dots, special_symbols);
                        continue;
                }

                t_sum += process_line(lines[i], lines[i-1], lines[i+1], special_symbols);
        }

        printf("total sum: %d\n", t_sum);

        // Free allocated memory
        for (int i = 0; i < line_count; i++)
        {
                free((void *) lines[i]);
        }

        return 0;

}


int check_for_special_symbols(int num_pos, const char* current_line,
                              const char* prev_line_up, const char* next_line_down,
                              const char* special_symbols)
{
        // check if the number is surrounded by special symbols
        // if it is, then we return 1, else we return 0


        // check current line -- is at left or at right

        // only check left if num_pos is not 0
        if (num_pos != 0)
        {
                if (is_special_symbol(current_line[num_pos-1], special_symbols))
                {
                        return 1;
                }
                // check if left diagonally
                if (is_special_symbol(prev_line_up[num_pos-1], special_symbols))
                {
                        return 1;
                }
                // check if left diagonally
                if (is_special_symbol(next_line_down[num_pos-1], special_symbols))
                {
                        return 1;
                }
        }

        // only check right if num_pos is not at the end
        if (num_pos != strlen(current_line)-1)
        {
                if (is_special_symbol(current_line[num_pos+1], special_symbols))
                {
                        return 1;
                }

                // check if right diagonally
                if (is_special_symbol(prev_line_up[num_pos+1], special_symbols))
                {
                        return 1;
                }

                // check if right diagonally
                if (is_special_symbol(next_line_down[num_pos+1], special_symbols))
                {
                        return 1;
                }
        }

        // check prev line -- is up
        if (is_special_symbol(prev_line_up[num_pos], special_symbols))
        {
                return 1;
        }

        // check the next line -- is down
        if (is_special_symbol(next_line_down[num_pos], special_symbols))
        {
                return 1;
        }
        return 0;
}


int is_special_symbol(char c, const char* special_symbols)
{
        int i = 0;
        while (special_symbols[i] != '\0')
        {
                if (c == special_symbols[i])
                {
                        return 1;
                }
                i++;
        }
        return 0;
}


uint8_t is_digit(char c)
{
        if (c >= '0' && c <= '9')
        {
                return (uint8_t) 0b00000001;
        }
        return (uint8_t) 0b00000000;
}


int process_line(const char* current_line, const char* prev_line_up,
                 const char* next_line_down, const char* special_symbols)
{
        // loop through each line and look for number characters
        // if we found a digit, then we move the pointer until there are no more digits

        int lines_valid_num_sum = 0;

        char temp[MAX_LINE_LENGTH*2];
        // clear temp
        for(int i = 0; i < MAX_LINE_LENGTH*2; i++)
        {
                temp[i] = '\0';
        }

        int temp_pos = 0;
        int res_total_val = 0;

        for(int i = 0; i < MAX_LINE_LENGTH; i++)
        {
                if (is_digit(current_line[i]))
                {
                       temp[temp_pos] = current_line[i];

                       // need to check around the number if there are special symbols
                       int result = check_for_special_symbols(i, current_line,
                                                              prev_line_up, next_line_down,
                                                              special_symbols);
                       res_total_val += result;
                       //printf("result: %d\n", result);
                       temp_pos++;
                       continue;
                }

                // convert the contents of temp to an integer
                if(res_total_val > 0)
                {
                        int res = atoi(temp);
                        printf("res: %d\n", res);
                        lines_valid_num_sum += res;
                        res_total_val = 0;
                }

                // clear temp and temp_pos
                for(int j = 0; j < MAX_LINE_LENGTH*2; j++)
                {
                        temp[j] = '\0';
                }
                temp_pos = 0;

        }

        printf("prev_line_up:   %s\n", prev_line_up);
        printf("current line:   %s\n", current_line);
        printf("next_line_down: %s\n", next_line_down);
        printf("-------------------\n");

        return lines_valid_num_sum;
}
