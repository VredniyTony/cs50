#import <stdio.h>
#import <cs50.h>
#import <string.h>
#include <ctype.h>

string getLetters();
void caesarCipher(string key, string letters);

int main(int argc, string argv[]){
    if (argc != 2){
        printf("Usage: ./caesar k\n");
        return 1;
    }
    string key = argv[1];
    int counter = 0;
    int lengthOfKey = strlen(key);
    do{
        if (!isalpha(key[counter])){
            printf("Usage: ./caesar k\n");
        return 1;
        }
        counter++;
    }while(counter<lengthOfKey);
    string letters = getLetters();
    caesarCipher(key, letters);
    return 0;
}

string getLetters(){
    printf("plaintext: ");
    string letters = get_string();
    return letters;
}

void caesarCipher(string key, string letters){
    int lengthOfLetters = strlen(letters);
    int lengthOfKey = strlen(key);
    int counter = 0, counterKey = 0, tmp = 0, upLetterForBias = 65, lowLetterForBias = 97, formulaNum = 26; 
    printf("ciphertext: ");
    for(counter = 0; counter < lengthOfLetters; counter++){
        if(isupper(key[counterKey])){
            tmp = key[counterKey]-upLetterForBias;
        }else{
            tmp = key[counterKey]-lowLetterForBias;
        }
         if(isupper(letters[counter])){
                letters[counter] = letters[counter] - upLetterForBias;
                letters[counter] = (letters[counter] + tmp) % formulaNum;
                letters[counter] = letters[counter] + upLetterForBias;
                counterKey++;
            }else if(islower(letters[counter])) {
                letters[counter] = letters[counter] - lowLetterForBias;
                letters[counter] = (letters[counter] + tmp) % formulaNum;
                letters[counter] = letters[counter]+lowLetterForBias;
                counterKey++;
            }else{
                letters[counter] = letters[counter];
            }
        if (counterKey==lengthOfKey){
            counterKey=0;
        }
    }

    printf("%s\n", letters);
}