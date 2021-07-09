cmake_minimum_required(VERSION 3.10.2)
project(test)
# 添加可执行代码
add_executable(${PROJECT_NAME} main.cpp test.cpp)
# 添加库依赖
target_link_libraries(${PROJECT_NAME} gtest url_signature)