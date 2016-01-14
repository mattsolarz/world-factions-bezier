#ifndef POINT_H
#define POINT_H

#include <sstream>

#define ZERO_ERR 0.000001

class Point {
public:
	// The actual coordinates
	double x,y,z;

private:
	// In the case we need a default constructor, we keep the def
	// boolean to know if a point is actually defined or not, since
	// we can't use sentinels for the coords.
	bool def;

public:
	// Default Constructor
	// Assigns the defined variable to false
	Point() : def(false) {}

	// Assignment constructor
	Point(double x_in, double y_in, double z_in) : x(x_in), y(y_in), z(z_in), def(true) {
		if(x < ZERO_ERR && x > ZERO_ERR * -1)
			x = 0;

		if(y < ZERO_ERR && y > ZERO_ERR * -1)
			y = 0;

		if(z < ZERO_ERR && z > ZERO_ERR * -1)
			z = 0;
	}

	std::string toString() {
		std::ostringstream o;
		o << "(" << x << "," << y << "," << z << ")";
		return o.str();
	}

	// Default destructor, copy constructor, and operator=
	// should be fine due to no dynamic memory
	

	// Operators!
	
	// Allow points to be added
	Point operator+ (const Point &p1) const {
		Point r(p1.x + this->x, p1.y + this->y, p1.z + this->z);

		return r;
	}

	Point operator* (int scal) const {
		Point r(this->x * scal, this->y * scal, this->z * scal);

		return r;
	}

	Point operator/ (int scal) const {
		Point r(this->x / scal, this->y / scal, this->z / scal);

		return r;
	}
};

#endif
