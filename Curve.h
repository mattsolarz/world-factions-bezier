#ifndef CURVE_H
#define CURVE_H

#include <cmath>
#include <iostream>
#include <vector>

#include "Point.h"


// Constants
#define ACTIONS_PER_SECOND 30

class Curve {
	// Contains the current points in the list
	std::vector<Point> point_list;

	std::vector<Point> rot_list;

	// Contains the total list of interpreted coordinates
	std::vector<Point> total_path;

	std::vector<Point> total_rot;

	// The amount of time the path takes
	double time;

	// The total distance of the path
	double total_distance;

	// The length of each step
	std::vector<double> step_lengths;

public:
	// Default constructor with empty point_list
	Curve(double time_in = 0) : time(time_in), total_distance(0) {}

	// Add a point to the path
	// Add with coordinates
	void addPoint(double x_in, double y_in, double z_in, double x_r, double y_r, double z_r);
	
	// Add with a pre-defined Point object
	void addPoint(Point p, Point r);

	// Calculate the total path
	void calculatePath();

	// Print the total path
	void printPath();

	// Assign the time of the path
	void setTime(double time_in);

	// Return the number of points in the path
	size_t size() { return point_list.size(); }

	// Static methods
	static double distance(const Point &p1, const Point &p2);

};
#endif
