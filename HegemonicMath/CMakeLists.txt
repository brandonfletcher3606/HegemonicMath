# cmake setup
cmake_minimum_required(VERSION 3.24)
project(HegemonicMath VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# get all sources files
file(GLOB SRC_FILES_HEGEMONIC_MATH 
        ${PROJECT_SOURCE_DIR}/src/*.cpp)

# get all include files
file(GLOB INC_FILES_HEGEMONIC_MATH 
        ${PROJECT_SOURCE_DIR}/include/*.h)

configure_file(${PROJECT_SOURCE_DIR}/include/HegemonicMathVersion.h.in "${PROJECT_SOURCE_DIR}/include/HegemonicMathVersion.h")

# build executable and link libraries
include_directories(${INC_FILES_HEGEMONIC_MATH})
add_library(HegemonicMath SHARED ${SRC_FILES_HEGEMONIC_MATH})

# this add a compile tile variable to be used, BUILDING_HEGEMONIC_TOOLS is specific for declspec
target_compile_definitions(HegemonicMath PRIVATE BUILDING_HEGEMONIC_MATH=1)

# select directies for the dll/so/lib
set_target_properties(HegemonicMath PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/external/lib"   # Path for .lib
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/external/lib"   # Path for .so (Linux)
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/external/bin"   # Path for .dll
)

target_include_directories(HegemonicMath
    PUBLIC ${PROJECT_SOURCE_DIR}/include/)

# copy over files
# file(COPY ${PROJECT_SOURCE_DIR}/include/ DESTINATION ${PROJECT_SOURCE_DIR}/external/include/)
