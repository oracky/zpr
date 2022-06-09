#include <fstream>
#include <iostream>
#include <vector>
#include "Config.h"


ConfigBase::ConfigBase(){}
ConfigBase::~ConfigBase(){}
void ConfigBase::createConfigFromContainer(const std::vector<std::string>& vec, ConfigsContainer& configs){}

Config::Config(){}
Config::Config(const std::string& database_file, int refresh) : database_file_(database_file), measure_refresh_rate_ms_(refresh)
{
    // create hardcoded and tested road system
    setDefaultConfigsForRoads(8, RoadDirection::HORIZONTAL, 0, 0);
    setDefaultConfigsForRoads(2, RoadDirection::VERTICAL, 200, 0, 90, 360.0f, 20.0f, 100);
    setDefaultConfigsForRoads(1, RoadDirection::VERTICAL, 400, 0, 90, 800.0f, 20.0f, 100);
    setDefaultConfigsForRoads(2, RoadDirection::VERTICAL, 500, 0, 90, 360.0f, 20.0f, 100);
    setDefaultConfigsForRoads(2, RoadDirection::VERTICAL, 200, 460, 90, 320.0f, 20.0f, 100);
    setDefaultConfigsForRoads(2, RoadDirection::VERTICAL, 500, 460, 90, 320.0f, 20.0f, 100);
    setDefaultConfigsForRoads(1, RoadDirection::VERTICAL, 50, 280, 90, 320.0f, 20.0f, 100);

    // create hardcoded and tested vehicle env
    setDefaultConfigsForVehicles(DEFAULT_CAR_NUMBER, DEFAULT_TRUCK_NUMBER, DEFAULT_PEDESTRIAN_NUMBER);

    // create hardcoded and tested places for cameras
    setDefaultConfigsForCameras();
}
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

void Config::setDefaultConfigsForVehicles(int car_number, int truck_number, int pedestrian_number)
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

void Config::readConfig(const std::string& path, ConfigBase& config_instance)
{

    std::ifstream file;
    std::vector<std::string> row_values;
    std::string line;

    file.open(path);
    if (file.is_open())
    {

      while(getline(file, line, ',')) {
          std::cout << line << std::endl;
          row_values.push_back(line);
          if(row_values.size() == config_instance.config_parameters_number)
          {
              config_instance.createConfigFromContainer(row_values, configs_);
              row_values.clear();
          }

      }
      file.close();
    }
}

void Config::createConfigFromContainer(const std::vector<std::string>& vec, ConfigsContainer& config){}

RoadConfig::RoadConfig(){}
RoadConfig::RoadConfig(int x, int y, float length, float width, const Move& preferedMove, int rotation_degrees)
    : x_(x), y_(y), length_(length), width_(width), prefered_move_(preferedMove), rotation_degrees_(rotation_degrees) {}

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
void RoadConfig::createConfigFromContainer(const std::vector<std::string>& vec, ConfigsContainer& config)
{
    char * pEnd;
    int x = std::strtol(vec[0].c_str(), &pEnd, 10);
    int y = std::strtol(vec[1].c_str(), &pEnd, 10);
    float length = std::strtof(vec[2].c_str(), &pEnd);
    float width = std::strtof(vec[3].c_str(), &pEnd);
    RoadDirection direction = static_cast<RoadDirection>(std::strtol(vec[4].c_str(), &pEnd, 10));
    auto move = direction == RoadDirection::HORIZONTAL ? Move(MoveType::RIGHT, MoveType::NONE) : Move(MoveType::NONE, MoveType::DOWN);
    int rotation = std::strtol(vec[5].c_str(), &pEnd, 10);
    config.roads_config_.push_back(RoadConfig(x, y, length, width, move, rotation));
}

VehicleConfig::VehicleConfig(){}
VehicleConfig::VehicleConfig(int x, int y, int speed, const VehicleType& type, const sf::Color& color, float size)
    : x_(x), y_(y), speed_(speed), type_(type), color_(color), size_(size) {}

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
void VehicleConfig::createConfigFromContainer(const std::vector<std::string>& vec, ConfigsContainer& configs){/*TODO*/}

CameraConfig::CameraConfig(){}
CameraConfig::CameraConfig(int x, int y, int rotation, const sf::Color& color, float size)
    : x_(x), y_(y), rotation_(rotation), color_(color), size_(size) {}
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
void CameraConfig::createConfigFromContainer(const std::vector<std::string>& vec, ConfigsContainer& configs){/*TODO*/}

