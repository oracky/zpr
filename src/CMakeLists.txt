add_library(Simulation Simulation.cpp Simulation.h)
add_executable(Main Main.cpp)
target_link_libraries(Main PRIVATE sqlite_orm::sqlite_orm Simulation)
