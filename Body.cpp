#include "Body.h"

void Body::addPoint(double x_in, double y_in, double z_in, double x_r, double y_r, double z_r) {
	p.addPoint(x_in, y_in, z_in);
	r.addPoint(x_r, y_r, z_r);
}

void Body::calculatePath() {
	p.calculatePath();
	r.calculatePath();
}

void Body::printPath() {
	std::cout << "Path\n";
	p.printPath();
	std::cout << "\nRotation\n";
	r.printPath();
}
