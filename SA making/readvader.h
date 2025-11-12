#ifndef READVADER_H
#define READVADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct words
{
    char *word;
    float score;
    float SD;
    int SIS_array[10];
};

struct words *read_file(char *score_file_name, int *num_of_words);
float calculate_score(const struct words *words, const char *sentence, int *num_of_words);
char **read_lines(const char *filename, int *num_lines);
void rm_punctuation(char *str);

#endif