#define BOOST_TEST_MODULE SQLTest test
#include <boost/test/unit_test.hpp>
#include <sqlite3.h> 
#include "SQLConnector.h"
#include "MeasurementTable.h"
#include "CameraTable.h"
#include "SimulationTable.h"
#include "VehicleType.hpp"
#include "Config.h"


static int callback(void *data, int argc, char **argv, char **azColName){
   return 0;
}

BOOST_AUTO_TEST_CASE(SQLTest)
{
    char *z_err_msg = 0;
    const char* data = "Callback function called";
    std::string name = "SimulationTest";
    auto config = Config(0, nullptr, true);

    auto connector = std::make_unique<SQLConnector>(config.getDatabaseFilePath());
    
    auto camera_table = CameraTable(1,50);
    auto sim_table = SimulationTable(name);
    auto measure_table = MeasurementTable(1, 2, 1.0, VehicleType::CAR, camera_table, sim_table);

    connector->insertData(sim_table);
    connector->insertData(camera_table);
    connector->insertData(measure_table);

    auto db = connector->getDatabaseConnection();

    auto sql = "SELECT * from Simulations WHERE name='SimulationTest'";
    auto rc = sqlite3_exec(db, sql, callback, (void*)data, &z_err_msg);
    BOOST_CHECK_EQUAL(rc, SQLITE_OK);

    sql = "SELECT * from Cameras WHERE y_coordinate=50";
    rc = sqlite3_exec(db, sql, callback, (void*)data, &z_err_msg);
    BOOST_CHECK_EQUAL(rc, SQLITE_OK);

    sql = "SELECT * from Measurements WHERE vehicle_type=1";
    rc = sqlite3_exec(db, sql, callback, (void*)data, &z_err_msg);
    BOOST_CHECK_EQUAL(rc, SQLITE_OK);
}