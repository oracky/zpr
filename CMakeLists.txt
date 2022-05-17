### Preamble ###
cmake_minimum_required(VERSION 3.15)
project(Zpr VERSION 0.1 LANGUAGES CXX)

##### Project wide setup ####
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

### Testing ###
include(CTest)
enable_testing()
add_subdirectory(test)
add_test(NAME zpr_test COMMAND Test)

### Dependencies ###
add_subdirectory(dependencies)

### Main Targets ###
add_subdirectory(src)


