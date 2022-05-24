default: all	

all: tests/greek
	
src/greek.o: include/greek.hxx src/greek.cc
	g++ -c -Iinclude -o src/greek.o src/greek.cc

lib/libgreek.a: src/greek.o
	ar rcs lib/libgreek.a src/greek.o

tests/main.o: include/greek.hxx tests/main.cc
	g++ -c -o tests/main.o tests/main.cc -Iinclude

tests/greek: lib/libgreek.a tests/main.o
	g++ -o tests/greek tests/main.o -Llib -lgreek

c-main: greek.o main.o
	g++ -o c-main greek.o main.o -lQuantLib

clean:
	rm -f *.o src/*.o lib/* goql
