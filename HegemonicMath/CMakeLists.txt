# cmake setup
cmake_minimum_required(VERSION 3.24)
project(HegemonicMath)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# get all sources files
file(GLOB SRC_FILES_HEGEMONIC_MATH 
        ${PROJECT_SOURCE_DIR}/src/*.cpp)

# build executable and link libraries
add_library(HegemonicMath ${SRC_FILES_HEGEMONIC_MATH})

target_include_directories(HegemonicMath 
    PUBLIC ${PROJECT_SOURCE_DIR}/include/
    )
