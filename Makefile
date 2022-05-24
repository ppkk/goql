default: all	

all: c-main
	
greek.o: greek.h greek.cc
	g++ -c -o greek.o greek.cc 

main.o: greek.h main.cc
	g++ -c -o main.o main.cc 

c-main: greek.o main.o
	g++ -o c-main greek.o main.o -lQuantLib

clean:
	rm *.o c-main
