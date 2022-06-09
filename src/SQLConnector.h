#ifndef SQLConnector_H
#define SQLConnector_H

#include <sqlite3.h>
#include "SQLTable.h"

class SQLConnector
{
public:
    SQLConnector(const std::string& filepath);
    ~SQLConnector();
    sqlite3* getDatabaseConnection() const;
    void insertData(SQLTable& table);
private:
    std::string filepath_;
    sqlite3* db_; 
    char* error_message_;

    static int callback(void *notUsed, int argc, char **argv, char **az_col_name);
};

#endif