CFLAGS=-W -Wall -pedantic -Wextra

all:

	g++ $(CFLAGS) -c Point.cpp
	g++ $(CFLAGS) -c Vector.cpp
	g++ $(CFLAGS) -c TP_OPENGL.cpp
	g++ *.o -o tp -lGL -lglut
clean:
	rm *.o
