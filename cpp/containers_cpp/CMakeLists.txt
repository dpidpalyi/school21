cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_COMPILER g++)
project(s21_containers LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

if(APPLE AND CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
  target_link_options(${PROJECT_NAME} INTERFACE -ld_classic)
endif()

option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
  include(cmake/updateSubmodules.cmake)
  add_subdirectory(extern/googletest)
  include(CTest)
  add_subdirectory(tests)
endif()
