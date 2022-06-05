set(LINUX_LINK_DIRS /usr/lib)
set(LINUX_INCLUDE_DIRS /usr/include)
set(SQLTABLES_LIB_FILES SQLTable.cc SQLTable.h MeasurementTable.cc MeasurementTable.h CameraTable.cc CameraTable.h SimulationTable.cc SimulationTable.h SQLConnector.cc SQLConnector.h VehicleType.hpp)

# add_library(Simulation Simulation.cpp Simulation.h)
add_library(SQLTables ${SQLTABLES_LIB_FILES})
add_library(Simulation Simulation.cpp Simulation.h)
add_executable(Main Main.cpp)

if(UNIX)
    message(STATUS "Unix system detected - adding link directories: ${LINUX_LINK_DIRS} | adding include directories: ${LINUX_INCLUDE_DIRS}")
    link_directories(${LINUX_LINK_DIRS})
    include_directories(${LINUX_INCLUDE_DIRS})
endif(UNIX)

target_link_libraries(Main PRIVATE SQLTables sqlite3)
