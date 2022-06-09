#include <fstream>
#include <iostream>
#include <vector>
#include "Config.h"


/**
 * An empty constructor for the ConfigBase class.
 */
ConfigBase::ConfigBase() {}

/**
 * This function is a constructor for the ConfigBase class.
 * 
 * @param config_parameters_number The number of parameters that the config file will have.
 */
ConfigBase::ConfigBase(int config_parameters_number) : config_parameters_number_(config_parameters_number) {}

/**
 * The destructor for the ConfigBase class.
 */
ConfigBase::~ConfigBase() {}

/**
 * This function returns the number of parameters that the config file will have
 * 
 * @return The number of config parameters.
 */
int ConfigBase::getConfigParametersNumber() const { return config_parameters_number_; }


/**
 * An empty constructor for the class RowObjectPlacementConfigBase.
 */
RowObjectPlacementConfigBase::RowObjectPlacementConfigBase(){}

/**
 * This function is a constructor for the RowObjectPlacementConfigBase class.
 * 
 * @param config_parameters_number The number of parameters that the config has.
 */
RowObjectPlacementConfigBase::RowObjectPlacementConfigBase(int config_parameters_number) : ConfigBase(config_parameters_number) {}

/**
 * `RowObjectPlacementConfigBase::~RowObjectPlacementConfigBase()`
 * 
 * The destructor is called when the object is destroyed.
 */
RowObjectPlacementConfigBase::~RowObjectPlacementConfigBase(){}

/**
 * This function is used to create a config from a vector of strings
 * 
 * @param vec a vector of strings that contains the values of the parameters in the order they were
 * defined in the config file.
 * @param configs This is the container that will hold the configs.
 */
void RowObjectPlacementConfigBase::createConfigFromContainer(const std::vector<std::string>& vec, ConfigsContainer& configs){}


/**
 * Config constructor. It parses the command line arguments, reads the config files ot sets the default values for the
 * configs if all_default is set to true.
 * 
 * @param argc The number of arguments passed to the program.
 * @param argv the command line arguments
 * @param all_default If true, all the parameters will be set to default values.
 */
Config::Config(int argc, char **argv, bool all_default) : database_file_(DB_PATH), measure_refresh_rate_ms_(DEFAULT_REFRESH_RATE)
{
    configs_ = ConfigsContainer();
    if (all_default)
        setAllDefaults();
    else
    {
        parseInputArgs(argc, argv);
        auto r_config = RoadConfig();
        auto v_config = VehicleConfig();
        auto c_config = CameraConfig();
        readConfig(roads_file_, r_config);
        readConfig(vehicle_file_, v_config);
        readConfig(cameras_file_, c_config);
    }
}

/**
 * Config constructor. It sets appropiate fields with specified database_file, refresh rate and configs.
 * 
 * @param database_file The path to the database file.
 * @param refresh the refresh rate of the measurements in milliseconds
 * @param roads_config a vector of RoadConfig objects
 * @param vehicles_config a vector of VehicleConfig objects
 * @param cameras_config a vector of CameraConfig objects
 */
Config::Config(const std::string& database_file, int refresh,
 const std::vector<RoadConfig>& roads_config,  const std::vector<VehicleConfig>& vehicles_config,
 const std::vector<CameraConfig>& cameras_config)
    : database_file_(database_file), measure_refresh_rate_ms_(refresh) 
{
    configs_ = ConfigsContainer();
    configs_.cameras_config_ = cameras_config;
    configs_.roads_config_ = roads_config;
    configs_.vehicles_config_ = vehicles_config;
}

/**
 * The destructor for the Config class.
 */
Config::~Config(){}

/**
 * This function returns refresh rate of the measure in milliseconds.
 * 
 * @return The refresh rate of the measure in milliseconds.
 */
int Config::getRefreshRate() const { return measure_refresh_rate_ms_; }

/**
 * It returns the database file path.
 * 
 * @return The database file path.
 */
std::string Config::getDatabaseFilePath() const { return database_file_; }

/**
 * This function returns the vector of RoadConfig objects that is stored in the ConfigContainer object.
 * 
 * @return A vector of RoadConfig objects.
 */
std::vector<RoadConfig> Config::getRoadsConfig() const { return configs_.roads_config_; }

/**
 * It returns the vector of vehicle configs.
 * 
 * @return A vector of VehicleConfig objects.
 */
