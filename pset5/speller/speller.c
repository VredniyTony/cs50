#include <ctype.h>
#include <stdio.h>
#include "dictionary.h"
#undef calculate
#undef getrusage

double calculate(const struct rusage *b, const struct rusage *a);

int main(int argc, char *argv[]){
    if (argc != 2 && argc != 3){
        printf("Usage: speller [dictionary] text\n");
        return 1;
    }
    struct rusage before, after;
    char* dictionary = (argc == 3) ? argv[1] : DICTIONARY;
    getrusage(RUSAGE_SELF, &before);
    bool loaded = load(dictionary);
    getrusage(RUSAGE_SELF, &after);
    if (!loaded){
        printf("Could not load %s.\n", dictionary);
        return 1;
    }
    char *text = (argc == 3) ? argv[2] : argv[1];
    FILE *fp = fopen(text, "r");
    if (fp == NULL){
        printf("Could not open %s.\n", text);
        unload();
        return 1;
    }
    printf("\nMISSPELLED WORDS\n\n");
    int index = 0, misspellings = 0, words = 0;
    char word[LENGTH+1];
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp)){
        if (isalpha(c) || (c == '\'' && index > 0)){
            word[index] = c;
            index++;
            if (index > LENGTH){
                while ((c = fgetc(fp)) != EOF && isalpha(c));
                index = 0;
            }
        }else if (isdigit(c)){
            while ((c = fgetc(fp)) != EOF && isalnum(c));
            index = 0;
        }else if (index > 0){
            word[index] = '\0';
            words++;
            getrusage(RUSAGE_SELF, &before);
            bool misspelled = !check(word);
            getrusage(RUSAGE_SELF, &after);
            if (misspelled){
                printf("%s\n", word);
                misspellings++;
            }
            index = 0;
        }
    }
    if (ferror(fp)){
        fclose(fp);
        printf("Error reading %s.\n", text);
        unload();
        return 1;
    }
    fclose(fp);
    getrusage(RUSAGE_SELF, &before);
    unsigned int n = size();
    getrusage(RUSAGE_SELF, &after);
    getrusage(RUSAGE_SELF, &before);
    bool unloaded = unload();
    getrusage(RUSAGE_SELF, &after);
    if (!unloaded){
        printf("Could not unload %s.\n", dictionary);
        return 1;
    }
    printf("\nWORDS MISSPELLED:     %d\n", misspellings);
    printf("WORDS IN DICTIONARY:  %d\n", n);
    printf("WORDS IN TEXT:        %d\n", words);
    return 0;
}

