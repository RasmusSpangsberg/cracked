#include <stdint.h>

#define DATA_TYPE int

typedef struct Matrix {
    int rows;
    int cols;
    DATA_TYPE* data;
} Matrix;