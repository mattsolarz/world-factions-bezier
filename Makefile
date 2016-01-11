CFLAGS = -std=c++11

all:
	g++ $(CFLAGS) Point.cpp Path.cpp RotPath.cpp Body.cpp point_unit.cpp -g -o point_unit.exe


