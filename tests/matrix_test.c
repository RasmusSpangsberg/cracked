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

    // TODO is this sufficient? How to check?
    free(a->data);
    free(a);
    free(b->data);
    free(b);

    return 0;
}