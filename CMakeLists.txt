#CMakeLists Header
cmake_minimum_required (VERSION 2.6)
project (libefsm)


# The version number.
set (LIBEFSM_VERSION_MAJOR 0)
set (LIBEFSM_VERSION_MINOR 1)


# Directory Parameters
set (PROJECT_BUILD_DIR build)


# Build flags
set (LIBNAME efsm)
set (CMAKE_BUILD_TYPE dev)
set (CMAKE_C_FLAGS_DEV "-std=c99")
add_definitions (-Wall -ggdb -g -DFSM_DEBUG)
#add_definitions (-O3)


# add include headers
include_directories (
    /usr/include
    src/libefsm
    src/fsm/fsm_template
)


# add FSM implementation source files
set (EFSM_BASE_SRC src/libefsm/fsm_base.c)
set (FSM_TEMPLATE_SRC src/fsm/fsm_template/fsm_template.c)

# add test source files
set (EXEC_00_SRC src/tests/00_template.c)


# driver libraries
add_library (${LIBNAME}_template STATIC ${EFSM_BASE_SRC} ${FSM_TEMPLATE_SRC})


# FSM implementation demos
add_executable (00_template ${EXEC_00_SRC})
target_link_libraries (00_template ${LIBNAME}_template)


# EOF
