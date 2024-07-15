#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hello.c"

// TODO: rename?
int bytes2int(unsigned char *buffer, int startIdx){
    return (int)buffer[startIdx+3] | (int)buffer[startIdx+2]<<8 | (int)buffer[startIdx+1]<<16 | (int)buffer[startIdx]<<24;
}

// TODO: metadata_parser??
void data_parser(char *path){
    unsigned char buffer[16];

    FILE *ptr = fopen(path, "rb");
    fread(buffer, sizeof(buffer), 1, ptr); // read bytes to our buffer

    // TODO: check magic num
    // parse metadata
    int magicNum  = bytes2int(buffer, 0);
    int numImages = bytes2int(buffer, 4);
    int numRows   = bytes2int(buffer, 8);
    int numCols   = bytes2int(buffer, 12);

    unsigned char *img_buffer = (unsigned char*)malloc(numRows * numCols * sizeof(unsigned char));
    fread(img_buffer, sizeof(img_buffer), 1, ptr);

    // parse image data
    Matrix *m = make_matrix(numRows, numCols);
    for (int i = 0; i < numRows*numCols; i++){
        m->data[i] = img_buffer[i];
    }

    print_matrix(m);

    fclose(ptr);
}

int main(){
    char* images_path = "data/t10k-images.idx3-ubyte";
    char* labels_path = "data/t10k-labels.idx1-ubyte";
    
    data_parser(images_path);
}