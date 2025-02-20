cmake_minimum_required(VERSION 3.11.1)

project(wax-string-tests)

add_subdirectory(googletest)

set (SRC_DIR ${CMAKE_SOURCE_DIR}/../src)
set (LIB_DIR ${CMAKE_SOURCE_DIR}/../${BUILD_DIR})

if (NOT EXISTS ${LIB_DIR})
  message("Build with 'make test' from top level makefile")
  return()
endif()

set (TEST_SRCS
  test_compose.cpp
  test_cstr.cpp
  test_edit.cpp
  test_format.cpp
  test_hash.cpp
  test_parse.cpp
  )
set (LOCAL_CXX_FLAGS "-std=c++20 -ggdb -fPIC")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LOCAL_CXX_FLAGS}")

include_directories(
  ${SRC_DIR}
  ${CMAKE_SOURCE_DIR}/googletest/googletest/include
  )

add_executable(unit-tests ${TEST_SRCS})
target_link_directories(unit-tests PUBLIC ${CMAKE_SOURCE_DIR}/../${BUILD_DIR})
target_link_libraries(unit-tests gmock_main wax-string-static)
