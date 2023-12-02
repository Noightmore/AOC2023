// https://adventofcode.com/2023/day/2

#include <stdio.h>

extern long parse_game(char* line, unsigned char red_bound, unsigned char green_bound, unsigned char blue_bound);

int parse_line(const char* input, int red_upper_bound, int green_upper_bound, int blue_upper_bound)
{
        // Skip characters until ':' is found
        while (*input != '\0' && *input != ':')
        {
                input++;
        }

        input++;

        // Parse loop
        while (*input != '\0')
        {
                // Skip characters until a digit is found
                while (*input != '\0' && (*input < '0' || *input > '9'))
                {
                        input++;
                }

                if (*input == '\0')
                {
                        break;
                }

                // Parse the number
                int num = 0;
                while (*input >= '0' && *input <= '9')
                {
                        num = num * 10 + (*input - '0');
                        input++;
                }

                // Determine the color
                char color = *(input + 1);

                printf("%d", num);
                printf("%c\n", color);

                switch (color)
                {
                        case 'r':
                                // Check if red count exceeds the upper bound
                                if (num > red_upper_bound)
                                {
                                        return 0;  // false
                                }
                                break;
                        case 'g':
                                // Check if green count exceeds the upper bound
                                if (num > green_upper_bound)
                                {
                                        return 0;  // false
                                }
                                break;
                        case 'b':
                                // Check if blue count exceeds the upper bound
                                if (num > blue_upper_bound)
                                {
                                        return 0;  // false
                                }
                                break;
                        default:
                                // Invalid color, do nothing
                                break;
                }

                // Move to the next character
                input++;
        }

        return 1;  // true
}

int day2_part1()
{

        FILE *fp;
        fp = fopen("../src/AOC_2023_lib/day2/input", "r");

        unsigned char red_bound = 12;
        unsigned char green_bound = 13;
        unsigned char blue_bound = 14;

        if (fp == NULL)
        {
                printf("Could not open file %s", "../src/AOC_2023_lib/day2/input");
                return 1;
        }

        char buff[255];
        long valid_games_count = 0;
        long game_id = 1;

        while (fgets(buff, 255, fp) != NULL)
        {
                printf("%s", buff);
                //long val = parse_game(buff, red_bound, green_bound, blue_bound);
                long val = parse_line(buff, red_bound, green_bound, blue_bound);
                printf("val: %ld\n", val);
                valid_games_count += game_id * val;
                game_id++;
        }
        fclose(fp);

        printf("valid games count: %ld\n", valid_games_count);
        // valid games count: 2447

        return 0;
}