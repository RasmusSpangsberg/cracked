#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "tiff.h"
#include "matrix.h"

// TODO: rename?
int bytes2int(unsigned char *buffer, int startIdx){
    return (int)buffer[startIdx+3] | (int)buffer[startIdx+2]<<8 | (int)buffer[startIdx+1]<<16 | (int)buffer[startIdx]<<24;
}

// TODO: metadata_parser??
void data_parser(char *path){
    //unsigned char buffer[16];
    unsigned char buffer[16+28*28];

    FILE *file = fopen(path, "rb");
    fread(buffer, sizeof(buffer), 1, file); // read bytes to our buffer

    // TODO: check magic num
    // parse metadata
    int magicNum  = bytes2int(buffer, 0);
    int numImages = bytes2int(buffer, 4);
    int numRows   = bytes2int(buffer, 8);
    int numCols   = bytes2int(buffer, 12);

    printf("magicNum %d\n", magicNum);
    printf("numImages %d\n", numImages);
    printf("numRows %d\n", numRows);
    printf("numCols %d\n", numCols);

    /*
    unsigned char *img_buffer = (unsigned char*)malloc(numRows * numCols * sizeof(unsigned char));
    //unsigned char img_buffer[28*28*4];
    //uint8_t img_buffer[28*28*4];
    int numItems = 4;
    int asd = fread(img_buffer, sizeof(img_buffer), numItems, file);

    if (asd != numItems){
        printf("fread = %d\n", asd);
        printf("end of file error = %d\n", feof(file));
        printf("file error = %d\n", ferror(file));
        return;
    }
    printf("fread val %d\n", asd);

    printf("%d\n", (uint8_t)img_buffer[33]);

    printf("numRows: %d\n", numRows);

    uint8_t x = (uint8_t) img_buffer[33];
    printf("sizeof(x) = %d\n", sizeof(x));
    int num = sizeof(x) * 8;
    for (int i = 0; i < num; i++)
        printf("%d", (x >> (num - i-1)) & 1);
    */

    // parse image data
    Matrix *m = make_matrix(numRows, numCols);

    for (int i = 0; i < numRows*numCols; i++){
        m->data[i] = (uint8_t) buffer[i+16];
    }

    print_matrix(m);
    write_tiff(m);
    fclose(file);
}