std::vector<VehicleConfig> Config::getVehiclesConfig() const { return configs_.vehicles_config_; }

/**
 * It returns a vector of CameraConfig objects.
 * 
 * @return A vector of CameraConfig objects.
 */
std::vector<CameraConfig> Config::getCamerasConfig() const { return configs_.cameras_config_; }

/**
 * This function sets the refresh rate of the measurement
 * 
 * @param refresh The refresh rate of the sensor in milliseconds.
 */
void Config::setRefreshRate(int refresh) { measure_refresh_rate_ms_ = refresh; }

/**
 * This function sets the database file path.
 * 
 * @param path The path to the database file.
 */
void Config::setDatabaseFilePath(const std::string& path) { database_file_ = path; }

/**
 * It sets the roads_config_ variable to the value of the roads_config parameter.
 * 
 * @param roads_config A vector of RoadConfig objects.
 */
void Config::setRoadsConfig(const std::vector<RoadConfig>& roads_config) { configs_.roads_config_ = roads_config;}

/**
 * It sets vehicle_config_ variable to the value of the vehicles_config parameter
 * 
 * @param vehicles_config A vector of VehicleConfig objects.
 */
void Config::setVehiclesConfig(const std::vector<VehicleConfig>& vehicles_config) { configs_.vehicles_config_ = vehicles_config;}

/**
 * It creates a prepared and tested road system, vehicle environment, and places for cameras
 */
void Config::setAllDefaults()
{
    //create hardcoded and tested road system
    setDefaultConfigsForRoads(8, RoadDirection::HORIZONTAL, 0, 0);
    setDefaultConfigsForRoads(2, RoadDirection::VERTICAL, 200, 0, 90, 360.0f, 20.0f, 100);
    setDefaultConfigsForRoads(1, RoadDirection::VERTICAL, 400, 0, 90, 800.0f, 20.0f, 100);
    setDefaultConfigsForRoads(2, RoadDirection::VERTICAL, 500, 0, 90, 360.0f, 20.0f, 100);
    setDefaultConfigsForRoads(2, RoadDirection::VERTICAL, 200, 460, 90, 320.0f, 20.0f, 100);
    setDefaultConfigsForRoads(2, RoadDirection::VERTICAL, 500, 460, 90, 320.0f, 20.0f, 100);
    setDefaultConfigsForRoads(1, RoadDirection::VERTICAL, 50, 280, 90, 320.0f, 20.0f, 100);

    // create hardcoded and tested vehicle env
    setConfigsForVehicles(DEFAULT_CAR_NUMBER, DEFAULT_TRUCK_NUMBER, DEFAULT_PEDESTRIAN_NUMBER);

    // create hardcoded and tested places for cameras
    setDefaultConfigsForCameras();
}

/**
 * It sets the default configuration for the roads
 * 
 * @param roads_number number of roads to be created
 * @param direction The direction of the road.
 * @param initial_x the x coordinate of the first road
 * @param initial_y the y coordinate of the first road
 * @param rotation the angle of rotation of the road.
 * @param length length of the road
 * @param width width of the road
 * @param margin the distance between two roads
 */
void Config::setDefaultConfigsForRoads(int roads_number, RoadDirection direction, int initial_x, int initial_y,  int rotation, float length, float width, int margin)
{
    auto move = direction == RoadDirection::HORIZONTAL ? Move(MoveType::RIGHT, MoveType::NONE) : Move(MoveType::NONE, MoveType::DOWN);
    auto margin_x = direction == RoadDirection::HORIZONTAL ? 0 : margin;
    auto margin_y = direction == RoadDirection::HORIZONTAL ? margin : 0;
    auto rotate = direction == RoadDirection::HORIZONTAL ? 0 : rotation;

    for (int i=1; i<=roads_number; ++i)
    {
        auto road_config = RoadConfig(i * margin_x + initial_x, i * margin_y + initial_y, length, width, move, rotate);
        configs_.roads_config_.push_back(road_config);
    }
}

/**
 * It takes in the number of cars, trucks and pedestrians and then creates a vehicle config for each of
 * them and pushes it into the configs_.vehicles_config_ vector
 * 
 * @param car_number number of cars
 * @param truck_number number of trucks
 * @param pedestrian_number number of pedestrians
 */
