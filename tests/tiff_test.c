#include "matrix.h"
#include "tiff.h"

int main(){
    Matrix *a = make_matrix(600, 800);
    fill_matrix(a);
    write_tiff(a);
}