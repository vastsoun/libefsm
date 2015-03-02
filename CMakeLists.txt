# CMakeList Project File
cmake_minimum_required(VERSION 2.6)

#Name of the Project
PROJECT(fsm-test)

# Build configuration
SET(CMAKE_C_FLAGS "-std=c99")
#SET(LIBNAME fsm)  #Name of the library that will be generated

ADD_DEFINITIONS(-Wall -ggdb -g)

#INCLUDE_DIRECTORIES(
#/usr/local/include
#./src/include
#)

#LINK_DIRECTORIES(/usr/lib /usr/local/lib)

SET(SRCS

  #TODO
  #src/
  #src/tests/

)


#ADD_LIBRARY(${LIBNAME} STATIC ${SRCS})
#TARGET_LINK_LIBRARIES(${LIBNAME} m)


# FSM implementation demos
ADD_EXECUTABLE(00_fsm_fp ${SRCS} src/tests/00_fsm_fp.c)
TARGET_LINK_LIBRARIES(00_fsm_fp m)



# Primary Application
#ADD_EXECUTABLE(${EXEC_NAME} ${SRCS} src/main.cpp)
#TARGET_LINK_LIBRARIES(${EXEC_NAME} m  cpc pthread z bluetooth)

