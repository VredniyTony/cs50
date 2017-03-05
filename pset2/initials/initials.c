#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

string getName();
void getInitials(string personName);

int main(){
    string personName = getName();
    getInitials(personName);
    return 0;
}

string getName(){
    string personName = get_string();
    return personName;
}

void getInitials(string personName){
    int lengthOfString = strlen(personName);
    int counterPersonName = 0;
    do{ 
    do{
    if (isalpha(personName[counterPersonName])){
            printf("%c", toupper(personName[counterPersonName]));
        }
        counterPersonName++;
    }while(!isalpha(personName[counterPersonName-1])&&(counterPersonName < lengthOfString));
    while(isalpha(personName[counterPersonName])&&(counterPersonName < lengthOfString)){
        counterPersonName++;
    }
    }while(counterPersonName < lengthOfString);
    printf("\n");
}