

#include "oracle.h"

int main()
{
    Oracle db;
    if(0 == db.Open("hs_user", "handsome", "192.168.3.43:1521/HS2008"))
    {
        std::cout<<"Connection to oracle established!"<<std::endl<<std::endl;

        if ( 0 != db.ExecuteNonQuery("insert into Person values('zz','zz','zz')"))
        {
            std::cout<<"Execute nonquery"<<std::endl;
        }

        ResultSet* results = db.ExecuteQuery("select Name from Person where CITY='kan'");

        if(results)
        {
            std::cout<<"Name ok"<<std::endl;
            if(results->next())
            {
                std::cout<<"Result: "<<results->getString(1)<<std::endl;
            }

            db.CloseResultSet(results);
        }

        results = db.ExecuteQuery("select * from Person");
        if(results)
        {
            std::cout<<std::endl<<"select * ok"<<std::endl;
            while(results->next())
            {
                std::string p1 = results->getString(1);
                std::string p2 = results->getString(2);
                std::cout<<"Result:"<<p1.c_str()<<" "<<p2.c_str()<<std::endl;
            }
            
            db.CloseResultSet(results);
        }

    }
}
