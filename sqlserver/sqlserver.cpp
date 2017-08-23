
#include <sybdb.h>
#include <iostream>
#include "common.h"

SqlServer::SqlServer()
{
    _db = NULL;
}

void SqlServer::Close()
{
    if (_db && _db != FAIL)
    {
        dbclose(_db);
        _db = NULL;
    }
}

SqlServer::~SqlServer()
{
    //close anyway
    Close();
}

int SqlServer::Open(const char* server,const char* dbName
    ,const char* uid,const char *password)
{
    dbinit();	
	LOGINREC *login = dblogin();  
    DBSETLUSER(login, uid);         
    DBSETLPWD(login, password);  
    
    //open the server provider
    _db = dbopen(login, server);	
	if(_db == FAIL)
	{
		std::cout<<"connect sql server failed!"<<std::endl;
		return -1;
	}

	std::cout<<"connect sql server success!"<<std::endl;
	if(dbuse(_db, dbName) == FAIL) 
	{ 
		std::cout<<"connect database failed!"<<std::endl;
		return -1;
	}

    return 0;
}

//execute query
//after query, should use bind & nextrow to
//retrieve the data
/*
    dbbind(_db, 1, CHARBIND, (DBINT)0, (BYTE*)szID);  
    dbbind(_db, 2, CHARBIND, (DBCHAR)0, (BYTE*)szName);  
    cout<<"ID\tName"<<endl; 
    while (dbnextrow(client->dbprocess) != NO_MORE_ROWS)
    {                          
        cout<<szID<<"\t"; 
        cout<<szName<<endl; 
    }
*/ 
int SqlServer::ExecuteQuery(const char* cmd)
{
    if(ExecuteNonQuery(cmd) == 0)
	{
		RETCODE recode=dbresults(_db);

		return recode == SUCCEED ? 0 : 1;
	}
	else
	{
		return -1;
    }

    return 0;
}

//bind you son of the bitch
RETCODE SqlServer::Bind(int column, int vartype , 
            DBINT varlen, BYTE* varaddr)
{
    if (_db == NULL || _db == FAIL)
    {
        return FAIL;
    }

    return dbbind(_db, column, vartype, varlen, varaddr);
}

//enum the result
RETCODE SqlServer::Next()
{
    if(_db == NULL || _db == FAIL)
    {
        return FAIL;
    }

    return dbnextrow(_db);
}


//execute non query
//delete, update, etc
int SqlServer::ExecuteNonQuery(const char* cmd)
{
    if (cmd == NULL)
    {
        return -2;
    }

    if (_db == NULL || _db == FAIL)
    {
        return -1;
    }

    RETCODE recode;
	recode = dbcmd(_db, cmd);
	if(recode==FAIL)
	{
		return -1;
	}

	recode=dbsqlexec(_db);
	
    std::cout<<cmd<<"-->"<<recode<<std::endl;

    return recode==SUCCEED ? 0 : -3;
}