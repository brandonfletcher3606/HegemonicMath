cmake_minimum_required(VERSION 3.23)
project(HegemonicMath_TestHarness)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# add the testing and google test information
enable_testing()
add_subdirectory(googletest)

# get all sources files
file(GLOB SRC_FILES_HEGEMONIC_MATH_TH 
        ${PROJECT_SOURCE_DIR}/src/*.cpp)

# get all include files
file(GLOB INC_FILES_HEGEMONIC_MATH_TH 
        ${PROJECT_SOURCE_DIR}/include/*.h)

include_directories(${PROJECT_SOURCE_DIR}/include/)
add_executable(HegemonicMath_TestHarness ${SRC_FILES_HEGEMONIC_MATH_TH})

target_link_libraries(HegemonicMath_TestHarness
    PUBLIC gtest_main
    PRIVATE HegemonicMath)

add_test(NAME HegemonicMath_TestHarness
    COMMAND HegemonicMath_TestHarness)