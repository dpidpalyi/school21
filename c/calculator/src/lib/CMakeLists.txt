cmake_minimum_required(VERSION 3.5)

project(lib)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
  calc.c
  calc.h
  parse.c 
  parse.h
  stack.c
  stack.h
)

add_library(${PROJECT_NAME} STATIC . ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
