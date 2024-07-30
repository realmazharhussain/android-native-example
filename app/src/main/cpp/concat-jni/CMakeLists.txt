cmake_minimum_required(VERSION 3.10)
project("concat JNI")

add_subdirectory(concat)
add_library(concat-jni SHARED concat-jni.c)
target_link_libraries(concat-jni concat)
target_include_directories(concat-jni PUBLIC concat)
