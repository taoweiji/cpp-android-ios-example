cmake_minimum_required(VERSION 3.10.2)
project(jsoncpp)
add_library(${PROJECT_NAME} src/json_reader.cpp src/json_value.cpp src/json_writer.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)