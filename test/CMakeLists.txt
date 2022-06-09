find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories (${CMAKE_SOURCE_DIR}/src
                     ${Boost_INCLUDE_DIRS}
                     )
                     
set(LIBRARIES_FOR_TESTS Simulation sfml-audio sfml-graphics sfml-network sfml-system
                     ${Boost_FILESYSTEM_LIBRARY}
                     ${Boost_SYSTEM_LIBRARY}
                     ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                     )

add_definitions (-DBOOST_TEST_DYN_LINK)
add_executable (TestCamera TestCamera.cc)
add_executable (TestVehicle TestVehicle.cc)
add_executable (TestRoad TestRoad.cc)
add_executable (TestSQL TestSQL.cc)

target_link_libraries (TestCamera ${LIBRARIES_FOR_TESTS})
target_link_libraries (TestVehicle ${LIBRARIES_FOR_TESTS})
target_link_libraries (TestRoad ${LIBRARIES_FOR_TESTS})
target_link_libraries (TestSQL ${LIBRARIES_FOR_TESTS} sqlite3)

