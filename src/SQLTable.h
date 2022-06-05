#ifndef SQLTable_H
#define SQLTable_H

#include <string>
#include "VehicleType.hpp"

class SQLTable
{
public:
    SQLTable();
    virtual ~SQLTable();
    virtual std::string prepareInsertQuery() const = 0;
    virtual void updateID(int new_id) = 0;
};


#endif