#include "data_loader.h"

int main(){
    char* images_path = "data/t10k-images.idx3-ubyte";
    //char* labels_path = "data/t10k-labels.idx1-ubyte";
    
    data_parser(images_path);
}