#ifndef PATH_H
#define PATH_H

#include <cmath>
#include <iostream>
#include <vector>

#include "Point.h"


// Constants
#define ACTIONS_PER_SECOND 30

class Path {
	// Contains the current points in the list
	std::vector<Point> point_list;

	// Contains all subpoints between the current point and the
	// last point. If empty, the last step has either not occured
	// or was not valid (step() returned false)
	std::vector<Point> cur_step;

	// Contains the total list of interpreted coordinates
	std::vector<Point> total_path;

	// Contains an iterator to the current point on the path
	std::vector<Point>::iterator cur_point;
	int int_point;

	// The amount of time the path takes
	double time;

	// The total distance of the path
	double total_distance;

	// The length of each step
	std::vector<double> step_lengths;

public:
	// Default constructor with empty point_list
	Path(double time_in = 0) : int_point(0), time(time_in), total_distance(0) {}

	// Add a point to the path
	// Add with coordinates
	void addPoint(double x_in, double y_in, double z_in);
	
	// Add with a pre-defined Point object
	void addPoint(Point p);

	// Calculate the total path
	void calculatePath();

	// Print the total path
	void printPath();

	// Print all current steps
	void printSteps();

	// Assign the time of the path
	void setTime(double time_in);

	// Return the number of points in the path
	size_t size() { return point_list.size(); }

	// Steps between the current point and the next point
	// Returns false if there is no next point
	// Iterators cur_point, calculates subpoint steps, 
	// and returns true otherwise
	bool step();

	// Static methods
	static double distance(const Point &p1, const Point &p2);

};
#endif
