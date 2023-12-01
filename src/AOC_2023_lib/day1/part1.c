// https://adventofcode.com/2023/day/1

#include <stdio.h>

int day1_part1()
{
        // loop through file located at path ./input.txt

        FILE *fp;
        fp = fopen("../src/AOC_2023_lib/day1/input", "r");

        if (fp == NULL)
        {
                printf("Error opening file!\n");
                return 1;
        }

        // read file line by line
        char line[256];
        long num_sum = 0;

        while (fgets(line, sizeof(line), fp))
        {
               // loop through the line and skip any non-number character (ascii code 48-57)
               char first_char_num = 0;
               char last_char_num = 0;

               for (int i = 0; line[i] != 0; i++)
               {
                       // print the character and its ascii code
                       //printf("char: %c, ascii: %d\n", line[i], line[i]);
                       if (line[i] < 48 || line[i] > 57)
                       {
                               continue;
                       }
                       if (first_char_num == 0)
                       {
                               first_char_num = line[i];
                       }

                       last_char_num = line[i];
               }

               long num = (first_char_num - 48) * 10 + (last_char_num - 48);

               printf("num: %ld\n", num);
               printf("line: %s\n", line);
               num_sum += num;

               // clear buffer bit xor
               for (int i = 0; i < sizeof(line); i++)
               {
                       line[i] = 0;
               }

        }

        fclose(fp);
        printf("max value: %ld\n", num_sum);
        return 0;
}