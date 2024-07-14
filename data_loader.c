#include <stdio.h>

// TODO: rename?
int bytes2int(unsigned char *buffer, int startIdx){
    return (int)buffer[startIdx+3] | (int)buffer[startIdx+2]<<8 | (int)buffer[startIdx+1]<<16 | (int)buffer[startIdx]<<24;
}

void png_parser(char *path){
    unsigned char buffer[16];

    FILE *ptr = fopen(path, "rb");
    fread(buffer, sizeof(buffer), 1, ptr); // read bytes to our buffer

    int magicNum  = bytes2int(buffer, 0);
    int numImages = bytes2int(buffer, 4);
    int numRows   = bytes2int(buffer, 8);
    int numCols   = bytes2int(buffer, 12);

    printf("magicNum  %d\n", magicNum);
    printf("numImages %d\n", numImages);
    printf("numRows   %d\n", numRows);
    printf("numCols   %d\n", numCols);

    fclose(ptr);

}

int main(){
    char* images_path = "data/t10k-images.idx3-ubyte";
    char* labels_path = "data/t10k-labels.idx1-ubyte";
    
    png_parser(images_path);
}