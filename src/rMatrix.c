#include <stdlib.h>
#include <memory.h>
#include <immintrin.h>
#include <string.h>
#include "rMatrix.h"
#include "rMatrixFast.h"

/*
 * STYLE GUIDELINES:
 *  1. all variables, function Arguments, ... must be prefixed like win32api docs
 *  2. functions must be defined in CamelCase Order.
 *  3. Functions Error Code must be returned using a
 */

// TODO:
//      | General Matrix Methods |
//      0. Matrix Creation and Disposal     [x]
//      1. Matrix Element Wise Operations   [x]
//      2. Matrix General Multiplication    [ ]
//      3. Matrix Transposition             [ ]
//      4. Matrix Determinant Calculation   [ ]
//      5. Matrix Inverse                   [ ]
//      6. Matrix PInverse                  [ ]
//      7. Matrix Duplication               [ ]

// TODO:
//      | Optimization, Logic and Data Structure|
//      1. Implement Linked Matrix Struct           [ ]
//      2. Implement Fast 64Byte Matrix Copy        [ ]
//      3. Implement Row/Column Majority            [ ]
//      4. Matrix Dynamic Padding                   [ ]
//      5. Extended Matrix Creation and operation   [ ]
//      6. Errorno Implementation                   [ ]


/*  DT - MT
 * 0000-0000 |   INT  | NORMAL |
 * 0000-0001 |   INT  | LINKED |
 * 0000-0010 |   INT  |  N's   |
 * 0000-0100 |   INT  |  ROW/COLUMN MAJOR   |
 * 0000-1000 |   INT  |  VARIABLE LENGTH   |
 * 0001-0000 |  FLOAT | NORMAL |
 * 0010-0000 |  SHORT | NORMAL |
 * 0100-0000 | DOUBLE | NORMAL |
 * 1000-0000 |  CHAR  | NORMAL |
 */

static volatile ReplicaErrno _errorNo = REPLICA_ERRNO_SUCCESS;

static inline void replica_internal_errno_set(ReplicaErrno val){
    _errorNo = val;
}

static inline RMatrixHandle replica_internal_matrix_allocate(size_t matrixSize){
    return _mm_malloc(matrixSize, 64);
}


ReplicaErrno replica_errno_get(){
    return _errorNo;
}

size_t replica_matrix_calculate_size_aligned(ushort row, ushort column, size_t dataType){
    register size_t raw_size = sizeof(BaseMatrix) + (row*column*dataType);
    return (raw_size%REPLICA_MATRIX_ALIGNMENT) + raw_size;
}

RMatrixHandle replica_matrix_create(
        _In_ ushort row,
        _In_ ushort column,
        _In_ ReplicaMatrixTypes dataType,
        _In_ byte matrixFlags,
        _In_ byte optimizationFlags,
        _In_ bool setZero){

    register size_t matrixAllocationSize = replica_matrix_calculate_size_aligned(row, column, dataType);

    // LINKED MATRIX Implementation
    RMatrixHandle hMatrix = replica_internal_matrix_allocate(matrixAllocationSize);
    if (hMatrix == NULL){
        replica_internal_errno_set(REPLICA_ERRNO_MEMALLOCFAIL);
        return NULL;
    }
    hMatrix->rows        = row;
    hMatrix->columns     = column;
    hMatrix->elementSize = dataType;
    hMatrix->matFlags    = matrixFlags;
    hMatrix->opFlags     = optimizationFlags;

    if (setZero) memset(hMatrix+1, 0, matrixAllocationSize-sizeof(*hMatrix));

    return hMatrix;
}

/*
 *
 */

char* replica_matrix_convert_int_string(RMatrixHandle matrix){
    char* res = calloc(1024, sizeof(char));
    unsigned int curIdx = 0;
    for (ushort i = 0; i < matrix->columns; i++){
        for (ushort j = 0; j < matrix->rows; j++){
            char* curentConverted = itoa(replica_matrix_fast_element_get_int(matrix, i, j), res+curIdx, 10);
            curIdx += strlen(curentConverted)+1;
            res[curIdx-1] = ' ';
        }
        res[curIdx] = '\n';
        curIdx++;
    }
    return res;
}

inline void replica_matrix_destroy(_In_ RMatrixHandle matrix) {
    _mm_free(matrix);
}
