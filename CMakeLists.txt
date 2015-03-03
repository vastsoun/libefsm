#CMakeLists Header
cmake_minimum_required (VERSION 2.6)
project (libefsm)


# The version number.
set (LIBEFSM_VERSION_MAJOR 0)
set (LIBEFSM_VERSION_MINOR 1)


# Directory Parameters
set (PROJECT_ROOT_DIR ".")
set (PROJECT_BUILD_DIR "${PROJECT_ROOT_DIR}/build")


# Build flags
set (LIBNAME efsm)
set (CMAKE_BUILD_TYPE dev)
set (CMAKE_C_FLAGS_DEV "-std=c99")
add_definitions (-Wall -ggdb -g -DFSM_FPM_DEBUG)
#add_definitions (-O3)

# add include headers
include_directories (/usr/include)
include_directories (${PROJECT_ROOT_DIR}/src/include)
include_directories (${PROJECT_ROOT_DIR}/src)


# add source files
set (LIB_SRC ${PROJECT_ROOT_DIR}/src/fsm_dsp402_fpm.c)
set (EXEC_00_SRC ${PROJECT_ROOT_DIR}/src/tests/00_fsm_fpm.c)


# driver libraries
add_library (${LIBNAME} STATIC ${PROJECT_ROOT_DIR}/src/fsm_dsp402_fpm.c)


# FSM implementation demos
add_executable (00_fsm_fpm ${EXEC_00_SRC})
target_link_libraries (00_fsm_fpm ${LIBNAME})


# EOF
