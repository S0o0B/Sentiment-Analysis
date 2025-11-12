#include <stdio.h>
#include <stdlib.h>
#include "readvader.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <vader_lexicon.txt> <validation_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // --- Read lexicon ---
    int num_of_words = 0;
    struct words *words = read_file(argv[1], &num_of_words);
    if (words == NULL || num_of_words == 0)
    {
        fprintf(stderr, "Error: Failed to load VADER lexicon from '%s'\n", argv[1]);
        return EXIT_FAILURE;
    }

    // --- Read validation sentences ---
    int num_lines = 0;
    char **sentences = read_lines(argv[2], &num_lines);
    if (sentences == NULL || num_lines == 0)
    {
        fprintf(stderr, "Error: Failed to load validation sentences from '%s'\n", argv[2]);
        free(words);
        return EXIT_FAILURE;
    }

    // --- Calculate and print sentiment scores ---
    printf("Sentiment Analysis Results:\n");
    printf("============================\n\n");

    for (int i = 0; i < num_lines; i++)
    {
        float score = calculate_score(words, sentences[i], &num_of_words);
        printf("Sentence: %s\nScore: %.2f\n\n", sentences[i], score);
    }

    // --- Free memory ---
    for (int i = 0; i < num_of_words; i++)
    {
        free(words[i].word);
    }
    free(words);

    for (int i = 0; i < num_lines; i++)
    {
        free(sentences[i]);
    }
    free(sentences);

    return EXIT_SUCCESS;
}
