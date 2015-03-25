all: main

main: main.cpp map.h terrain.h grass.h water.h character.h
	g++ main.cpp -o main

clean:
	rm *.o main
