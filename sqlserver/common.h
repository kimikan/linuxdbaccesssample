
#ifndef _COMMON_H_
#define _COMMON_H_


#include <sybdb.h>
#include <iostream>

class SqlServer 
{
public:
    SqlServer();

    int Open(const char* server,const char* dbName,
        const char* uid,const char *password);

    void Close();

    int ExecuteQuery(const char* cmd);

    int ExecuteNonQuery(const char* cmd);

    RETCODE Bind (int column, int vartype , 
            DBINT varlen, BYTE* varaddr); 

    RETCODE Next();

    ~SqlServer();

private:
    DBPROCESS*  _db;
};

#endif