#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main(){
    Matrix *a = make_matrix(5, 5);
    Matrix *b = make_matrix(2, 4);

    fill_matrix(a);
    print_matrix(a);
    printf("\n");

    Matrix *output = convolution(a);
    print_matrix(output);


    /*
    fill_matrix(a);
    print_matrix(a);
    
    printf("\n");
    fill_matrix(b);
    print_matrix(b);

    Matrix* c = mult_matrix(a, b);
    printf("\n");
    print_matrix(c);
    */

    // TODO is this sufficient? How to check?
    free(a->data);
    free(a);
    free(b->data);
    free(b);

    return 0;
}