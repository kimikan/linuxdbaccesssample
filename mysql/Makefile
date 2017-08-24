Server : mysql.o main.o
	g++ mysql.o main.o -o main -L./connector/lib -lmysqlclient 

mysql.o : mysql.cpp
	g++ -c mysql.cpp -o mysql.o 
main.o : main.cpp
	g++ -c main.cpp -o main.o -I./connector/include
clean : 
	rm mysql.o main.o
