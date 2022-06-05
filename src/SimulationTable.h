#ifndef SimulationTable_H
#define SimulationTable_H

#include "SQLTable.h"

class SimulationTable : public SQLTable
{
public:
    SimulationTable();
    SimulationTable(std::string& name);
    ~SimulationTable() = default;
    std::string prepareInsertQuery() const override;
    void updateID(int new_id) override; 
    unsigned int getID() const;
    std::string& getName();
    void setName(std::string& name);
    
private:
    unsigned int id_;
    std::string name_;
};


#endif