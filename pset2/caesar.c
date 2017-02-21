#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string getLetters();
void caesarCipher(int key, string letters);

int main(int argc, string argv[]){
    if (argc != 2){
        printf("Usage: ./caesar k\n");
        return 1;
    }
    int key = atoi(argv[1]);
    string letters = getLetters();
    caesarCipher(key, letters);
    return 0;
}

string getLetters(){
    printf("plaintext: ");
    string letters = get_string();
    return letters;
}

void caesarCipher(int key, string letters){
    int lengthOFLetters = strlen(letters);
    printf("ciphertext: ");
    int counter = 0;
    for(counter = 0; counter < lengthOFLetters; counter++){
        if (isalpha(letters[counter])){
            if(isupper(letters[counter])){
                letters[counter] = letters[counter] - 65;
                letters[counter] = (letters[counter] + key) % 26;
                letters[counter] = letters[counter] + 65;
            }else{
                letters[counter] = letters[counter] - 97;
                letters[counter] = (letters[counter] + key) % 26;
                letters[counter] = letters[counter]+97;
            }  
        }else{
            letters[counter] = letters[counter];
        }
    }
    printf("%s\n", letters);
}