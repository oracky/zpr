add_library(Simulation simulation.cpp simulation.h)
add_executable(Main main.cpp)
target_link_libraries(Main PRIVATE sqlite_orm::sqlite_orm Simulation)
