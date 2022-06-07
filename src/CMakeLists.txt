set(SQLTABLES_LIB_FILES SQLTable.cc SQLTable.h MeasurementTable.cc MeasurementTable.h CameraTable.cc CameraTable.h SimulationTable.cc SimulationTable.h SQLConnector.cc SQLConnector.h VehicleType.hpp)
set(SIMULATION_LIB_FILES Simulation.cc Simulation.h Vehicle.cc Vehicle.h VehicleGraphical.cc VehicleGraphical.h
    Config.cc Config.h Move.cc Move.h Road.cc Road.h Camera.cc Camera.h ParallelJob.cc ParallelJob.h ${SQLTABLES_LIB_FILES})

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

#look for SFML and add it
set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/SFML/cmake-modules/")
find_package (SFML COMPONENTS system graphics audio network REQUIRED)

# include_directories(${SFML_INCLUDE_DIR})

# add_library(Simulation Simulation.cpp Simulation.h)
# add_library(SQLTables ${SQLTABLES_LIB_FILES})
add_library(Simulation ${SIMULATION_LIB_FILES})
add_executable(Main Main.cpp)

if(UNIX)
    set(LINUX_LINK_DIRS /usr/lib)
    set(LINUX_INCLUDE_DIRS /usr/include)
    message(STATUS "Unix system detected - adding link directories: ${LINUX_LINK_DIRS} | adding include directories: ${LINUX_INCLUDE_DIRS}")
    link_directories(${LINUX_LINK_DIRS})
    include_directories(${LINUX_INCLUDE_DIRS} ${SFML_INCLUDE_DIR})
endif(UNIX)
# elseif(WIN32)
#     set(WIN_SQLITE_DIR ENV{SQLITE3})
#     message(STATUS "Unix system detected - adding sqlite directory: ${WIN_SQLITE_DIR}")
#     link_directories(${WIN_LINK_DIRS})
#     include_directories(${SFML_INCLUDE_DIR})
# endif(UNIX)

target_link_libraries(Main PRIVATE Simulation Threads::Threads sqlite3 sfml-audio sfml-graphics sfml-network sfml-system)
