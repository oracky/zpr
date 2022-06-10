set(SQLTABLES_LIB_FILES SQLTable.cc SQLTable.h MeasurementTable.cc MeasurementTable.h CameraTable.cc CameraTable.h SimulationTable.cc SimulationTable.h SQLConnector.cc SQLConnector.h VehicleType.hpp)
set(SIMULATION_LIB_FILES Simulation.cc Simulation.h Vehicle.cc Vehicle.h VehicleGraphical.cc VehicleGraphical.h
    Config.cc Config.h Move.cc Move.h Road.cc Road.h Camera.cc Camera.h ${SQLTABLES_LIB_FILES})

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

#look for SFML and add it
if(WIN32)
    set(CMAKE_PREFIX_PATH D:/SFML32)
    cmake_path(SET SQLITE3_INCLUDE D:/sqlite3/include)
    cmake_path(SET SFML_INCLUDE D:/SFML32)
    find_package (SFML 2.5 COMPONENTS graphics audio REQUIRED)
elseif(UNIX)
    set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/SFML/cmake-modules/")
    find_package (SFML COMPONENTS system graphics audio network REQUIRED)
endif()

add_library(Simulation ${SIMULATION_LIB_FILES})
add_executable(Main Main.cc)

if(WIN32)
    message(STATUS "Windows")
    target_link_libraries(Main PRIVATE Simulation Threads::Threads sqlite3 sfml-graphics sfml-audio)
elseif(UNIX)
    set(LINUX_LINK_DIRS /usr/lib)
    set(LINUX_INCLUDE_DIRS /usr/include)
    message(STATUS "Unix system detected - adding link directories: ${LINUX_LINK_DIRS} | adding include directories: ${LINUX_INCLUDE_DIRS}")
    link_directories(${LINUX_LINK_DIRS})
    include_directories(${LINUX_INCLUDE_DIRS} ${SFML_INCLUDE_DIR})
    target_link_libraries(Main PRIVATE Simulation Threads::Threads sqlite3 sfml-audio sfml-graphics sfml-network sfml-system)
endif()

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif(MSVC)
