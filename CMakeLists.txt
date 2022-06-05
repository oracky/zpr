### Preamble ###
cmake_minimum_required(VERSION 3.15)
project(Zpr VERSION 0.1 LANGUAGES CXX)

##### Project wide setup ####
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE on)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})



### Testing ###
include(CTest)
enable_testing()
add_subdirectory(test)
add_test(NAME zpr_test COMMAND Test)

# ### Dependencies ###
# add_subdirectory(dependencies)

### Main Targets ###
add_subdirectory(src)


target_compile_options(Main PRIVATE -lsqlite3)