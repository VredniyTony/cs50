#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

string getString();
void sortText(string letters);
string sortTextAlphabetically(string letters, int lengthOfLetters);
int setMaxRepeatedLetters(string letters, int lengthOfLetters);
void printLetters(string letters, int counterOfMax, int lengthOfLetters);

int main(){
    string text = getString();
    sortText(text);
    return 0;
}

string getString(){
    printf("Enter text: ");
    string text = get_string();
    return text;
}

void sortText(string letters){
    int lengthOfLetters = strlen(letters);
    letters = sortTextAlphabetically(letters, lengthOfLetters);
    int counterOfMax = setMaxRepeatedLetters(letters, lengthOfLetters);
    printLetters(letters, counterOfMax, lengthOfLetters);
}

string sortTextAlphabetically(string letters, int lengthOfLetters){
    int counter1 = 0, counter2=0;
    char tmp = 0;
        for (counter1 =0; counter1 < lengthOfLetters; counter1++){
           for (counter2 = 0; counter2 < lengthOfLetters; counter2++){
               if (letters[counter1]<letters[counter2]){
                  tmp = letters[counter2];
                  letters[counter2] = letters[counter1];
                  letters[counter1] = tmp;
                }
            }
        }
    return letters;
}

int setMaxRepeatedLetters(string letters, int lengthOfLetters){
    int counter = 1, counterOfMax = 0, counterOfVeriable = 1;
    for (counter=0; counter<lengthOfLetters; counter++){
        if ((letters[counter]==letters[counter+1]) && ((counter+1)<lengthOfLetters)){
            counterOfVeriable++;
        }else if(counterOfMax<counterOfVeriable){
            counterOfMax=counterOfVeriable;

            counterOfVeriable = 1;
        }else{
            counterOfVeriable = 1;
        }
    }
    return counterOfMax;
}

void printLetters(string letters, int counterOfMax, int lengthOfLetters){
    int counter = 0, counterOfVeriable = 1;
    while (counterOfMax>0){
    do{
        if (!isalpha(letters[counter])){
                counterOfVeriable = 1;
                counter++;
                continue;
            }
        if (letters[counter]==letters[counter+1]){
            counterOfVeriable++;
        }else if (counterOfVeriable == counterOfMax){
            printf("%c - %d;\n", toupper(letters[counter]), counterOfMax);
            counterOfVeriable = 1;
        }else{
            counterOfVeriable = 1;
            }
        counter++;
    }while(counter<lengthOfLetters);
    counter = 0;
    counterOfMax--;
    counterOfVeriable = 1;
    }
}