// https://adventofcode.com/2023/day/2

#include <stdio.h>
#include <alloca.h>
#include <regex.h>

typedef struct regex_num_patterns {
        char* pattern;
        char num;
} regex_num_patterns;


void set_first_and_last_num(char* first, char* last, const char* line, const regex_num_patterns* patterns)
{
        int first_pos = 2147483647;
        int last_pos = 0;

        for (int i = 0; line[i] != 0; i++)
        {
                // print the character and its ascii code
                //printf("char: %c, ascii: %d\n", line[i], line[i]);
                if (line[i] < 48 || line[i] > 57)
                {
                        continue;
                }
                if (*first == 0)
                {
                        *first = line[i];
                        first_pos = i;
                }

                *last = line[i];
                last_pos = i;
        }

        // using regex to find the first and last number

        // Iterate through patterns
        // Iterate through patterns
        for (int i = 0; i < 10; ++i)
        {
                regex_t regex;
                if (regcomp(&regex, patterns[i].pattern, 0) == 0)
                {
                        regmatch_t match;
                        int first_pos_reg = -1;
                        int last_pos_reg = -1;

                        // Iterate through input string to find matches
                        for (int j = 0; line[j] != 0; ++j)
                        {
                                if (regexec(&regex, line + j, 1, &match, 0) == 0)
                                {
                                        int index = j + match.rm_so;

                                        if (first_pos_reg == -1)
                                        {
                                                first_pos_reg = index;
                                        }

                                        last_pos_reg = index;

                                        // Print result for the current pattern
                                        printf("Pattern %c matched at index %d\n", patterns[i].num, index);

                                        // keep the information about the matches indexes and value for the most left and right match
                                        if (first_pos_reg != -1)
                                        {
                                                if (first_pos == -1 || first_pos_reg < first_pos)
                                                {
                                                        first_pos = first_pos_reg;
                                                        *first = patterns[i].num;
                                                }
                                        }

                                        if (last_pos_reg != -1)
                                        {
                                                if (last_pos == -1 || last_pos_reg > last_pos)
                                                {
                                                        last_pos = last_pos_reg;
                                                        *last = patterns[i].num;
                                                }
                                        }
                                }
                        }

                        regfree(&regex);
                }
        }

        // print the first and last character and their indexes for the regex method
        printf("first: %c, last: %c\n", *first, *last);
        printf("first pos: %d, last pos: %d\n", first_pos, last_pos);


}


int day1_part2()
{
        //region regex_num_patterns
        regex_num_patterns* patterns = alloca(sizeof(regex_num_patterns) * 10);

        patterns[0].pattern = "zero";
        patterns[0].num = '0';

        patterns[1].pattern = "one";
        patterns[1].num = '1';

        patterns[2].pattern = "two";
        patterns[2].num = '2';

        patterns[3].pattern = "three";
        patterns[3].num = '3';

        patterns[4].pattern = "four";
        patterns[4].num = '4';

        patterns[5].pattern = "five";
        patterns[5].num = '5';

        patterns[6].pattern = "six";
        patterns[6].num = '6';

        patterns[7].pattern = "seven";
        patterns[7].num = '7';

        patterns[8].pattern = "eight";
        patterns[8].num = '8';

        patterns[9].pattern = "nine";
        patterns[9].num = '9';
        //endregion

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

                set_first_and_last_num(&first_char_num, &last_char_num, line, patterns);

                // print the first and last character
                printf("first: %c, last: %c\n", first_char_num, last_char_num);

                long num = (first_char_num - 48) * 10 + (last_char_num - 48);

                printf("num: %ld\n", num);
                printf("line: %s\n", line);

                num_sum += num;

                // clear buffer
                for (int i = 0; i < sizeof(line); i++)
                {
                        line[i] = 0;
                }

        }

        fclose(fp);
        printf("num sum: %ld\n", num_sum);
        return 0;
}
