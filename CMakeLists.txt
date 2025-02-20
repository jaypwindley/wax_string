cmake_minimum_required(VERSION 3.11.1)

project(wax-string VERSION "0.2.0")

set (SRC src)
set (SRCS
  ${SRC}/edit.cpp
  ${SRC}/format.cpp
  ${SRC}/libmain.cpp
  ${SRC}/parse.cpp)

set (LOCAL_CXX_FLAGS "-std=c++20 -O4 -ggdb -fPIC")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LOCAL_CXX_FLAGS}")

configure_file(${SRC}/version.h.in version.h)
include_directories(
  ${PROJECT_BINARY_BIN}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR})

add_library(objs OBJECT ${SRCS})
set_property(TARGET objs PROPERTY POSITION_INDEPENDENT_CODE 1)

add_library(wax-string        SHARED $<TARGET_OBJECTS:objs>)
add_library(wax-string-static STATIC $<TARGET_OBJECTS:objs>)
