cmake_minimum_required(VERSION 3.10.2)
project(download)
add_library(${PROJECT_NAME} download.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)