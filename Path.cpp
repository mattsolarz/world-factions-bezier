#include "Path.h"

void Path::addPoint(double x_in, double y_in, double z_in) {
	Point toAdd(x_in, y_in, z_in);

	addPoint(toAdd);
}

void Path::addPoint(Point p) {
	if(!point_list.empty()) {
		double dist = distance(point_list.back(), p);
		total_distance += dist;
		step_lengths.push_back(dist);
	}

	point_list.push_back(p);

	cur_point = point_list.begin() + int_point;

}

void Path::setTime(double time_in) {
	time = time_in;
}

bool Path::step() {
	if(point_list.empty() || cur_point == point_list.end() || cur_point + 1 == point_list.end())
		return false;

	double time_for_step = time * step_lengths[int_point] / total_distance;

	int numsteps = ceil(ACTIONS_PER_SECOND * time_for_step);

	cur_step.clear();

	// Get the handle point
	auto handle = cur_point;
	handle++;

	// If handle is end(), then we're on the last point and we've
	// already done all the calculations
	if(handle == point_list.end()) {
		std::cout << "end\n";
		cur_point++;
		int_point++;
		return false;
	}

	// Get the second anchor point
	// If it's end() and "handle" wasn't, then we just need to do
	// a straight line
	auto next = handle;
	next++;

	// Loop through the bezier points
	if(next != point_list.end() && handle != point_list.end()) {
		std::cout << "bezier\n";
		for(int i = 0; i < numsteps; ++i) {
			double t = static_cast<double>(i)/numsteps;

			double x = pow(1 - t,2) * cur_point->x + 2 * (1 - t) * t * handle->x + pow(t,2) * next->x;
			double y = pow(1 - t,2) * cur_point->y + 2 * (1 - t) * t * handle->y + pow(t,2) * next->y;
			double z = pow(1 - t,2) * cur_point->z + 2 * (1 - t) * t * handle->z + pow(t,2) * next->z;

			cur_step.push_back(Point(x,y,z));
		}

		// Increment the pointers
		cur_point += 2;
		int_point += 2;
	}
	else if(next == point_list.end() && handle != point_list.end()) {
		std::cout << "straight\n";
		Point step = Point(handle->x - cur_point->x, handle->y - cur_point->y, handle->z - cur_point->z);
		step = step / numsteps; // Divide into numsteps pieces

		for(int i = 0; i < numsteps; ++i) {
			cur_step.push_back(*next + (step * i));
		}

		cur_point++;
		int_point++;
	}
	else {
		std::cout << "wtf\n";
		return false;
	}

	return true;
}

void Path::calculatePath() {
	for(size_t i = 0; i < point_list.size(); i += 2) {
		if(i == point_list.size() - 2) {
			double time_for_step = time * step_lengths[i] / total_distance;
			int numsteps = ceil(ACTIONS_PER_SECOND * time_for_step);

			Point step = Point(point_list[i + 1].x - point_list[i].x, point_list[i + 1].y - point_list[i].y, point_list[i + 1].z - point_list[i].z);
			step = step / numsteps; // Divide into numsteps pieces

			for(int j = 0; j < numsteps; ++j) {
				total_path.push_back(point_list[i] + (step * j));
			}
		}
		else {
			double time_for_step = time * (step_lengths[i] + step_lengths[i + 1]) / total_distance;
			int numsteps = ceil(ACTIONS_PER_SECOND * time_for_step);
			
			for(int j = 0; j < numsteps; ++j) {
				double t = static_cast<double>(j)/numsteps;

				double x = pow(1 - t,2) * point_list[i].x + 2 * (1 - t) * t * point_list[i + 1].x + pow(t,2) * point_list[i + 2].x;
				double y = pow(1 - t,2) * point_list[i].y + 2 * (1 - t) * t * point_list[i + 1].y + pow(t,2) * point_list[i + 2].y;
				double z = pow(1 - t,2) * point_list[i].z + 2 * (1 - t) * t * point_list[i + 1].z + pow(t,2) * point_list[i + 2].z;

				total_path.push_back(Point(x,y,z));
			}  
		}
	}

	total_path.push_back(point_list.back());

	/*
	bool run = true;
	while(cur_point != point_list.end() && int_point != static_cast<int>(size()) - 1 || !run) {
		run = step();

		total_path.insert(total_path.end(), cur_step.begin(), cur_step.end());
	}

	total_path.push_back(point_list.back());
	*/
}

void Path::printPath() {
	if(total_path.empty())
		return;

	for(auto it = total_path.begin(); it != total_path.end(); ++it) {
		std::cout << "(" << it->x << "," << it->y << "," << it->z << ")\n";
	}
}

void Path::printSteps() {
	if(cur_step.empty())
		return;

	for(auto it = cur_step.begin(); it != cur_step.end(); ++it) {
		std::cout << "(" << it->x << "," << it->y << "," << it->z << ")\n";
	}
}

double Path::distance(const Point &p1, const Point &p2) {
	return std::sqrt(
		std::pow(p1.x - p2.x, 2) + 
		std::pow(p1.y - p2.y, 2) + 
		std::pow(p1.z - p2.z, 2)
	);
}
