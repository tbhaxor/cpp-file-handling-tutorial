cmake_minimum_required(VERSION 3.10)

project(FileHandling)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_subdirectory(WritingFile)
add_subdirectory(ReadingFile)
add_subdirectory(AppendingFile)
add_subdirectory(BinaryFile)
add_subdirectory(FileRW)