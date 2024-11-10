cmake_minimum_required(VERSION 3.20)
project(pq VERSION 0.1 DESCRIPTION "kx q map")
add_library(p.q SHARED p.q.cpp)
target_include_directories(p.q PRIVATE .)
