cmake_minimum_required (VERSION 3.16)

project(test)

set(EXEC world)
set(SRCS hello.c)

add_executable(${EXEC} ${SRCS})
