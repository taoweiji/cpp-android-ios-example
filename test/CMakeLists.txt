cmake_minimum_required(VERSION 3.10.2)
project(test)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} jsoncpp gtest)