cmake_minimum_required(VERSION 3.3)
project(DICT)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -liconv")

set(SOURCE_FILES main.cpp readerlib.h readerlib.cpp readtext.cpp readtext.h)
add_library(Reader STATIC readerlib.cpp)
add_executable(DICT ${SOURCE_FILES})
target_link_libraries(DICT Reader)
