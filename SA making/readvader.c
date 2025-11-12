#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "readvader.h"

struct words *read_file(char *score_file_name, int *num_of_words)
{
    // open and read the file containing the score
    FILE *file = fopen(score_file_name,"r"); 
    // print error if file is empty
    if (file == NULL) 
    {
        printf("Error opening the file.\n");
        return NULL;
    }
    
    struct words *words_array = NULL;
    int array_size = 0;
    int index = 0;
    while (1) 
    {
        // Allocate memory for a new word when needed
        if (index == array_size) 
        {
            if (array_size > 0)
            {
                array_size *= 2;
            }
            else
            {
                array_size = 1;
            }

            // memory allocated using realloc and used to create an array of the words
            words_array = realloc(words_array, array_size *sizeof(struct words));
        }

        struct words *word = &words_array[index];

        // Read the word exracted from the file
        int character = fgetc(file); // Read the next character
        if (character == EOF) // check if it is the end-of-file marker
        { 
            break;
        }

        // seperate the words by checking if the next chatacter is a space, tab , new line or the end of the file
        int len = 0;
        while (character != EOF && character != ' ' && character != '\t' && character != '\n') 
        {
            // store the words extracted using realloc
            word->word = realloc(word->word, (len + 1) * sizeof(char));
            word->word[len] = character;
            word->word[len+1] = '\0';
            len++;
            character = fgetc(file);
        }

        // Extract the score, standard deviation, and sentiment intensity scores
        ungetc(character, file);
        fscanf(file, "%f %f", &(word->score), &(word->SD));
        for (int i = 0; i < 10; i++) {
            fscanf(file, "%d", &(word->SIS_array[i]));
        }

        index++;
    }

    *num_of_words = index;
    fclose(file);
    // close file once everything is done
    
    return words_array;
}

float calculate_score(const struct words *words, const char *sentence, int *num_of_words) {
    // add 1 to act as a buffer
    char lowercase[strlen(sentence) + 1];
    strcpy(lowercase, sentence);

    // convert the sentence to lowercase to take account of the capitalised words
    for (int i = 0; lowercase[i]; i++) 
    {
        lowercase[i] = tolower(lowercase[i]);
    }

    // remove possible punctuation from the sentence
    rm_punctuation(lowercase); 

    float total_score = 0;

    // use tokens so keep track of the words in the sentence and the number of words in each sentence
    char *word = strtok(lowercase, " ");
    int token_count = 0;

    while (word != NULL) 
    {
        token_count++;

        //check each word from the  file being validated with the array of strings extracted in the read_file function
        for (int j = 0; j < *num_of_words; j++) 
        {
            // if there is a match add the score to the total_score
            if (strcmp(words[j].word, word) == 0) 
            {
                total_score += words[j].score;
                break;
            }
                       
        }
        // get the next word
        word = strtok(NULL, " ");
    }

    // calculate the average score
    float average_score = total_score / token_count;
    return average_score;
}

char **read_lines(const char *filename, int *num_lines)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return NULL;
    }

    // count the number of lines in the file
    char character;
    int count = 0;
    while ((character = fgetc(file)) != EOF)
    {
        if (character == '\n')
        {
            count++;
        }
    }
    //reset the file pointer to the beginning of the file to be able to do the following
    rewind(file);

    // allocate memory to eavh individual lines i the array
    char **lines = malloc(sizeof(char *) * (count + 1));

    // read the lines from the file
    for (int i = 0; i < count; i++)
    {
        int len = 0;
        lines[i] = malloc(sizeof(char) * 101);
        int character = fgetc(file);
        
        while (character != EOF && character != '\n')
        {
            lines[i][len++] = character;
            character = fgetc(file);
        }
        lines[i][len] = '\0';
    }
    // set the last element to NULL to mark the end of the array
    lines[count] = NULL;
    fclose(file);
    // set the number of lines
    *num_lines = count;
    return lines;
}

void rm_punctuation(char *str) {
    int len = strlen(str);
    // loop trough the characters in the word and repalce the punctuation with a space
    for (int i = 0; i < len; i++) {
        if (ispunct(str[i])) {
            str[i] = ' '; 
        }
    }
}