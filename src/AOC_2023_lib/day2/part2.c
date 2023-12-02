// https://adventofcode.com/2023/day/2#part2

#include <stdio.h>

int parse_line(const char* input)
{
        // Skip characters until ':' is found
        while (*input != '\0' && *input != ':')
        {
                input++;
        }

        input++;

        int max_red = 0;
        int max_green = 0;
        int max_blue = 0;

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
                                // Update max_red if num is greater
                                if (num > max_red)
                                {
                                        max_red = num;
                                }
                                break;
                        case 'g':
                                // Update max_green if num is greater
                                if (num > max_green)
                                {
                                        max_green = num;
                                }
                                break;
                        case 'b':
                                // Update max_blue if num is greater
                                if (num > max_blue)
                                {
                                        max_blue = num;
                                }
                                break;
                        default:
                                // Invalid color, do nothing
                                break;
                }

                // Move to the next character
                input++;
        }

        // Return the product of the maximum values
        return max_red * max_green * max_blue;
}

int day2_part2()
{
        FILE *fp;
        fp = fopen("../src/AOC_2023_lib/day2/input", "r");

        if (fp == NULL)
        {
                printf("Could not open file %s", "../src/AOC_2023_lib/day2/input");
                return 1;
        }

        char buff[255];
        long total = 0;
        long game_id = 1;

        while (fgets(buff, 255, fp) != NULL)
        {
                printf("%s", buff);
                long result = parse_line(buff);

                printf("Game %ld: %d\n", game_id, result);
                total += result;
                game_id++;
        }
        fclose(fp);

        printf("Total: %ld\n", total);

        return 0;
}
