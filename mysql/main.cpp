
//written by kimikan, 
//to show how to 
/* Standard C++ includes */
//tcp://139.196.73.96:3306", "root", "--passok--");
/* Connect to the MySQL test database */


#include <mysql.h>

#include <iostream>

#include "mysql.h"

int main(void) 
{
    /* db configure*/
    const char *server = "139.196.73.96";
    const char *user = "root";
    const char *password = "--passok--";
    const char *database = "nb";
    const int  port=3306;   

    MySql mysql;
    int error = mysql.Open(server, port, database, user, password);
    if (0 == error)
    {
        MYSQL_RES * result = mysql.ExecuteQuery("select * from b_admin_role");

        if (result != NULL)
        {
            int count = mysql.GetFieldCount(result);

            while(true)
            {
                MYSQL_ROW row = mysql.Next(result);

                if(row == NULL)
                {
                    break;
                }

                for(int i = 0; i < count; ++i)
                {
                    std::cout<<row[i]<<" ";
                }
                std::cout<<std::endl;
            }
            mysql.FreeQueryResult(result);
        }
        else
        {
            std::cout<<"Query failed"<<std::endl;
        }
    }
    else
    {
        std::cout<<"Son of the bitch"<<error<<std::endl;
    }

    return 0;

}
