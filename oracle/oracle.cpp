
#include "oracle.h"

#include <iostream>

//constructor function
Oracle::Oracle()
{
    _conn = NULL;
    _env = NULL;
    _stmt = NULL;
}

void Oracle::Close()
{
    if(_env == NULL || _conn == NULL)
    {
        return;
    }

    try
    {
        if(_stmt != NULL)
        {
            _conn->terminateStatement (_stmt);
            _stmt = NULL;
        }

        _env->terminateConnection(_conn);
        _conn = NULL;
        Environment::terminateEnvironment(_env);
        _conn = NULL;
        
    }
    catch(SQLException ex)
    {
        std::cout<<"Exception:Code "<<ex.getErrorCode()
                 <<", Message - "<<ex.getMessage()<<std::endl;
    }
}

//destructor function
Oracle::~Oracle()
{
    Close();
}

int Oracle::Open(const char* user, const char* pwd
               , const char* connection_string)
{
    //close firstly
    Close();

    try
    {
        _env = Environment::createEnvironment(Environment::OBJECT);
        _conn = _env->createConnection(user,pwd,connection_string);
        _stmt = _conn->createStatement();
    }
    catch (SQLException ex)
    {
        std::cout<<"Exception:Code - "<<ex.getErrorCode()
            <<", Message - "<<ex.getMessage()<<std::endl;
        return -1;
    }

    return 0;
}

int Oracle::Commit()
{
    if(_env == NULL || _conn == NULL)
    {
        return 0;
    }

    try
    {
        _conn->commit();
    }
    catch(SQLException ex)
    {
        std::cout<<"Exception: Code - "<<ex.getErrorCode()
                 <<", Message - "<<ex.getMessage()<<std::endl;
        return -1;
    }

    return 0;
}

ResultSet* Oracle::ExecuteQuery(const char* cmd)
{
    if(_env == NULL || _conn == NULL)
    {
        return NULL;
    }

    if(cmd == NULL || _stmt == NULL)
    {
        return NULL;
    }

    try
    {
        _stmt->setSQL(cmd);

        return _stmt->executeQuery();
    }
    catch(SQLException ex)
    {
        std::cout<<"Exception: Code - "<<ex.getErrorCode()
                 <<",Message-"<<ex.getMessage()<<std::endl;
    }
    
    return NULL;
}

bool Oracle::CloseResultSet(ResultSet* results)
{
    if(_env == NULL || _conn == NULL)
    {
        return false;
    }

    if(results == NULL || _stmt == NULL)
    {
        return false;
    }

    _stmt->closeResultSet(results);

    return true;
}

int Oracle::ExecuteNonQuery(const char* cmd)
{
    if(_env == NULL || _conn == NULL)
    {
        return 0;
    }

    if(cmd == NULL || _stmt == NULL)
    {
        return 0;
    }

    try
    {
        _stmt->setSQL(cmd);

        _stmt->executeUpdate();
        return 0;
    }
    catch(SQLException ex)
    {
        std::cout<<"Exception: Code - "<<ex.getErrorCode()
                 <<", Message - "<<ex.getMessage()<<std::endl;
    }
    
    return -2;
}
