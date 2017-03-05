#include <stdio.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(void)
{   
    FILE* file = fopen("card.raw", "r");
    if (file == NULL){
        fclose(file); 
        fprintf(stderr, "unable to recover file from card.raw \n");
        return 1;
    }
    int counter = 0; 
    BYTE buffer[512];
    char lname[10]; 
    FILE* temp = NULL; 
    while (!feof(file)){
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1)){
            if (temp != NULL){
                fclose(temp);
            }
            sprintf(lname, "%03d.jpg", counter);
            temp = fopen(lname, "w");
            counter++;
            fwrite(buffer, sizeof(buffer), 1, temp);
        }
        else if (counter > 0){
            fwrite(buffer, sizeof(buffer), 1, temp);            
        }
        fread(buffer, sizeof(buffer), 1, file);
    }
    fclose(file);
    return 0;
}