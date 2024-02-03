//
// Created by David on 12/1/2023.
//

#ifndef MATLAB_REPLICA_BACKEND_RMATRIXFAST_H
#define MATLAB_REPLICA_BACKEND_RMATRIXFAST_H
#include "rMatrix.h"


void replica_matrix_fast_elemental_add_int(_In_ RMatrixHandle matrixA,
                                           _In_ RMatrixHandle matrixB,
                                           _Out_opt_ RMatrixHandle outMatrixC);
void replica_matrix_fast_elemental_mult_int(_In_ RMatrixHandle matrixA,
                                           _In_ RMatrixHandle matrixB,
                                           _Out_opt_ RMatrixHandle outMatrixC);
void replica_matrix_fast_elemental_div_int(_In_ RMatrixHandle matrixA,
                                           _In_ RMatrixHandle matrixB,
                                           _Out_opt_ RMatrixHandle outMatrixC);
void replica_matrix_fast_elemental_sub_int(_In_ RMatrixHandle matrixA,
                                           _In_ RMatrixHandle matrixB,
                                           _Out_opt_ RMatrixHandle outMatrixC);
void replica_matrix_fast_elemental_pow_int(_In_ RMatrixHandle matrixA,
                                           _In_ RMatrixHandle matrixB,
                                           _Out_opt_ RMatrixHandle outMatrixC);

/**
 * gets matrix element of <b>type</b>.<br>
 * <b>NOTE</b>: the matrix indexing starts from 1 and not 0.
 * so matrix[0,0] will result in undefined behaviour!
 * @param pMatrix a RMatrixHandle
 * @param usRow element row position
 * @param usColumn element column position
 * @param type element data type
 */

#define replica_internal_matrix_fast_element_get_pointer_sized(pMatrix, usRow, usColumn, size) (((void*)((pMatrix)+1)) + ((pMatrix)->columns*(usRow) + (usColumn))*(size))
#define replica_internal_matrix_fast_element_get_pointer_typed(pMatrix, usRow, usColumn, type) (((type*)((pMatrix)+1)) + ((pMatrix)->columns*(usRow) + (usColumn)))
#define replica_internal_matrix_fast_element_set_typed(pMatrix, usRow, usColumn, type, tValue) *replica_internal_matrix_fast_element_get_pointer_typed(pMatrix, usRow, usColumn, type) = (tValue)


#define replica_matrix_fast_element_get_char(pMatrix, usRow, usColumn) *replica_internal_matrix_fast_element_get_pointer_typed((pMatrix), (usRow), (usColumn), char)
#define replica_matrix_fast_element_get_short(pMatrix, usRow, usColumn) *replica_internal_matrix_fast_element_get_pointer_typed((pMatrix), (usRow), (usColumn), short)
#define replica_matrix_fast_element_get_float(pMatrix, usRow, usColumn) *replica_internal_matrix_fast_element_get_pointer_typed((pMatrix), (usRow), (usColumn), float)
#define replica_matrix_fast_element_get_int(pMatrix, usRow, usColumn) *replica_internal_matrix_fast_element_get_pointer_typed((pMatrix), (usRow), (usColumn), int)
#define replica_matrix_fast_element_get_double(pMatrix, usRow, usColumn) *replica_internal_matrix_fast_element_get_pointer_typed((pMatrix), (usRow), (usColumn), double)
#define replica_matrix_fast_element_get_size_t(pMatrix, usRow, usColumn) *replica_internal_matrix_fast_element_get_pointer_typed((pMatrix), (usRow), (usColumn), size_t)


// you jump through columns by multiplying the count of columns by the rows
//
//#define replica_matrix_element_fast_get_float(pMatrix, usRow, usColumn)  replica_matrix_element_fast_get_typed(pMatrix, usRow,usColumn, float)
//#define replica_matrix_element_fast_get_double(pMatrix, usRow, usColumn) replica_matrix_element_fast_get_typed(pMatrix, usRow,usColumn, double)
//#define replica_matrix_element_fast_get_int(pMatrix, usRow, usColumn)    replica_matrix_element_fast_get_typed(pMatrix, usRow, usColumn, int)
//#define replica_matrix_element_fast_get_short(pMatrix, usRow, usColumn)  replica_matrix_element_fast_get_typed(pMatrix, usRow,usColumn, short)
//#define replica_matrix_element_fast_get_char(pMatrix, usRow, usColumn)   replica_matrix_element_fast_get_typed(pMatrix, usRow,usColumn, char)
//
//#define replica_matrix_element_fast_set_double(pMatrix, usRow, usColumn, fdValue) replica_matrix_element_fast_get_typed(pMatrix, usRow, usColumn, double) = (double) fdValue
//#define replica_matrix_element_fast_set_float(pMatrix, usRow, usColumn, fValue)   replica_matrix_element_fast_get_typed(pMatrix, usRow, usColumn, float)  = (float) fValue
//#define replica_matrix_element_fast_set_int(pMatrix, usRow, usColumn, dValue)     replica_matrix_element_fast_get_typed(pMatrix, usRow, usColumn, int)    = (int) dValue
//#define replica_matrix_element_fast_set_short(pMatrix, usRow, usColumn, sValue)   replica_matrix_element_fast_get_typed(pMatrix, usRow, usColumn, short)  = (short) sValue
//#define replica_matrix_element_fast_set_char(pMatrix, usRow, usColumn, cValue)    replica_matrix_element_fast_get_typed(pMatrix, usRow, usColumn, char)   = (char) cValue
//
//#define replica_matrix_row_fast_get_int(pMatrix, usRow) replica_matrix_element_fast_get_pointer_typed(pMatrix, usRow, 1, int)
//#define replica_matrix_row_fast_get_float(pMatrix, usRow) replica_matrix_element_fast_get_pointer_typed(pMatrix, usRow, 1, float)
//#define replica_matrix_row_fast_get_double(pMatrix, usRow) replica_matrix_element_fast_get_pointer_typed(pMatrix, usRow, 1, double)
//#define replica_matrix_row_fast_get_short(pMatrix, usRow) replica_matrix_element_fast_get_pointer_typed(pMatrix, usRow, 1, short)
//#define replica_matrix_row_fast_get_char(pMatrix, usRow) replica_matrix_element_fast_get_pointer_typed(pMatrix, usRow, 1, char)
//
//#define replica_matrix_column_fast_get_int(pMatrix, usColumn)    NULL
//#define replica_matrix_column_fast_get_float(pMatrix, usColumn)  NULL
//#define replica_matrix_column_fast_get_double(pMatrix, usColumn) NULL
//#define replica_matrix_column_fast_get_short(pMatrix, usColumn)  NULL
//#define replica_matrix_column_fast_get_char(pMatrix, usColumn)   NULL


#endif // HEADER GUARD