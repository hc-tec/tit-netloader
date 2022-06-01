cmake_minimum_required(VERSION 3.16)

project(tit-netloader)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


add_compile_options(-Wall -O0 -std=c++17 -g -Wno-sign-compare -Wno-class-memaccess -Wno-strict-aliasing)


# build with openssl 1.1.0+
option(WITH_OPENSSL "build with openssl" ON)


include_directories(src)

# link dir of libhttp_parser.so
link_directories(/usr/local/lib)

link_libraries(co)
link_libraries(backtrace)
link_libraries(http_parser)

add_subdirectory(src/core)
add_subdirectory(test)

link_directories(third_party)



#include_directories(include/base)
#include_directories(include/log)


