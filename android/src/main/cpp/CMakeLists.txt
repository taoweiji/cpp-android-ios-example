# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)
project("cross")
include_directories(export_include)
add_library(${PROJECT_NAME} SHARED native-lib.cpp)
find_library(log-lib log)
set(XLOG_PATH ../jniLibs/jni/${ANDROID_ABI}/)
find_library(xlog-lib marsxlog PATHS ${XLOG_PATH} NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
target_link_libraries(${PROJECT_NAME} jsoncpp ${log-lib} ${xlog-lib})