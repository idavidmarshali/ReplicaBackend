//
// Created by David on 11/26/2023.
//

#ifndef MATLAB_REPLICA_BACKEND_RMATRIX_H
#define MATLAB_REPLICA_BACKEND_RMATRIX_H
#include "matlabReplica.h"

#define REPLICA_CPU_CACHE_LINE 64 //bytes
#define REPLICA_MATRIX_ALIGNMENT 64 //bytes

enum ReplicaMatrixTypeEnum{
    REPLICA_MATRIX_TYPE_INT    = sizeof(int),
    REPLICA_MATRIX_TYPE_SHORT  = sizeof(short),
    REPLICA_MATRIX_TYPE_FLOAT  = sizeof(float),
    REPLICA_MATRIX_TYPE_DOUBLE = sizeof(double),
    REPLICA_MATRIX_TYPE_CHAR   = sizeof(char)
};

enum ReplicaMatrixFlagEnum {
    REPLICA_MATRIX_FLAG_NORMAL = 0,
    REPLICA_MATRIX_FLAG_LINKED = 1,
    REPLICA_MATRIX_FLAG_Nz     = 2,
};

struct BaseMatrixStruct{
    byte   matFlags;     // 1 byte | Matrix Specific Flags
    byte   elementSize;  // 1 byte |
    byte   opFlags;      // 1 byte | Optimization Specific Flags
    byte   _reserved;     // 1 byte |
    ushort rows;         // 2 bytes
    ushort columns;      // 2 bytes/
};
/*
 * BaseMatrixStruct.matFlags :
 *  These Flags Specify the type and structure
 *  of the underlying matrix.
 *  the flag attribute is 1 byte long and is divided into two 4bit sections.
 *
 * -    Lower 4 bits: the lower four bits of the matFlags specifies the
 *      structure of our matrix:
 *      bits | pos | Means
 *      -----|-----|-----
 *      0000 |  0  | NORMAL Matrix
 *      0001 |  0  | LINKED Matrix
 *      0010 |  1  | N's Matrix (zeros, ones, twos)
 *      0100 |  2  | Row/Column Majority (1 is column major, 0 is row major)
 *      1000 |  3  | EXTENDED (means matrix elements are not of defined dataTypes)
 *
 * -    Higher 4 bits: the higher four bits of matFlags specifies matrix
 *      element dataType:
 *      bits | pos | element type
 *      -----|-----|------
 *      0000 |  0  | NONE           (matrix is extended)
 *      0001 |  0  | char           (1 byte)
 *      0010 |  1  | short          (2 bytes)
 *      0100 |  2  | float          (4 bytes)
 *      0101 |  2  | int            (4 bytes)
 *      1000 |  3  | double         (8 bytes)
 *      1001 |  3  | size_t         (8 bytes)
 *
 */
/*
 * BaseMatrixStruct.opFlags :
 *  These Flags Specify the optimization structure
 *  of the underlying matrix.
 *  the opFlags attribute is 1 byte long and is divided into two 4bit sections.
 *
 * -    Lower 4 bits: the lower four bits of the opFlags specifies the
 *      internal padding of the matrix elements:
 *      bits | pos | Means
 *      -----|-----|-----
 *      0000 |  0  | No Padding
 *      0001 |  0  | 128bit Padding (16 bytes)
 *      0010 |  1  | 256bit padding (32 bytes)
 *      0100 |  2  | 512bit padding (64 bytes)
 *
 * -    Higher 4 bits: N/A
 */

typedef struct BaseMatrixStruct BaseMatrix;
typedef enum ReplicaMatrixTypeEnum ReplicaMatrixTypes;
typedef enum ReplicaMatrixFlagEnum ReplicaMatrixFlags;
typedef BaseMatrix* RMatrixHandle;

/**
 * creates a matrix in memory and returns the handle to the matrix.
 * <br><b>
 * MatrixHandles owner ship is passed to the caller! 
 * </b>
 * @param row 
 * @param column 
 * @param dataType determines the size of matrix elements
 * @param flags effects matrix initialization behaviour
 * @param outCode returned code in case of Error occurrence
 * @return 
 */
#define replica_matrix_calculate_size(usRow, usColumn, dataType) ((sizeof(BaseMatrix) + ((row)*(column)*(dataType))
size_t replica_matrix_calculate_size_aligned(ushort row, ushort column, size_t dataType);


ReplicaErrno replica_errno_get();

RMatrixHandle replica_matrix_create(
        _In_ ushort row,
        _In_ ushort column,
        _In_ ReplicaMatrixTypes dataType,
        _In_ byte matrixFlags,
        _In_ byte optimizationFlags,
        _In_ bool setZero);

//RMatrixHandle replica_matrix_create(_In_ ushort row, _In_ ushort column, _In_ ReplicaMatrixTypes dataType, _In_ byte flags,
//                                    _Out_opt_ ReplicaReturnCode* outCode);

void replica_matrix_destroy(_In_ RMatrixHandle matrix);
char* replica_matrix_convert_int_string(_In_ RMatrixHandle matrix);
//void replica_matrix_transpose(_In_ RMatrixHandle matrixA, _Out_opt_ RMatrixHandle outMatrixB, _Out_opt_ ReplicaReturnCode* outCode);


#endif //MATLAB_REPLICA_BACKEND_RMATRIX_H
