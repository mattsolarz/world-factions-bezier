CFLAGS = -std=c++11

all:
	g++ $(CFLAGS) Point.cpp Curve.cpp point_unit.cpp -g -o point_unit.exe


