# cmake setup
cmake_minimum_required(VERSION 3.24)
project(HegemonicMath)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# get all sources files
file(GLOB SRC_FILES_HEGEMONIC_MATH 
        ${PROJECT_SOURCE_DIR}/src/*.cpp)

# get all include files
file(GLOB INC_FILES_HEGEMONIC_MATH 
        ${PROJECT_SOURCE_DIR}/include/*.h)

# set the directories for the install locations
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/external/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/external/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/external/lib")

# build executable and link libraries
include_directories(${PROJECT_SOURCE_DIR}/include/)
add_library(HegemonicMath SHARED ${SRC_FILES_HEGEMONIC_MATH})

target_include_directories(HegemonicMath
    PUBLIC ${PROJECT_SOURCE_DIR}/include/)

# setting which header files should be supplied with the library
set_target_properties(HegemonicMath PROPERTIES PUBLIC_HEADER ${INC_FILES_HEGEMONIC_MATH})

# copy over files
file(COPY ${PROJECT_SOURCE_DIR}/include/ DESTINATION ${PROJECT_SOURCE_DIR}/external/include/)

# # add the command to copy over include directories
# install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION ${PROJECT_SOURCE_DIR}/external/include/)

# # call the command on the BUILD phase
# add_custom_command(TARGET HegemonicMath POST_BUILD
#         COMMAND cmake --install ${PROJECT_SOURCE_DIR}/../build)
