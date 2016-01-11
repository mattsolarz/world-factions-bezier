#include "RotPath.h"

void RotPath::addPoint(double x_in, double y_in, double z_in) {
	Point toAdd(x_in, y_in, z_in);

	addPoint(toAdd);
}

void RotPath::addPoint(Point p) {
	if(!rot_list.empty()) {
		double dist = distance(rot_list.back(), p);
		total_distance += dist;
		step_lengths.push_back(dist);
	}

	rot_list.push_back(p);

	cur_point = rot_list.begin() + int_point;

}

void RotPath::setTime(double time_in) {
	time = time_in;
}

bool RotPath::step() {
	cur_point = rot_list.begin() + int_point;
	if(rot_list.empty() || cur_point == rot_list.end() || cur_point + 1 == rot_list.end())
		return false;

	double time_for_step = time * step_lengths[int_point] / total_distance;

	int numsteps = ceil(ACTIONS_PER_SECOND * time_for_step);

	cur_step.clear();

	auto handle = cur_point + 1;

	// Get the second anchor point
	// If it's end() and "handle" wasn't, then we just need to do
	// a straight line
	std::cout << "straight\n";
	Point step(handle->x - cur_point->x, handle->y - cur_point->y, handle->z - cur_point->z);
	step = step / numsteps; // Divide into numsteps pieces

	for(int i = 0; i < numsteps; ++i) {
		cur_step.push_back(*cur_point + (step * i));
	}

	cur_point++;
	int_point++;

	return true;
}

void RotPath::calculatePath() {
	bool run = true;
	while(cur_point != rot_list.end() && int_point != static_cast<int>(size()) - 1 || !run) {
		run = step();

		total_path.insert(total_path.end(), cur_step.begin(), cur_step.end());
	}

	total_path.push_back(rot_list.back());
}

void RotPath::printPath() {
	if(total_path.empty())
		return;

	for(auto it = total_path.begin(); it != total_path.end(); ++it) {
		std::cout << "(" << it->x << "," << it->y << "," << it->z << ")\n";
	}
}

void RotPath::printSteps() {
	if(cur_step.empty())
		return;

	for(auto it = cur_step.begin(); it != cur_step.end(); ++it) {
		std::cout << "(" << it->x << "," << it->y << "," << it->z << ")\n";
	}
}

double RotPath::distance(const Point &p1, const Point &p2) {
	return std::sqrt(
		std::pow(p1.x - p2.x, 2) + 
		std::pow(p1.y - p2.y, 2) + 
		std::pow(p1.z - p2.z, 2)
	);
}