void Config::setConfigsForVehicles(int car_number, int truck_number, int pedestrian_number)
{
    configs_.vehicles_config_.clear();

    while(car_number > 0 && truck_number > 0 && pedestrian_number > 0)
    {
        for (auto& road : configs_.roads_config_)
        {
            if ( car_number > 0)
            {
                auto vehicle_config = VehicleConfig(road.getXCoordinate()-1, road.getYCoordinate()-1, CAR_SPEED, VehicleType::CAR, sf::Color::Blue, 10.f);
                configs_.vehicles_config_.push_back(vehicle_config);
                --car_number;
            }
            if ( truck_number > 0)
            {
                auto vehicle_config = VehicleConfig(road.getXCoordinate()-1, road.getYCoordinate()-1, TRUCK_SPEED, VehicleType::TRUCK, sf::Color::Black, 10.f);
                configs_.vehicles_config_.push_back(vehicle_config);
                --truck_number;
            }
            if ( pedestrian_number > 0)
            {
                auto vehicle_config = VehicleConfig(road.getXCoordinate()-1, road.getYCoordinate()-1, PEDESTRIAN_SPEED, VehicleType::PEDESTRIAN, sf::Color::Red, 10.f);
                configs_.vehicles_config_.push_back(vehicle_config);
                --pedestrian_number;
            }
        }

    }
}

/**
 * It sets the default camera configurations
 */
void Config::setDefaultConfigsForCameras()
{
    configs_.cameras_config_.clear();
    
    // hardcoded camera configs, which was selected to present different rotation, sizes and placement
    configs_.cameras_config_.push_back(CameraConfig(630, 430, 90, sf::Color(0,255,0,200), 30));
    configs_.cameras_config_.push_back(CameraConfig(330, 230, 90, sf::Color(0,255,0,200), 30));
    configs_.cameras_config_.push_back(CameraConfig(330, 440, 270, sf::Color(0,255,0,200), 60));
    configs_.cameras_config_.push_back(CameraConfig(630, 90, 0, sf::Color(0,255,0,200), 15));
    configs_.cameras_config_.push_back(CameraConfig(270, 65, 45, sf::Color(0,255,0,200), 45));
    configs_.cameras_config_.push_back(CameraConfig(150, 235, 45, sf::Color(0,255,0,200), 45));
    configs_.cameras_config_.push_back(CameraConfig(310, 450, 45, sf::Color(0,255,0,200), 30));
    configs_.cameras_config_.push_back(CameraConfig(530, 530, 90, sf::Color(0,255,0,200), 30));
    configs_.cameras_config_.push_back(CameraConfig(530, 230, 120, sf::Color(0,255,0,200), 30));
}

/**
 * It reads a csv-like file and creates a config object for each row in the csv-like file
 * 
 * @param path the path to the config file
 * @param config_instance This is the instance of the class that will be used to create the config.
 */
void Config::readConfig(const std::string& path, RowObjectPlacementConfigBase& config_instance)
{

    std::ifstream file;
    std::vector<std::string> row_values;
    std::string line;

    file.open(path);
    if (file.is_open())
    {
      while(getline(file, line, ',')) {
          row_values.push_back(line);
          if(row_values.size() == config_instance.getConfigParametersNumber())
          {
              config_instance.createConfigFromContainer(row_values, configs_);
              row_values.clear();
          }
      }
      file.close();
    }
}

/**
 * It reads the config file and sets the configs for the vehicles
 * 
 * @param path The path to the configuration file.
 * @param vehicle_config This is the vehicle configuration object that contains the number of
 * parameters that are expected to be read from the config file.
 */
void Config::readConfig(const std::string& path, const VehicleConfig& vehicle_config)
{
    std::ifstream file;
    std::vector<std::string> row_values;
    std::string line;
    char* p_end;

    file.open(path);
    if (file.is_open())
    {
      while(getline(file, line, ',')) {
          row_values.push_back(line);
          if(row_values.size() == vehicle_config.getConfigParametersNumber())
          {
              setConfigsForVehicles(std::strtol(row_values[0].c_str(), &p_end, 10), std::strtol(row_values[1].c_str(), &p_end, 10), std::strtol(row_values[2].c_str(), &p_end, 10));
              break;
          }
      }
      file.close();
    }
}

/**
 * It parses the input arguments and sets the configuration variables accordingly
 * 
 * @param argc number of arguments
 * @param argv list of arguments
 */
