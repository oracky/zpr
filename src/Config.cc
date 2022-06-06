#include "Config.h"


Config::Config(int pedestrian_number, int car_number, int truck_number, int road_number)
    : pedestrian_number_(pedestrian_number), car_number_(car_number), truck_number_(truck_number), road_number_(road_number) {}
int Config::getCarNumber() const { return car_number_; }
int Config::getPedestrianNumber() const { return pedestrian_number_; }
int Config::getTruckNumber() const { return truck_number_; }
int Config::getRoadNumber() const { return road_number_; }
void Config::setCarNumber(int number) { car_number_ = number; }
void Config::setPedestrianNumber(int number) { pedestrian_number_ = number; }
void Config::setTruckNumber(int number) { truck_number_ = number; }
void Config::setRoadNumber(int number) { road_number_ = number; }