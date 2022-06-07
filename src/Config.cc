#include "Config.h"


Config::Config(int pedestrian_number, int car_number, int truck_number, int road_number,
 const std::vector<RoadConfig>& roads_config,  const std::vector<VehicleConfig>& vehicles_config)
    : pedestrian_number_(pedestrian_number), car_number_(car_number), truck_number_(truck_number), road_number_(road_number),
      roads_config_(roads_config), vehicles_config_(vehicles_config) {}
int Config::getCarNumber() const { return car_number_; }
int Config::getPedestrianNumber() const { return pedestrian_number_; }
int Config::getTruckNumber() const { return truck_number_; }
int Config::getRoadNumber() const { return road_number_; }
std::vector<RoadConfig> Config::getRoadsConfig() const { return roads_config_; }
std::vector<VehicleConfig> Config::getVehiclesConfig() const { return vehicles_config_; }
void Config::setCarNumber(int number) { car_number_ = number; }
void Config::setPedestrianNumber(int number) { pedestrian_number_ = number; }
void Config::setTruckNumber(int number) { truck_number_ = number; }
void Config::setRoadNumber(int number) { road_number_ = number; }
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

