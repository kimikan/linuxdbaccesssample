
#ifndef _ORACLE_H_
#define _ORACLE_H_

#include <string>
#include <iostream>

#include <occi.h>

using namespace oracle::occi;

class Oracle 
{
public:
    Oracle();

    ~Oracle();

    void Close();

    int Open(const char* user, const char* pwd, const char* connection_string);
    
    int Commit();

    ResultSet* ExecuteQuery(const char* cmd);

    bool CloseResultSet(ResultSet* results);

    int ExecuteNonQuery(const char* cmd);

private:
    Environment*    _env;

    Connection*     _conn;

    Statement*      _stmt;
};

#endif
