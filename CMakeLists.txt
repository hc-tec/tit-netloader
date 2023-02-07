cmake_minimum_required(VERSION 3.16)

project(tit-netloader)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


add_compile_options(-Wall -O0 -std=c++17 -g -Wno-sign-compare -Wno-class-memaccess -Wno-strict-aliasing)



include_directories(src)
include_directories(third_party/http-parser)
# link dir of libhttp_parser.so
link_directories(third_party/http-parser)

add_subdirectory(src/core)
add_subdirectory(test)
add_subdirectory(third_party/cocoyaxi)


link_directories(third_party)



#include_directories(include/base)
#include_directories(include/log)


