#ifndef BODY_H
#define BODY_H

#include "Point.h"
#include "Path.h"
#include "RotPath.h"

#include <iostream>

class Body {
	Path p;

	RotPath r;

public:
	
	Body(int time) : p(Path(time)), r(RotPath(time)) {}

	void addPoint(double x_in, double y_in, double z_in, double x_r = 0, double y_r = 0, double z_r = 0);

	void calculatePath();

	void printPath();

};

#endif
