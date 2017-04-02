#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include "dictionary.h"

#define DICTIONARY "/home/cs50/pset5/dictionaries/large"

double calculate(const struct rusage* b, const struct rusage* a);
bool checkArgc(int argc);
double timeLoad(struct rusage before,struct rusage after, char* dictionary);
bool checkFile(FILE* fp, char*text);
double spellCheck(FILE* fp, struct rusage before,struct rusage after);
double timeSize(struct rusage before,struct rusage after);
double timeUnload(struct rusage before,struct rusage after, char* dictionary);
void print(double ti_load,double ti_check, double ti_size, double ti_unload);

int main(int argc, char* argv[])
{
    if (checkArgc(argc) == false){
        return 0;
    }

    struct rusage before, after;

    double ti_load = 0.0, ti_check = 0.0, ti_size = 0.0, ti_unload = 0.0;
    char* dictionary = (argc == 3) ? argv[1] : DICTIONARY;

    ti_load = timeLoad(before, after, dictionary);

    // try to open text
    char* text = (argc == 3) ? argv[2] : argv[1];
    FILE* fp = fopen(text, "r");
    if (checkFile(fp, text)==false){
        return 0;
    }

    ti_check = spellCheck(fp,before, after);
    fclose(fp);
    ti_size = timeSize(before, after);
    ti_unload = timeUnload(before, after, dictionary);

    print(ti_load, ti_check, ti_size, ti_unload);
    
    return 0;
}

/**
 * Returns number of seconds between b and a.
 */
double calculate(const struct rusage* b, const struct rusage* a)
{
    return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
    (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
    ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
    (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec))) / 1000000.0);
}

bool checkArgc(int argc){
        if (argc == 3) {
            return true;
        } else {
            printf("Usage: speller [dictionary] text\n");
            return false;
        }
}

double timeLoad(struct rusage before,struct rusage after, char* dictionary){
    double ti_load;
    getrusage(RUSAGE_SELF, &before);
    bool loaded = load(dictionary);
    getrusage(RUSAGE_SELF, &after);

    // abort if dictionary not loaded
    if (!loaded)
    {
        printf("Could not load %s.\n", dictionary);
        exit(0);
    }

    // calculate time to load dictionary
    ti_load = calculate(&before, &after);
    return ti_load;
}

bool checkFile (FILE* fp, char*text){
        if (fp == NULL){
            printf("Could not open %s.\n", text);
            return false;
        } else {
            return true;
        }
}

double spellCheck(FILE* fp, struct rusage before,struct rusage after){
    double ti_check = 0.0;
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
            ti_check += calculate(&before, &after); 
            
            if (misspelled){
                misspellings++;
            }
            index = 0;
        }
    }
        printf("WORDS MISSPELLED:     %d\n", misspellings);
        printf("WORDS IN TEXT:        %d\n", words);
        return ti_check;
}

double timeSize(struct rusage before,struct rusage after){
    double ti_size;
    getrusage(RUSAGE_SELF, &before);
    unsigned int n = size();
    getrusage(RUSAGE_SELF, &after);
    ti_size = calculate(&before, &after);
    printf("WORDS IN DICTIONARY:  %d\n", n);
    return ti_size;
}

double timeUnload(struct rusage before,struct rusage after, char* dictionary){
    double ti_unload;
    getrusage(RUSAGE_SELF, &before);
    bool unloaded = unload();
    getrusage(RUSAGE_SELF, &after);

    if (!unloaded){
        printf("Could not unload %s.\n", dictionary);
        exit(0);
    }
    
    ti_unload = calculate(&before, &after);
    return ti_unload;
}

void print(double ti_load,double ti_check, double ti_size, double ti_unload){
     printf("TIME IN load:         %.2f\n", ti_load);
    printf("TIME IN check:        %.2f\n", ti_check);
    printf("TIME IN size:         %.2f\n", ti_size);
    printf("TIME IN unload:       %.2f\n", ti_unload);
    printf("TIME IN TOTAL:        %.2f\n\n", ti_load + ti_check + ti_size + ti_unload);
}