void Config::parseInputArgs(int argc, char** argv)
{
    char* p_end;
    
    switch (argc)
    {
    case 1:
        std::cout << "Didn't provide any configuration information. Continuing with default settings" << std::endl;
        break;
    case 2:
        std::cout << "Provided " << argv[1] << " as a path to database. Refresh rate and other configuration information is set to default." << std::endl;
        database_file_ = argv[1];
        break;
    case 3:
        std::cout << "Provided " << argv[1] << " as a path to database." << std::endl
                  << "Provided " << argv[2] << "ms as a refresh rate for measurements and database saving. Other configuration information is set to default." << std::endl;
        database_file_ = argv[1];
        measure_refresh_rate_ms_ = std::strtol(argv[2], &p_end, 10);
        break;
    case 4:
        std::cout << "Provided " << argv[1] << " as a path to database." << std::endl
                  << "Provided " << argv[2] << "ms as a refresh rate for measurements and database saving." << std::endl
                  << "Provided " << argv[3] << " as a path to roads config. Other configuration information is set to default." << std::endl;
        database_file_ = argv[1];
        measure_refresh_rate_ms_ = std::strtol(argv[2], &p_end, 10);
        roads_file_ = argv[3];
        break;
    case 5:
        std::cout << "Provided " << argv[1] << " as a path to database." << std::endl
                  << "Provided " << argv[2] << "ms as a refresh rate for measurements and database saving." << std::endl
                  << "Provided " << argv[3] << " as a path to roads config. " << std::endl
                  << "Provided " << argv[4] << " as a path to vehciles config. Other configuration information is set to default." << std::endl;
        database_file_ = argv[1];
        measure_refresh_rate_ms_ = std::strtol(argv[2], &p_end, 10);
        roads_file_ = argv[3];
        vehicle_file_ = argv[4];
        break;
    case 6:
        std::cout << "Provided " << argv[1] << " as a path to database." << std::endl
                  << "Provided " << argv[2] << "ms as a refresh rate for measurements and database saving." << std::endl
                  << "Provided " << argv[3] << " as a path to roads config."  << std::endl
                  << "Provided " << argv[4] << " as a path to vehciles config." << std::endl
                  << "Provided " << argv[5] << " as a path to cameras config." << std::endl;
        database_file_ = argv[1];
        measure_refresh_rate_ms_ = std::strtol(argv[2], &p_end, 10);
        roads_file_ = argv[3];
        vehicle_file_ = argv[4];
        cameras_file_ = argv[5];
        break;
    default:
        std::cout << "Wrong usage. Try: ./Main [db_path] [refresh_rate] [roads_cfg_file] [vehicles_cfg_file] [cameras_cfg_file]." << std::endl;
        exit(1);
    }
}


/**
 * `RoadConfig()` is a constructor for the `RoadConfig` class
 */
RoadConfig::RoadConfig() : RowObjectPlacementConfigBase(CONFIG_PARAMETERS_NUMBER_) {}

/**
 * This function is a constructor for the RoadConfig class
 * 
 * @param x x coordinate of the road
 * @param y The y coordinate of the road.
 * @param length The length of the road in meters.
 * @param width The width of the road.
 * @param preferedMove The prefered move on the road.
 * @param rotation_degrees The angle of the road in degrees.
 */
RoadConfig::RoadConfig(int x, int y, float length, float width, const Move& preferedMove, int rotation_degrees)
    : RowObjectPlacementConfigBase(CONFIG_PARAMETERS_NUMBER_), x_(x), y_(y), length_(length), width_(width), prefered_move_(preferedMove), rotation_degrees_(rotation_degrees) {}

/**
 * It returns the x coordinate of the road.
 * 
 * @return The x coordinate of the road.
 */
int RoadConfig::getXCoordinate() const { return x_; }

/**
 * It returns the y coordinate of the road.
 * 
 * @return The y coordinate of the road.
 */
int RoadConfig::getYCoordinate() const { return y_; }

/**
 *  It returns the rotation of the road in degrees.
 * 
 * @return The rotation of the road in degrees.
 */
int RoadConfig::getRotation() const { return rotation_degrees_; }

/**
 * It returns the length of the road.
 * 
 * @return The length of the road.
 */
float RoadConfig::getLength() const { return length_; }

/**
 * It returns the width of the road.
 * 
 * @return The width of the road.
 */
float RoadConfig::getWidth() const { return width_; }

/**
 * It returns the prefered move of the road.
 * 
 * @return The prefered move of the road.
 */
