#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "matrix.h"

#define DATA_TYPE uint8_t

/*
struct Matrix {
    int rows;
    int cols;
    DATA_TYPE* data;
};
typedef struct Matrix Matrix; // TODO idk what this line does, other than make below Matrix* work
*/

// convert row/col to idx
int idx_matrix(int row, int col, int totalCols){
    return row * totalCols + col;
}

Matrix* make_matrix(int n_rows, int n_cols) {
    struct Matrix* matrix = malloc(sizeof(struct Matrix));
    matrix->rows = n_rows;
    matrix->cols = n_cols;
    matrix->data = malloc(sizeof(DATA_TYPE) * n_rows * n_cols);

    return matrix;
}

void fill_matrix(Matrix *m){
    for (int i = 0; i < m->rows * m->cols; i++){
        m->data[i] = (DATA_TYPE) i;
    }
}

void fill_zero_matrix(Matrix *m){
    for (int i = 0; i < m->rows * m->cols; i++){
        m->data[i] = 0;
    }
}

void print_matrix(Matrix *m){
    int numDecimals = 1;
    for (int i = 0; i < m->rows; i++){
        //printf("[%.*f", numDecimals, m->data[i*m->cols]);
        printf("[");
            if (m->data[i*m->cols] < 100)
                printf(" ");
            if (m->data[i*m->cols] < 10)
                printf(" ");
        printf("%d", m->data[i*m->cols]);
        for (int j = 1; j < m->cols; j++){
            int idx = idx_matrix(i, j, m->cols);
            //printf(", %.*f", numDecimals, m->data[idx]);
            printf(", ");
            if (m->data[idx] < 100)
                printf(" ");
            if (m->data[idx] < 10)
                printf(" ");
            printf("%d", m->data[idx]);
        }
        printf("]\n");
    }
}

void print_idx_matrix(int i, int j, Matrix* m){
    int numDecimals = 1;
    int idx = idx_matrix(i, j, m->cols);
    printf("%.*f\n", numDecimals, m->data[idx]);
}

Matrix* mult_matrix(Matrix *a, Matrix *b){
    assert(a->cols == b->rows);
    Matrix* m = make_matrix(a->rows, b->cols);
    fill_zero_matrix(m);

    for (int k = 0; k < a->rows; k++){
        for (int i = 0; i < b->cols; i++){
            for (int j = 0; j < b->rows; j++){
                int idx_a = idx_matrix(k, j, a->cols);
                int idx_b = idx_matrix(j, i, b->cols);
                int idx_m = idx_matrix(k, i, m->cols);

                m->data[idx_m] += a->data[idx_a] * b->data[idx_b];
            }
        }
    }

    return m;
}


Matrix* zero_padding(Matrix *m){
    Matrix *zero_padded = make_matrix(m->rows+2, m->cols+2);
    fill_zero_matrix(zero_padded);

    for (int i = 0; i < m->rows; i++){
        for (int j = 0; j < m->cols; j++){
            int from_idx = idx_matrix(i, j, m->cols);
            int to_idx = idx_matrix(i+1, j+1, m->cols+2);
            zero_padded->data[to_idx] = m->data[from_idx];
        }
    }

    return zero_padded;

}

void convolve(Matrix *input, Matrix *output, Matrix *kernel, int i, int j){
    assert(kernel->rows == kernel->cols);
    int size = kernel->rows;
    int kernel_stretch = (size - 1) / 2;
    int outputVal = 0;

    int kernel_idx = 0;
    for (int k = -kernel_stretch; k <= kernel_stretch; k++){
        for (int l = -kernel_stretch; l <= kernel_stretch; l++){
            int input_idx = idx_matrix(i+k, j+l, input->cols);
            outputVal += input->data[input_idx] * kernel->data[kernel_idx];
            kernel_idx++;
        }
    }
}

Matrix convolution(Matrix *input){
    int size = 3;
    Matrix *kernel = make_matrix(size, size);
    fill_matrix(kernel);

    Matrix *output = make_matrix(input->rows, input->cols);
    input = zero_padding(input);

    for (int i = 1; i < input->rows-1; i++){
        for (int j = 1; j < input->cols-1; j++){
            convolve(input, output, kernel, i, j);
        }
    }
}

int main(){
    Matrix* a = make_matrix(5, 5);
    Matrix* b = make_matrix(2, 4);

    fill_matrix(a);
    print_matrix(a);
    printf("\n");

    convolution(a);


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
