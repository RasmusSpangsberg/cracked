#include <stdint.h>

#define DATA_TYPE int

typedef struct Matrix {
    int rows;
    int cols;
    DATA_TYPE* data;
} Matrix;

Matrix* make_matrix(int n_rows, int n_cols);
void fill_matrix(Matrix *m);
void fill_zero_matrix(Matrix *m);
void print_matrix(Matrix *m);
Matrix* mult_matrix(Matrix *a, Matrix *b);
Matrix* zero_padding(Matrix *m);
int convolve(Matrix *input, Matrix *output, Matrix *kernel, int i, int j);
Matrix* convolution(Matrix *input);