#ifndef CameraTable_H
#define CameraTable_H

#include "SQLTable.h"

class CameraTable : public SQLTable
{
public:
    CameraTable();
    CameraTable(int x, int y, double visibility, double precision);
    ~CameraTable() = default;
    std::string prepareInsertQuery() const;
    void updateID(int new_id) override; 
    unsigned int getID() const;
    int getXCoordinate() const;
    void setXCoordinate(int x);
    int getYCoordinate() const;
    void setYCoordinate(int y);
    double getVisibility() const;
    void setVisibility(double visibility);
    double getPrecision() const;
    void setPrecision(double precision);

private:
    unsigned int id_;
    int x_;
    int y_;
    double visibility_;
    double precision_;

    bool isPrecisionValid(double precision);
};

#endif