### Preamble ###
cmake_minimum_required(VERSION 3.15)
project(Zpr VERSION 0.1 LANGUAGES CXX)

##### Project wide setup ####
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE on)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

### Testing ###
include(CTest)
enable_testing()
add_subdirectory(test)
add_test(NAME CAMERA_TEST COMMAND TestCamera)
add_test(NAME VEHICLE_TEST COMMAND TestVehicle)
add_test(NAME ROAD_TEST COMMAND TestRoad)
add_test(NAME SQL_TEST COMMAND TestSQL)


### Main Targets ###
add_subdirectory(src)

target_compile_options(Main PRIVATE -lsqlite3)