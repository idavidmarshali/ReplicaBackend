#include <stdio.h>
#include <stdlib.h>
#include "rMatrix.h"
#include "rMatrixFast.h"

int main() {
    RMatrixHandle A = replica_matrix_create(5, 5, REPLICA_MATRIX_TYPE_INT, REPLICA_MATRIX_FLAG_NORMAL,
                                            REPLICA_MATRIX_FLAG_NORMAL, true);
    RMatrixHandle B = replica_matrix_create(5, 5, REPLICA_MATRIX_TYPE_INT, REPLICA_MATRIX_FLAG_NORMAL, REPLICA_MATRIX_FLAG_NORMAL, true);
    for (ushort i = 0; i < A->columns; i++){
        for (ushort j = 0; j < A->rows; j++){
            replica_internal_matrix_fast_element_set_typed(A, i, j, int, i+j);
            replica_internal_matrix_fast_element_set_typed(B, i, j, int, i*j);
        }
    }

    char* matrixS = replica_matrix_convert_int_string(A);
    printf("%s\n", matrixS);

    printf("%d\n", replica_errno_get());
    free(matrixS);
    replica_matrix_destroy(A);
    replica_matrix_destroy(B);
}
