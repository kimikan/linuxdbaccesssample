Server : oracle.o main.o
	g++ oracle.o main.o -o main -L./instantclient -locci -lclntsh -lipc1 -lmql1 -lnnz12 -lociei -lons -loramysql12 -lclntshcore

oracle.o : oracle.cpp
	g++ -c oracle.cpp -o oracle.o -I./sdk/include
main.o : main.cpp
	g++ -c main.cpp -o main.o -I./sdk/include
clean : 
	rm oracle.o main.o
