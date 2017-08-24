

//written by jkan
//2017-8-23, purpose for niubang trade 
//db access wrapper


//https://dev.mysql.com/doc/refman/5.6/en/mysql-field-count.html
#include "mysql.h"

#include <iostream>
#include <my_global.h>

MySql::MySql()
{
    _conn = mysql_init(NULL);
}

MySql::~MySql()
{
    //Close anyway
    Close();
}

//open the database anyway
int MySql::Open(const char* server,int port, const char* dbName,
        const char* uid,const char *password)
{
    if(_conn == NULL)
    {
        return -1;
    }

    if (!mysql_real_connect(_conn, server,
            uid, password, dbName, port, NULL, 0)) {
        
        std::cerr<<"connect error: %s"<<mysql_error(_conn)<<std::endl;

        return (-2);
    }

    return 0;
}

void MySql::Close()
{
    if (_conn != NULL)
    {
        mysql_close(_conn);
        _conn = NULL;
    }
}

int MySql::GetFieldCount(MYSQL_RES* result)
{
    return mysql_num_fields(result);
}

//release the result dataset
void MySql::FreeQueryResult(MYSQL_RES* result)
{
    if(result == NULL)
    {
        return;
    }

    mysql_free_result(result);
}

MYSQL_RES* MySql::ExecuteQuery(const char* cmd)
{
    if(_conn == NULL || cmd == NULL)
    {
        return NULL;
    }

    /* send SQL query */
    if (mysql_query(_conn, cmd)) 
    {
        std::cerr<<mysql_error(_conn)<<std::endl;
        return NULL;
    }

    return mysql_use_result(_conn);
}

MYSQL_ROW MySql::Next(MYSQL_RES* result)
{
    if (result == NULL)
    {
        return NULL;
    }

    return mysql_fetch_row(result);
}

//execute non query
//means query without result
int MySql::ExecuteNonQuery(const char* cmd)
{
    if(_conn == NULL || cmd == NULL)
    {
        return -1;
    }

    /* send SQL query */
    if (mysql_query(_conn, cmd)) 
    {
        std::cerr<<mysql_error(_conn)<<std::endl;
        return -2;
    }

    return mysql_field_count(_conn);
}