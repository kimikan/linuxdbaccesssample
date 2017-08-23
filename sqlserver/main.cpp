#include <iostream>

using namespace std;

#include "common.h"

int main()
{
    SqlServer sql;

    int ret = sql.Open("139.196.143.124:1433", "JYDB", "sa", "Hznb@123");

    if (0 == ret)
    {
        ret = sql.ExecuteQuery("select * from dbo.QT_DailyQuote;");

        if (ret == 0)
        {
            long long id;
            int code;
            sql.Bind(1, BIGINTBIND, (DBINT)0, (BYTE*)&id);  
            sql.Bind(2, INTBIND, (DBBIGINT)0, (BYTE*)&code);  
            cout<<"ID\tName"<<endl; 

            int index = 0;
            while (sql.Next() != NO_MORE_ROWS)
            {             
                if (++index > 20)
                {
                    break;
                }
                             
                std::cout<<"ID:"<<id<<" Code:"<<code<<std::endl; 
            } 
        }
        std::cout<<"Ok"<<std::endl;
    }

    return 0;
}
