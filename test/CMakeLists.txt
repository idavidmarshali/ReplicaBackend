

add_compile_options(-mavx)
include_directories(../include)
add_executable(mpOptim optimtest/testOptim.c)
add_executable(mpTest test.c)
if (MP_COMPILE_LIB EQUAL 1)
    target_link_libraries(mpTest LINK_PRIVATE MatlabReplica)
endif ()
