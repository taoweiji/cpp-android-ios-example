# the minimum version of CMake.
cmake_minimum_required(VERSION 3.4.1)
project("cross")
include_directories(export_include)
set(NATIVERENDER_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

if(DEFINED PACKAGE_FIND_FILE)
    include(${PACKAGE_FIND_FILE})
endif()

include_directories(${NATIVERENDER_ROOT_PATH}
                    ${NATIVERENDER_ROOT_PATH}/include)

add_library(${PROJECT_NAME} SHARED napi_init.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC libace_napi.z.so url_signature)
#target_link_libraries(${PROJECT_NAME} url_signature)


#cmake_minimum_required(VERSION 3.10.2)
#project("cross")
#include_directories(export_include)
#add_library(${PROJECT_NAME} SHARED cross.cpp)
#find_library(log-lib log)
#target_link_libraries(${PROJECT_NAME} ${log-lib} url_signature)