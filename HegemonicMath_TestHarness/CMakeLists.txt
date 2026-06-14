cmake_minimum_required(VERSION 3.23)
project(HegemonicMath_TestHarness)

set(CMAKE_CXX_STANDARD 20)
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

set_target_properties(HegemonicMath PROPERTIES
    IMPORTED_IMPLIB               "${PROJECT_SOURCE_DIR}/../HegemonicMath/external/lib/Debug/HegemonicMath.lib"
    IMPORTED_LOCATION             "${PROJECT_SOURCE_DIR}/../HegemonicMath/external/bin/Debug/HegemonicMath.dll"
    INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/../HegemonicMath/include"
)

include_directories(${PROJECT_SOURCE_DIR}/include/)
add_executable(HegemonicMath_TestHarness ${SRC_FILES_HEGEMONIC_MATH_TH})

target_link_libraries(HegemonicMath_TestHarness 
        PUBLIC gtest_main
        PRIVATE HegemonicMath)

# this command copies all the dlls to where the executable is
add_custom_command(TARGET HegemonicMath_TestHarness POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:HegemonicMath_TestHarness> $<TARGET_FILE_DIR:HegemonicMath_TestHarness>
  COMMAND_EXPAND_LISTS
)

add_test(NAME HegemonicMath_TestHarness
    COMMAND HegemonicMath_TestHarness)