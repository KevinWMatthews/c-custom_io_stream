cmake_minimum_required(VERSION 3.5)

project(io_stream VERSION 0.1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_executable(null_io_stream null_io_stream.c)
add_executable(custom_io_stream custom_io_stream.c)
