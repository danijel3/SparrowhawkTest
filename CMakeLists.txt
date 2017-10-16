cmake_minimum_required(VERSION 3.6)
project(SparrowhawkTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/bin)

link_directories("$ENV{CONDA_PREFIX}/lib")
include_directories("$ENV{CONDA_PREFIX}/include")

set(SOURCE_FILES main.cpp)
add_executable(SparrowhawkTest ${SOURCE_FILES})

target_link_libraries(SparrowhawkTest "sparrowhawk" "dl" "re2" "protobuf" "pthread" "thrax" "fst" "fstfar")
