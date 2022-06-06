#ifndef Config_H
#define Config_H

class Config
{
public:
    Config(int pedestrian_number, int car_number, int truck_number, int road_number);
    int getPedestrianNumber() const;
    int getCarNumber() const;
    int getTruckNumber() const;
    int getRoadNumber() const;
    void setPedestrianNumber(int number);
    void setCarNumber(int number);
    void setTruckNumber(int number);
    void setRoadNumber(int number);

private:
    int pedestrian_number_;
    int car_number_;
    int truck_number_;
    int road_number_;
};


// class RoadConfig
// {
// public:

// }

#endif