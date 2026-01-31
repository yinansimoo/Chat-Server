cmake_minimum_required(VERSION 3.0)
project(main)

set(LAG ${LAG} -g)

#include_directories(/usr/include)

#link_directories(/usr/bin)

set(LLAG ./testjson.cpp)
#aux_source_directory(. LLAGA)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(server ${LLAG})

#target_link_libraries()

