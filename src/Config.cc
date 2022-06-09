#include <fstream>
#include <iostream>
#include <vector>
#include "Config.h"


ConfigBase::ConfigBase() {}
ConfigBase::ConfigBase(int config_parameters_number) : config_parameters_number_(config_parameters_number) {}
ConfigBase::~ConfigBase() {}
int ConfigBase::getConfigParametersNumber() const { return config_parameters_number_; }

RowObjectPlacementConfigBase::RowObjectPlacementConfigBase(){}
RowObjectPlacementConfigBase::RowObjectPlacementConfigBase(int config_parameters_number) : ConfigBase(config_parameters_number) {}
RowObjectPlacementConfigBase::~RowObjectPlacementConfigBase(){}
void RowObjectPlacementConfigBase::createConfigFromContainer(const std::vector<std::string>& vec, ConfigsContainer& configs){}


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

// Config::Config(const std::string& database_file, int refresh,
//      const std::string& roads_config_file,
//      const std::string& vehicles_config_file,
//      const std::string& cameras_config_file) : database_file_(database_file), measure_refresh_rate_ms_(refresh)
// {
//     configs_ = ConfigsContainer();
//     auto r_config = RoadConfig();
//     auto v_config = VehicleConfig();
//     auto c_config = CameraConfig();
//     readConfig(roads_config_file, r_config);
//     readConfig(vehicles_config_file, v_config);
//     readConfig(cameras_config_file, c_config);
// }

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
Config::~Config(){}

int Config::getRefreshRate() const { return measure_refresh_rate_ms_; }
std::string Config::getDatabaseFilePath() const { return database_file_; }
std::vector<RoadConfig> Config::getRoadsConfig() const { return configs_.roads_config_; }
std::vector<VehicleConfig> Config::getVehiclesConfig() const { return configs_.vehicles_config_; }
std::vector<CameraConfig> Config::getCamerasConfig() const { return configs_.cameras_config_; }
void Config::setRefreshRate(int refresh) { measure_refresh_rate_ms_ = refresh; }
void Config::setDatabaseilePath(const std::string& path) { database_file_ = path; }
void Config::setRoadsConfig(const std::vector<RoadConfig>& roads_config) { configs_.roads_config_ = roads_config;}
void Config::setVehiclesConfig(const std::vector<VehicleConfig>& vehicles_config) { configs_.vehicles_config_ = vehicles_config;}

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

void Config::readConfig(const std::string& path, const VehicleConfig& vehicle_config)
{
    std::ifstream file;
    std::vector<std::string> row_values;
    std::string line;
    char* pEnd;

    file.open(path);
    if (file.is_open())
    {
      while(getline(file, line, ',')) {
          row_values.push_back(line);
          if(row_values.size() == vehicle_config.getConfigParametersNumber())
          {
              setConfigsForVehicles(std::strtol(row_values[0].c_str(), &pEnd, 10), std::strtol(row_values[1].c_str(), &pEnd, 10), std::strtol(row_values[2].c_str(), &pEnd, 10));
              break;
          }
      }
      file.close();
    }
}

void Config::parseInputArgs(int argc, char** argv)
{
    char* pEnd;
    
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
                  << "Provided " << argv[2] << " as a refresh rate for measurements and database saving. Other configuration information is set to default." << std::endl;
        database_file_ = argv[1];
        measure_refresh_rate_ms_ = std::strtol(argv[2], &pEnd, 10);
        break;
    case 4:
        std::cout << "Provided " << argv[1] << " as a path to database." << std::endl
                  << "Provided " << argv[2] << " as a refresh rate for measurements and database saving." << std::endl
                  << "Provided " << argv[3] << " as a path to roads config. Other configuration information is set to default." << std::endl;
        database_file_ = argv[1];
        measure_refresh_rate_ms_ = std::strtol(argv[2], &pEnd, 10);
        roads_file_ = argv[3];
        break;
    case 5:
        std::cout << "Provided " << argv[1] << " as a path to database." << std::endl
                  << "Provided " << argv[2] << " as a refresh rate for measurements and database saving." << std::endl
                  << "Provided " << argv[3] << " as a path to roads config. " << std::endl
                  << "Provided " << argv[4] << " as a path to vehciles config. Other configuration information is set to default." << std::endl;
        database_file_ = argv[1];
        measure_refresh_rate_ms_ = std::strtol(argv[2], &pEnd, 10);
        roads_file_ = argv[3];
        vehicle_file_ = argv[4];
        break;
    case 6:
        std::cout << "Provided " << argv[1] << " as a path to database." << std::endl
                  << "Provided " << argv[2] << " as a refresh rate for measurements and database saving." << std::endl
                  << "Provided " << argv[3] << " as a path to roads config."  << std::endl
                  << "Provided " << argv[4] << " as a path to vehciles config." << std::endl
                  << "Provided " << argv[5] << " as a path to cameras config." << std::endl;
        database_file_ = argv[1];
        measure_refresh_rate_ms_ = std::strtol(argv[2], &pEnd, 10);
        roads_file_ = argv[3];
        vehicle_file_ = argv[4];
        cameras_file_ = argv[5];
        break;
    default:
        std::cout << "Wrong usage. Try: ./Main [db_path] [refresh_rate] [roads_cfg_file] [vehicles_cfg_file] [cameras_cfg_file]." << std::endl;
        exit(1);
    }
}


