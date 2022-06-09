#ifndef Config_H
#define Config_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "Move.h"
#include "Road.h"
#include "VehicleType.hpp"


class RoadConfig;
class VehicleConfig;
class CameraConfig;

struct ConfigsContainer
{
    std::vector<RoadConfig> roads_config_;
    std::vector<VehicleConfig> vehicles_config_;
    std::vector<CameraConfig> cameras_config_;
};

class ConfigBase
{
public:
    ConfigBase();
    ConfigBase(int config_parameters_number);
    virtual ~ConfigBase();
    int getConfigParametersNumber() const;
private:
    int config_parameters_number_;
};

class RowObjectPlacementConfigBase : public ConfigBase
{
public:
    RowObjectPlacementConfigBase();
    RowObjectPlacementConfigBase(int config_parameters_number);
    virtual ~RowObjectPlacementConfigBase();
    virtual void createConfigFromContainer(const std::vector<std::string>& vec, ConfigsContainer& configs);
};

class RoadConfig : public RowObjectPlacementConfigBase
{
public:
    RoadConfig();
    RoadConfig(int x, int y, float length, float width, const Move& preferedMove, int rotation_degrees=0);
    int getXCoordinate() const;
    int getYCoordinate() const;
    int getRotation() const;
    float getLength() const;
    float getWidth() const;
    Move getPreferedMove() const;
    void setXCoordinate(int x);
    void setYCoordinate(int y);
    void setRotation(int degrees);
    void setLength(float length);
    void setWidth(float width);
    void setPreferedMove(const Move& prefered_move);
    void createConfigFromContainer(const std::vector<std::string>& vec, ConfigsContainer& configs) override;

private:
    static constexpr int CONFIG_PARAMETERS_NUMBER_ = 6;
    int x_;
    int y_;
    int rotation_degrees_;
    float length_;
    float width_;
    Move prefered_move_;
};

class VehicleConfig : public ConfigBase
{
public:
    VehicleConfig();
    VehicleConfig(int x, int y, int speed, const VehicleType& type, const sf::Color& color, float size);
    int getXCoordinate() const;
    int getYCoordinate() const;
    int getSpeed() const;
    float getSize() const;
    VehicleType getVehicleType() const;
    sf::Color getColor() const;
    void setXCoordinate(int x);
    void setYCoordinate(int y);
    void setSize(float size);
    void setSpeed(int speed);
    void setVehicleType(const VehicleType& type);
    void setColor(const sf::Color& color);

private:
    static constexpr int CONFIG_PARAMETERS_NUMBER_ = 3;
    int x_;
    int y_;
    int speed_;
    float size_;
    VehicleType type_;
    sf::Color color_;
};

class CameraConfig : public RowObjectPlacementConfigBase
{
public:
    CameraConfig();
    CameraConfig(int x, int y, int rotation, const sf::Color& color, float size);
    int getXCoordinate() const;
    int getYCoordinate() const;
    int getRotation() const;
    float getSize() const;
    sf::Color getColor() const;
    void setXCoordinate(int x);
    void setYCoordinate(int y);
    void setRotation(int rotation);
    void setSize(float size);
    void setColor(const sf::Color& color);
    void createConfigFromContainer(const std::vector<std::string>& vec, ConfigsContainer& configs) override;

private:
    static constexpr int CONFIG_PARAMETERS_NUMBER_ = 8;
    int x_;
    int y_;
    int rotation_;
    float size_;
    sf::Color color_;
};

class Config
{
public:
    Config(int argc, char** argv, bool all_default=false);
    Config(const std::string& database_file, int refresh_rate,
     const std::vector<RoadConfig>& roads_config,
     const std::vector<VehicleConfig>& vehicles_config,
     const std::vector<CameraConfig>& cameras_config);
    ~Config();
     
    int getRefreshRate() const;
    std::string getDatabaseFilePath() const;
    std::vector<RoadConfig> getRoadsConfig() const;
    std::vector<VehicleConfig> getVehiclesConfig() const;
    std::vector<CameraConfig> getCamerasConfig() const;
    void setRefreshRate(int refresh);
    void setDatabaseilePath(const std::string& path);
    void setRoadsConfig(const std::vector<RoadConfig>& roads_config);
    void setVehiclesConfig(const std::vector<VehicleConfig>& vehciles_config);
    void readConfig(const std::string& path, RowObjectPlacementConfigBase& config_instance);
    void readConfig(const std::string& path, const VehicleConfig& vehicle_config);
    void readCamerasConfig(const std::string& path);
    void readVehiclesConfig(const std::string& path);
    void parseInputArgs(int argc, char** argv);

private:
    static constexpr int DEFAULT_CAR_NUMBER = 20;
    static constexpr int DEFAULT_TRUCK_NUMBER = 20;
    static constexpr int DEFAULT_PEDESTRIAN_NUMBER = 20;
    static constexpr int DEFAULT_REFRESH_RATE = 500;
    static constexpr auto DB_PATH = "../zpr.db";
    static constexpr auto ROADS_PATH = "../roads.cfg";
    static constexpr auto VEHICLES_PATH = "../vehicles.cfg";
    static constexpr auto CAMERAS_PATH = "../cameras.cfg";
    static constexpr int CAR_SPEED = 9;
    static constexpr int TRUCK_SPEED = 7;
    static constexpr int PEDESTRIAN_SPEED = 2;
    int pedestrian_number_;
    int car_number_;
    int truck_number_;
    int road_number_;
    int measure_refresh_rate_ms_;
    std::string database_file_;
    std::string roads_file_;
    std::string vehicle_file_;
    std::string cameras_file_;
    ConfigsContainer configs_;

    void setDefaultConfigsForRoads(int roads_number, RoadDirection direction, int initial_x, int initial_y,  int rotation=0, float length=800.0f, float width=20.f, int margin=100);
    void setConfigsForVehicles(int car_number, int truck_number, int pedestrian_number);
    void setDefaultConfigsForCameras();
    void setAllDefaults();
};




#endif