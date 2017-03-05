#include <stdio.h>
#include <cs50.h>

int main(){
    printf("Minutes: ");
    int minutes = get_int();
    int botl = 12*minutes;    
    printf("Bottles: %d\n",botl);
    return 0;
}