RoadConfig::RoadConfig() : RowObjectPlacementConfigBase(CONFIG_PARAMETERS_NUMBER_) {}
RoadConfig::RoadConfig(int x, int y, float length, float width, const Move& preferedMove, int rotation_degrees)
    : RowObjectPlacementConfigBase(CONFIG_PARAMETERS_NUMBER_), x_(x), y_(y), length_(length), width_(width), prefered_move_(preferedMove), rotation_degrees_(rotation_degrees) {}

int RoadConfig::getXCoordinate() const { return x_; }
int RoadConfig::getYCoordinate() const { return y_; }
int RoadConfig::getRotation() const { return rotation_degrees_; }
float RoadConfig::getLength() const { return length_; }
float RoadConfig::getWidth() const { return width_; }
Move RoadConfig::getPreferedMove() const { return prefered_move_; }
void RoadConfig::setXCoordinate(int x) { x_ = x; }
void RoadConfig::setYCoordinate(int y) { y_ = y; }
void RoadConfig::setRotation(int degrees) { rotation_degrees_ = degrees; }
void RoadConfig::setLength(float length) { length_ = length; }
void RoadConfig::setWidth(float width) { width_ = width; }
void RoadConfig::setPreferedMove(const Move& prefered_move) { prefered_move_ = prefered_move; }
void RoadConfig::createConfigFromContainer(const std::vector<std::string>& vec, ConfigsContainer& configs)
{
    std::cout << "Road config" << std::endl;
    // configs.roads_config_.clear();
    char* pEnd;

    int x = std::strtol(vec[0].c_str(), &pEnd, 10);
    int y = std::strtol(vec[1].c_str(), &pEnd, 10);
    float length = std::strtof(vec[2].c_str(), &pEnd);
    float width = std::strtof(vec[3].c_str(), &pEnd);
    RoadDirection direction = static_cast<RoadDirection>(std::strtol(vec[4].c_str(), &pEnd, 10));
    auto move = direction == RoadDirection::HORIZONTAL ? Move(MoveType::RIGHT, MoveType::NONE) : Move(MoveType::NONE, MoveType::DOWN);
    int rotation = std::strtol(vec[5].c_str(), &pEnd, 10);
    configs.roads_config_.push_back(RoadConfig(x, y, length, width, move, rotation));
}

VehicleConfig::VehicleConfig() : ConfigBase(CONFIG_PARAMETERS_NUMBER_) {}
VehicleConfig::VehicleConfig(int x, int y, int speed, const VehicleType& type, const sf::Color& color, float size)
    : ConfigBase(CONFIG_PARAMETERS_NUMBER_), x_(x), y_(y), speed_(speed), type_(type), color_(color), size_(size) {}

int VehicleConfig::getXCoordinate() const { return x_; }
int VehicleConfig::getYCoordinate() const { return y_; }
int VehicleConfig::getSpeed() const { return speed_; }
float VehicleConfig::getSize() const { return size_; }
VehicleType VehicleConfig::getVehicleType() const { return type_; }
sf::Color VehicleConfig::getColor() const { return color_; }

void VehicleConfig::setXCoordinate(int x) { x_ = x; }
void VehicleConfig::setYCoordinate(int y) { y_ = y; }
void VehicleConfig::setSpeed(int speed) { speed_ = speed; }
void VehicleConfig::setSize(float size) { size_ = size; }
void VehicleConfig::setVehicleType(const VehicleType& type) { type_ = type; }
void VehicleConfig::setColor(const sf::Color& color) { color_ = color; }

CameraConfig::CameraConfig() : RowObjectPlacementConfigBase(CONFIG_PARAMETERS_NUMBER_) {}
CameraConfig::CameraConfig(int x, int y, int rotation, const sf::Color& color, float size)
    : RowObjectPlacementConfigBase(CONFIG_PARAMETERS_NUMBER_), x_(x), y_(y), rotation_(rotation), color_(color), size_(size) {}
int CameraConfig::getXCoordinate() const { return x_; }
int CameraConfig::getYCoordinate() const { return y_; }
int CameraConfig::getRotation() const { return rotation_; }
float CameraConfig::getSize() const { return size_; }
sf::Color CameraConfig::getColor() const { return color_; }

void CameraConfig::setXCoordinate(int x) { x_ = x; }
void CameraConfig::setYCoordinate(int y) { y_ = y; }
void CameraConfig::setRotation(int rotation) { rotation_ = rotation; }
void CameraConfig::setSize(float size) { size_ = size; }
void CameraConfig::setColor(const sf::Color& color) { color_ = color; }
void CameraConfig::createConfigFromContainer(const std::vector<std::string>& vec, ConfigsContainer& configs)
{
    char* pEnd;

    int x = std::strtol(vec[0].c_str(), &pEnd, 10);
    int y = std::strtol(vec[1].c_str(), &pEnd, 10);
    int rotation = std::strtol(vec[2].c_str(), &pEnd, 10);
    int r =  std::strtol(vec[3].c_str(), &pEnd, 10);
    int g =  std::strtol(vec[4].c_str(), &pEnd, 10);
    int b =  std::strtol(vec[5].c_str(), &pEnd, 10);
    int a =  std::strtol(vec[6].c_str(), &pEnd, 10);
    auto color = sf::Color(r,g,b,a);
    float size = std::strtof(vec[7].c_str(), &pEnd);

    configs.cameras_config_.push_back(CameraConfig(x, y, rotation, color, size));
}

