# cmake setup
cmake_minimum_required(VERSION 3.23)
project(HegemonicEngineTotal)

message("Building HegemonicMath...")
add_subdirectory(HegemonicMath)
message("...Building HegemonicMath Complete")

message("Building HegemonicMath Test Harness...")
add_subdirectory(HegemonicMath_TestHarness)
message("...Building HegemonicMath Test Harness Complete")
