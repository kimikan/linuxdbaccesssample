
//written by jkan
//2017-8-23

#ifndef _MYSQL_H_
#define _MYSQL_H_

#include <mysql.h>

class MySql
{
public:
    MySql();

    ~MySql();

    int Open(const char* server,int port, const char* dbName,
        const char* uid,const char *password);

    void Close();

    MYSQL_RES* ExecuteQuery(const char* cmd);

    void FreeQueryResult(MYSQL_RES* res);

    int GetFieldCount(MYSQL_RES* res);

    int ExecuteNonQuery(const char* cmd);

    /*
    int Bind (int column, int vartype , 
            DBINT varlen, BYTE* varaddr); 
    */
    MYSQL_ROW Next(MYSQL_RES* res);

private:
    MYSQL*  _conn;
};


#endif