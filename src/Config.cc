#include "Config.h"


Config::Config(int pedestrian_number, int car_number, int truck_number, int road_number, std::string database_file,
 const std::vector<RoadConfig>& roads_config,  const std::vector<VehicleConfig>& vehicles_config,
 const std::vector<CameraConfig>& cameras_config)
    : pedestrian_number_(pedestrian_number), car_number_(car_number), truck_number_(truck_number), road_number_(road_number),
      database_file_(database_file), roads_config_(roads_config), vehicles_config_(vehicles_config), cameras_config_(cameras_config) {}

int Config::getCarNumber() const { return car_number_; }
int Config::getPedestrianNumber() const { return pedestrian_number_; }
int Config::getTruckNumber() const { return truck_number_; }
int Config::getRoadNumber() const { return road_number_; }
std::string Config::getDatabaseFilePath() const { return database_file_; }
std::vector<RoadConfig> Config::getRoadsConfig() const { return roads_config_; }
std::vector<VehicleConfig> Config::getVehiclesConfig() const { return vehicles_config_; }
std::vector<CameraConfig> Config::getCamerasConfig() const { return cameras_config_; }
void Config::setCarNumber(int number) { car_number_ = number; }
void Config::setPedestrianNumber(int number) { pedestrian_number_ = number; }
void Config::setTruckNumber(int number) { truck_number_ = number; }
void Config::setRoadNumber(int number) { road_number_ = number; }
void Config::setDatabaseilePath(const std::string& path) { database_file_ = path; }
void Config::setRoadsConfig(const std::vector<RoadConfig>& roads_config) { roads_config_ = roads_config;}
void Config::setVehiclesConfig(const std::vector<VehicleConfig>& vehicles_config) { vehicles_config_ = vehicles_config;}

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

