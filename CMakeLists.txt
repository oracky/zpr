cmake_minimum_required(VERSION 3.0.0)
project(zpr VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(zpr src/main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
include(FetchContent)

# # You can configure this for your need, presumbably you want speificy a git tag here instead of a branch
# FetchContent_Declare(sqliteOrm
#   GIT_REPOSITORY https://github.com/fnc12/sqlite_orm
#   GIT_TAG        origin/master
# )

# add_subdirectory(sqlite_orm)
