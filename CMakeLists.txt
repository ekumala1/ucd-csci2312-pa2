cmake_minimum_required(VERSION 3.3)
project(ucd_csci2312_pa2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES pa2.cpp Point.cpp Point.h Cluster.cpp Cluster.h pa2check.cpp pa2check.h KMeans.cpp KMeans.h)
add_executable(ucd_csci2312_pa2 ${SOURCE_FILES})