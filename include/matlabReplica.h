//
// Created by David on 11/26/2023.
//

#ifndef MATLAB_REPLICA_BACKEND_MATLABREPLICA_H
#define MATLAB_REPLICA_BACKEND_MATLABREPLICA_H

#ifndef _WINDOWS_
    #define _In_
    #define _In_opt_
    #define _Out_
    #define _Out_opt_
#endif

#ifndef byte
    #define byte char
#endif
#ifndef bool
    #define bool byte
    #define true 1
    #define false 0
#endif
#define ushort unsigned short

/**
 * ERRNO Table:
 *
 *    ERROR Adverb  | No. | Description
 *  --------------- | --- | ------------
 *  Success         |  0  | No Errors
 *  Generic         |  1  | Unkown
 *  MemAllocFail    |  2  | Memory allocation failed
 *
 */
typedef enum {
    REPLICA_ERRNO_SUCCESS = 0,
    REPLICA_ERRNO_GENERIC = 1,
    REPLICA_ERRNO_MEMALLOCFAIL = 2,
    REPLICA_ERRNO_INVALID_ARG = 3,
    REPLICA_ERRNO_NULLREFRENCE = 4
} ReplicaErrno;


#endif //MATLAB_REPLICA_BACKEND_MATLABREPLICA_H
