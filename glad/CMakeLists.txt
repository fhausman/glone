cmake_minimum_required (VERSION 3.13)
project("glad")

add_library(glad STATIC "src/glad.c" "include/glad/glad.h")
target_include_directories(glad PRIVATE "include")

set_property(TARGET glad PROPERTY CXX_STANDARD 17)
set_property(TARGET glad PROPERTY CXX_COMPILE_FEATURES cxx_std_17)
