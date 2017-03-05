#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char* argv[]){
    if (argc != 4){
        printf("Usage: resize factor infile outfile\n");
        return 1;
    }
    char* infile = argv[2];
    char* outfile = argv[3];
    double factor = atoi(argv[1]);
    if (factor < 0.0 || factor > 100.0){
        printf("Factor must be in range 0..100!\n");
        return 1;
    }
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL){
        printf("Could not open %s.\n", infile);
        return 2;
    }
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL){
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    BITMAPFILEHEADER bf, bf_r;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf_r = bf;
    BITMAPINFOHEADER bi, bi_r;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi_r = bi;
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || bi.biBitCount != 24 || bi.biCompression != 0){
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    bi_r.biWidth  = bi.biWidth * factor;
    bi_r.biHeight = bi.biHeight * factor;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) %4) % 4;
    int res_padding = (4 - (bi_r.biWidth * sizeof(RGBTRIPLE)) %4) % 4;
    bi_r.biSizeImage = (bi_r.biWidth * sizeof(RGBTRIPLE) + res_padding) * abs(bi_r.biHeight);
    bf_r.bfSize = bf.bfSize - bi.biSizeImage + bi_r.biSizeImage;
    fwrite(&bf_r, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi_r, sizeof(BITMAPINFOHEADER), 1, outptr);
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++){
        for (int j = 0; j < factor; j++){  
            for (int k = 0; k < bi.biWidth; k++){
                RGBTRIPLE triple;
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                for (int l = 0; l < factor; l++)
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);    
            }
            for (int l = 0; l < res_padding; l++)
                fputc(0x00, outptr);
            if (j < factor - 1.0)
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
        }
        fseek(inptr, padding, SEEK_CUR);
    }
    fclose(inptr);
    fclose(outptr);
    return 0;
}