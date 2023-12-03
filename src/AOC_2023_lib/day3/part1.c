// https://adventofcode.com/2023/day/3

#include <stdio.h>

typedef unsigned char uint8_t;

void process_line(char* buffer, char* line, const char* symbols);
int is_special_symbol(char c, const char* special_symbols);
uint8_t check_left_and_right_symbols(int char_pos, const char* line_to_check);
uint8_t is_digit(char c);


int day3_part1()
{
        char special_symbols[] = {'#', '+', '$', '%',
                                  '&', '/', '(', ')', '=',
                                  '?', '!', '@', '*', '^',
                                  '~', '-', '_', ',', ';',
                                  ':','<', '>','|', '[',
                                  ']', '{', '}', '\0'};


        FILE *fp;
        fp = fopen("../src/AOC_2023_lib/day3/input", "r");

        if (fp == NULL)
        {
                (void) printf("Could not open file %s", "../src/AOC_2023_lib/day3/input");
                return 1;
        }

        char buffer[256];
        char prev_line[256];

        // clear buffers
        for (int i = 0; i < 256; i++)
        {
                buffer[i] = '\0';
                prev_line[i] = '\0';
        }

        while (fgets(buffer, 256, fp) != NULL)
        {
                printf("previous line %s", prev_line);
                printf("current line: %s", buffer);

                process_line(buffer, prev_line, special_symbols);
                printf("%s", "                            \n");
        }

        (void) fclose(fp);


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

uint8_t check_left_and_right_symbols(int char_pos, const char* line_to_check)
{
        // returns the number of digits found
        // byte encoding
        // 0b00000000 = no digits found
        // 0b00000001 = digit found on the left
        // 0b00000010 = digit found on the right
        // 0b00000011 = digit found on the left and right

        // 0b00000100 = digit found on the left on the previous line
        // 0b00001000 = digit found on the right on the previous line
        // 0b00001100 = digit found on the left and right on the previous line


        // check if found special symbol is at the start of the line
        if (char_pos == 0)
        {
                // only check right symbol
                // is a symbol to the right a number?
                return is_digit(line_to_check[char_pos + 1]) << 1;
        }

        // check if found special symbol is at the end of the line
        if (line_to_check[char_pos + 1] == '\0')
        {
                // only check left symbol
                // is a symbol to the left a number?
                return is_digit(line_to_check[char_pos - 1]);
        }

        // check both left and right symbols
        // is a symbol to the left a number?
        // is a symbol to the right a number?
        return (is_digit(line_to_check[char_pos - 1])) | is_digit(line_to_check[char_pos + 1]) << 1;
}


void process_line(char* buffer, char* prev_line, const char* special_symbols)
{

        for (int char_pos = 0; buffer[char_pos] != '\0'; char_pos++) // for each character in buffer
        {
                char character_in_buffer = buffer[char_pos]; // alias

                if (is_special_symbol(character_in_buffer, special_symbols))
                {
                        // current line check
                        (void) printf("Found special symbol: %c\n", character_in_buffer);
                        int special_character_pos = char_pos;

                        uint8_t digits_found = check_left_and_right_symbols(special_character_pos, buffer);
                        (void) printf("Digits found on current line: %d\n", digits_found);

                        // previous line check (ABOVE)
                        if (prev_line[0] != '\0')
                        {
                                digits_found |= check_left_and_right_symbols(
                                        special_character_pos, prev_line) << 2;

                                //(void) printf("Digits found on previous line: %d\n", (digits_found % digits_found >> 1) + 1);
                                (void) printf("Digits found on previous line: %d\n", digits_found & 0b00001100);
                        }

                }
        }





        // copy buffer to prev_line and clear buffer
        for (int i = 0; buffer[i] != '\0'; i++)
        {
                prev_line[i] = buffer[i];
                buffer[i] = '\0';
        }
}
