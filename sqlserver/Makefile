Server : config.o sqlserver.o main.o
	g++ config.o sqlserver.o main.o -o main -L/usr/local/freetds/lib -lsybdb -I/usr/local/freetds/inc
config.o : config.cpp
	g++ -c config.cpp -o config.o 
sqlserver.o : sqlserver.cpp
	g++ -c sqlserver.cpp -o sqlserver.o 
main.o : main.cpp
	g++ -c main.cpp -o main.o 
clean : 
	rm config.o sqlserver.o main.o
