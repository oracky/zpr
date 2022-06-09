//#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif
#include "SQLConnector.h"

SQLConnector::SQLConnector(const std::string& filepath)
{
    sqlite3 *db;
    int connection_status = sqlite3_open(filepath.c_str(), &db);
   
    if(!connection_status)
    {
        #ifdef DEBUG
            std::cout << "Openning database... " <<  std::endl;
        #endif
        db_ = db;
    }
        
    else
    {
        #ifdef DEBUG
            const char* err = sqlite3_errmsg(db);
            std::cout << "Can't open database: " << err << std::endl;
        #endif
        db_ = nullptr;
    }

        
}
SQLConnector::~SQLConnector() { sqlite3_close(db_); }


sqlite3* SQLConnector::getDatabaseConnection() const { return db_; }

void SQLConnector::insertData(SQLTable& table)
{
    std::string query = table.prepareInsertQuery();
    #ifdef DEBUG
        std::cout << query << std::endl;
    #endif
    
    int call_status;

    call_status = sqlite3_exec(db_, query.c_str(), SQLConnector::callback, 0, &error_message_);

    if ( call_status != SQLITE_OK )
    {
        #ifdef DEBUG
            std::cout << "Couldn't execute the query: " << error_message_ << std::endl;
        #endif
        sqlite3_free(error_message_);
    }

    else {
        table.updateID(sqlite3_last_insert_rowid(db_));
    } 

    
}

int SQLConnector::callback(void *notUsed, int argc, char **argv, char **az_col_name) 
{
    #ifdef DEBUG
            for(int i = 0; i<argc; i++) 
            {
                std::cout << az_col_name[i] << " = " << argv[i] ? argv[i] : "NULL";
            }
    #endif
    return 0;
}