Move RoadConfig::getPreferedMove() const { return prefered_move_; }

/**
 * This function sets the x coordinate of the road.
 * 
 * @param x The x coordinate of the road.
 */
void RoadConfig::setXCoordinate(int x) { x_ = x; }

/**
 * This function sets the y coordinate of the road.
 * 
 * @param y The y coordinate of the road.
 */
void RoadConfig::setYCoordinate(int y) { y_ = y; }

/**
 * This function sets the rotation of the road
 * 
 * @param degrees The rotation of the road in degrees.
 */
void RoadConfig::setRotation(int degrees) { rotation_degrees_ = degrees; }

/**
 * This function sets the length of the road.
 * 
 * @param length The length of the road.
 */
void RoadConfig::setLength(float length) { length_ = length; }

/**
 * Sets the width of the road.
 * 
 * @param width The width of the road.
 */
void RoadConfig::setWidth(float width) { width_ = width; }

/**
 * Sets the prefered move.
 * 
 * @param prefered_move The move that the car should make.
 */
void RoadConfig::setPreferedMove(const Move& prefered_move) { prefered_move_ = prefered_move; }

/**
 * It takes a vector of strings each of which representing single value from the config file row and converts them into a RoadConfig object
 * 
 * @param vec a vector of strings that contains the parameters for the road.
 * @param configs The container that holds all the configs.
 */
void RoadConfig::createConfigFromContainer(const std::vector<std::string>& vec, ConfigsContainer& configs)
{
    char* p_end;

    int x = std::strtol(vec[0].c_str(), &p_end, 10);
    int y = std::strtol(vec[1].c_str(), &p_end, 10);
    float length = std::strtof(vec[2].c_str(), &p_end);
    float width = std::strtof(vec[3].c_str(), &p_end);
    RoadDirection direction = static_cast<RoadDirection>(std::strtol(vec[4].c_str(), &p_end, 10));
    auto move = direction == RoadDirection::HORIZONTAL ? Move(MoveType::RIGHT, MoveType::NONE) : Move(MoveType::NONE, MoveType::DOWN);
    int rotation = std::strtol(vec[5].c_str(), &p_end, 10);
    configs.roads_config_.push_back(RoadConfig(x, y, length, width, move, rotation));
}

/**
 * The constructor of the VehicleConfig class initializes the number of parameters to be configured
 */
VehicleConfig::VehicleConfig() : ConfigBase(CONFIG_PARAMETERS_NUMBER_) {}

/**
 * It's a constructor for the VehicleConfig class
 * 
 * @param x x coordinate of the vehicle
 * @param y The y coordinate of the vehicle.
 * @param speed The speed of the vehicle.
 * @param type The type of vehicle.
 * @param color The color of the vehicle.
 * @param size the size of the vehicle.
 */
VehicleConfig::VehicleConfig(int x, int y, int speed, const VehicleType& type, const sf::Color& color, float size)
    : ConfigBase(CONFIG_PARAMETERS_NUMBER_), x_(x), y_(y), speed_(speed), type_(type), color_(color), size_(size) {}

/**
 * It returns the x coordinate of the vehicle.
 * 
 * @return The x coordinate of the vehicle.
 */
int VehicleConfig::getXCoordinate() const { return x_; }

/**
 * This function returns the y coordinate of the vehicle.
 * 
 * @return The y coordinate of the vehicle.
 */
int VehicleConfig::getYCoordinate() const { return y_; }

/**
 * It returns the speed of the vehicle.
 * 
 * @return The speed of the vehicle.
 */
int VehicleConfig::getSpeed() const { return speed_; }

/**
 * This function returns the size of the vehicle.
 * 
 * @return The size of the vehicle.
 */
float VehicleConfig::getSize() const { return size_; }

/**
 * This function returns vehicle type
 * 
 * @return The type of vehicle.
 */
VehicleType VehicleConfig::getVehicleType() const { return type_; }

/**
 * This function returns the color of the vehicle
 * 
 * @return The color of the vehicle.
 */
sf::Color VehicleConfig::getColor() const { return color_; }

/**
 * This function sets the x coordinate of the vehicle.
 * 
 * @param x The x coordinate of the vehicle.
 */
void VehicleConfig::setXCoordinate(int x) { x_ = x; }

/**
 * This function sets the y coordinate of the vehicle.
 * 
 * @param y The y coordinate of the vehicle.
 */
