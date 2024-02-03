#include <immintrin.h>
#include "rMatrix.h"
#include "rMatrixFast.h"
#include <math.h>
#include <omp.h>
#include <memory.h>


/**
 * if C is not NULL:
 *  C = A.+B
 * else:
e *  A = A.+B
 * @param matrixA
 * @param matrixB
 * @param matrixC
 */

/*
 * [REGION] Element Wise Operations
 */
void replica_matrix_fast_elemental_add_int(
        _In_ RMatrixHandle matrixA,
        _In_ RMatrixHandle matrixB,
        _Out_opt_ RMatrixHandle outMatrixC){

    RMatrixHandle outMatrix = (RMatrixHandle)((outMatrixC == NULL) * (size_t)matrixA + (size_t)(outMatrixC));
#pragma omp for
    for (ushort i = 0; i < matrixA->columns; i++){
        for (ushort j = 0; j < matrixA->rows; j++){
            register int res = replica_matrix_fast_element_get_int(matrixA, i, j) + replica_matrix_fast_element_get_int(matrixB, i, j);
            replica_internal_matrix_fast_element_set_typed(outMatrixC, i, j, int, res);
        }
    }
}

void replica_matrix_fast_elemental_mult_int(
        _In_ RMatrixHandle matrixA,
        _In_ RMatrixHandle matrixB,
        _Out_opt_ RMatrixHandle outMatrixC){

    RMatrixHandle outMatrix = (RMatrixHandle)((outMatrixC == NULL) * (size_t)matrixA + (size_t)(outMatrixC));
#pragma omp for
    for (ushort i = 0; i < matrixA->columns; i++){
        for (ushort j = 0; j < matrixA->rows; j++){
            register int res = replica_matrix_fast_element_get_int(matrixA, i, j) * replica_matrix_fast_element_get_int(matrixB, i, j);
            replica_internal_matrix_fast_element_set_typed(outMatrixC, i, j, int, res);
        }
    }
}

void replica_matrix_fast_elemental_div_int(
        _In_ RMatrixHandle matrixA,
        _In_ RMatrixHandle matrixB,
        _Out_opt_ RMatrixHandle outMatrixC){

    RMatrixHandle outMatrix = (RMatrixHandle)((outMatrixC == NULL) * (size_t)matrixA + (size_t)(outMatrixC));
#pragma omp for
    for (ushort i = 0; i < matrixA->columns; i++){
        for (ushort j = 0; j < matrixA->rows; j++){
            register int res = replica_matrix_fast_element_get_int(matrixA, i, j) / replica_matrix_fast_element_get_int(matrixB, i, j);
            replica_internal_matrix_fast_element_set_typed(outMatrixC, i, j, int, res);
        }
    }
}

void replica_matrix_fast_elemental_sub_int(
        _In_ RMatrixHandle matrixA,
        _In_ RMatrixHandle matrixB,
        _Out_opt_ RMatrixHandle outMatrixC){

    RMatrixHandle outMatrix = (RMatrixHandle)((outMatrixC == NULL) * (size_t)matrixA + (size_t)(outMatrixC));
#pragma omp for
    for (ushort i = 0; i < matrixA->columns; i++){
        for (ushort j = 0; j < matrixA->rows; j++){
            register int res = replica_matrix_fast_element_get_int(matrixA, i, j) - replica_matrix_fast_element_get_int(matrixB, i, j);
            replica_internal_matrix_fast_element_set_typed(outMatrixC, i, j, int, res);
        }
    }
}

void replica_matrix_fast_elemental_pow_int(
        _In_ RMatrixHandle matrixA,
        _In_ RMatrixHandle matrixB,
        _Out_opt_ RMatrixHandle outMatrixC){

    RMatrixHandle outMatrix = (RMatrixHandle)((outMatrixC == NULL) * (size_t)matrixA + (size_t)(outMatrixC));
#pragma omp for
    for (ushort i = 0; i < matrixA->columns; i++){
        for (ushort j = 0; j < matrixA->rows; j++){
            register int res = (int) pow(replica_matrix_fast_element_get_int(matrixA, i, j),
                                   replica_matrix_fast_element_get_int(matrixB, i, j));
            replica_internal_matrix_fast_element_set_typed(outMatrixC, i, j, int, res);
        }
    }
}
/*
 * [END REGION] Element Wise Operations
 */


RMatrixHandle replica_matrix_fast_transpose(_In_ RMatrixHandle matrix){
    RMatrixHandle outMatrix = replica_matrix_create(matrix->columns, matrix->rows, matrix->elementSize, matrix->matFlags, matrix->opFlags, true);
    if (outMatrix == NULL) return outMatrix;
#pragma omp for
    for (ushort i = 0; i < matrix->rows; i++){
        for (ushort j = 0; j < matrix->columns; j++){
            switch (matrix->elementSize) {
                case 0b0001:
                    replica_internal_matrix_fast_element_set_typed(outMatrix, j, i, char,
                                                                   replica_matrix_fast_element_get_char(matrix, i, j));
                    break;
                case 0b0010:
                    replica_internal_matrix_fast_element_set_typed(outMatrix, j, i, short,
                                                                   replica_matrix_fast_element_get_short(matrix, i, j));
                    break;
                case 0b0100:
                    replica_internal_matrix_fast_element_set_typed(outMatrix, j, i, float,
                                                                   replica_matrix_fast_element_get_float(matrix, i, j));
                    break;
                case 0b0101:
                    replica_internal_matrix_fast_element_set_typed(outMatrix, j, i, int,
                                                                   replica_matrix_fast_element_get_int(matrix, i, j));
                    break;
                case 0b1000:
                    replica_internal_matrix_fast_element_set_typed(outMatrix, j, i, double ,
                                                                   replica_matrix_fast_element_get_double(matrix, i, j));
                    break;
                case 0b1001:
                    replica_internal_matrix_fast_element_set_typed(outMatrix, j, i, size_t,
                                                                   replica_matrix_fast_element_get_size_t(matrix, i, j));
                    break;
                default:
                    memcpy(replica_internal_matrix_fast_element_get_pointer_sized(outMatrix, i, j, matrix->elementSize),
                           replica_internal_matrix_fast_element_get_pointer_sized(matrix, j, i, matrix->elementSize),
                           matrix->elementSize);
            }
        }
    }
    return outMatrix;
}
