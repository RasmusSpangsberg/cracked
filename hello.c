#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

struct Matrix {
    int rows;
    int cols;
    double* data;
};
typedef struct Matrix Matrix; // TODO idk what this line does, other than make below Matrix* work

// convert row/col to idx
int idx_matrix(int row, int col, int totalCols){
    return row * totalCols + col;
}

Matrix* make_matrix(int n_rows, int n_cols) {
    struct Matrix* matrix = malloc(sizeof(struct Matrix));
    matrix->rows = n_rows;
    matrix->cols = n_cols;
    matrix->data = malloc(sizeof(double) * n_rows * n_cols);

    return matrix;
}

void fill_matrix(Matrix *m){
    for (int i = 0; i < m->rows * m->cols; i++){
        m->data[i] = (double) i;
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
        printf("[%.*f", numDecimals, m->data[i*m->cols]);
        for (int j = 1; j < m->cols; j++){
            int idx = idx_matrix(i, j, m->cols);
            printf(", %.*f", numDecimals, m->data[idx]);
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

/*
int main(){
    Matrix* a = make_matrix(3, 2);
    Matrix* b = make_matrix(2, 4);

    fill_matrix(a);
    print_matrix(a);
    
    printf("\n");
    fill_matrix(b);
    print_matrix(b);

    Matrix* c = mult_matrix(a, b);
    printf("\n");
    print_matrix(c);

    // TODO is this sufficient? How to check?
    free(a->data);
    free(a);
    free(b->data);
    free(b);

    return 0;
}
*/