void VehicleConfig::setYCoordinate(int y) { y_ = y; }

/**
 * This function sets the speed of the vehicle.
 * 
 * @param speed The speed of the vehicle in meters per second.
 */
void VehicleConfig::setSpeed(int speed) { speed_ = speed; }

/**
 * This function sets the size of the vehicle.
 * 
 * @param size The size of the vehicle.
 */
void VehicleConfig::setSize(float size) { size_ = size; }

/**
 * This function sets the type of the vehicle.
 * 
 * @param type The type of vehicle.
 */
void VehicleConfig::setVehicleType(const VehicleType& type) { type_ = type; }

/**
 * This function sets the color of the vehicle.
 * 
 * @param color The color of the vehicle.
 */
void VehicleConfig::setColor(const sf::Color& color) { color_ = color; }

/**
 * The constructor for the CameraConfig class.
 */
CameraConfig::CameraConfig() : RowObjectPlacementConfigBase(CONFIG_PARAMETERS_NUMBER_) {}

/**
 * It's a constructor for the CameraConfig class
 * 
 * @param x The x coordinate of the camera.
 * @param y The y coordinate of the camera.
 * @param rotation The rotation of the camera in degrees.
 * @param color The color of the camera.
 * @param size The size of the camera.
 */
CameraConfig::CameraConfig(int x, int y, int rotation, const sf::Color& color, float size)
    : RowObjectPlacementConfigBase(CONFIG_PARAMETERS_NUMBER_), x_(x), y_(y), rotation_(rotation), color_(color), size_(size) {}

/**
 * This function returns the x coordinate of the camera.
 * 
 * @return The x coordinate of the camera.
 */
int CameraConfig::getXCoordinate() const { return x_; }

/**
 * This function returns the y coordinate of the camera.
 * 
 * @return The y coordinate of the camera.
 */
int CameraConfig::getYCoordinate() const { return y_; }

/**
 * This function returns the angle of rotation.
 * 
 * @return The rotation of the camera.
 */
int CameraConfig::getRotation() const { return rotation_; }

/**
 * This function returns the size of the camera.
 * 
 * @return The size of the camera.
 */
float CameraConfig::getSize() const { return size_; }

/**
 * It returns the color of the camera.
 * 
 * @return The color of the camera.
 */
sf::Color CameraConfig::getColor() const { return color_; }

/**
 * This function sets the x coordinate of the camera.
 * 
 * @param x The x coordinate of the camera.
 */
void CameraConfig::setXCoordinate(int x) { x_ = x; }

/**
 * This function sets the y coordinate of the camera.
 * 
 * @param y The y coordinate of the camera.
 */
void CameraConfig::setYCoordinate(int y) { y_ = y; }

/**
 * This function sets the angle of rotation.
 * 
 * @param rotation The rotation of the camera. This is a value between 0 and 360.
 */
void CameraConfig::setRotation(int rotation) { rotation_ = rotation; }

/**
 * This function sets the size of the camera.
 * 
 * @param size The size of the camera.
 */
void CameraConfig::setSize(float size) { size_ = size; }

/**
 * This function sets the color of the camera.
 * 
 * @param color The color of the camera.
 */
void CameraConfig::setColor(const sf::Color& color) { color_ = color; }

/**
 * It takes a vector of strings each of which representing single value from the config file row and converts them into a CameraConfig object
 * 
 * @param vec a vector of strings that contains the parameters for the camera.
 * @param configs The container that holds all the configs.
 */
void CameraConfig::createConfigFromContainer(const std::vector<std::string>& vec, ConfigsContainer& configs)
{
    char* p_end;

    int x = std::strtol(vec[0].c_str(), &p_end, 10);
    int y = std::strtol(vec[1].c_str(), &p_end, 10);
    int rotation = std::strtol(vec[2].c_str(), &p_end, 10);
    int r =  std::strtol(vec[3].c_str(), &p_end, 10);
    int g =  std::strtol(vec[4].c_str(), &p_end, 10);
    int b =  std::strtol(vec[5].c_str(), &p_end, 10);
    int a =  std::strtol(vec[6].c_str(), &p_end, 10);
    auto color = sf::Color(r,g,b,a);
    float size = std::strtof(vec[7].c_str(), &p_end);

    configs.cameras_config_.push_back(CameraConfig(x, y, rotation, color, size));
}

