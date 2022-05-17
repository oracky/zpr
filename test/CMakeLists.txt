find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories (${CMAKE_SOURCE_DIR}/src
                     ${Boost_INCLUDE_DIRS}
                     )
add_definitions (-DBOOST_TEST_DYN_LINK)
add_executable (Test TestSimulation.cpp)
target_link_libraries (Test
                       Simulation
                       ${Boost_FILESYSTEM_LIBRARY}
                       ${Boost_SYSTEM_LIBRARY}
                       ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                       )