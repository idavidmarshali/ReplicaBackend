cmake_minimum_required(VERSION 3.21)
project(matlab_replica_backend C)
set(CMAKE_C_STANDARD 99)

set(AVX_FLAGS -mavx -mavx512f -mavx512vl -mavx512er)

set(MP_COMPILE_LIB 1)
set(MP_DEBUG_MODE 1)
set(LIBRARY_SOURCE_DIR src)

if (MP_COMPILE_LIB EQUAL 1)
    FILE(GLOB LIBRARY_SOURCE_FILES ${LIBRARY_SOURCE_DIR}/*.c)
    add_compile_options(-march=native ${AVX_FLAGS})
    include_directories(include)
    add_library(MatlabReplica STATIC ${LIBRARY_SOURCE_FILES})
endif ()

if (MP_DEBUG_MODE EQUAL 1)
    add_subdirectory(test)
endif ()
