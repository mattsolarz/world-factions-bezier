#include "Curve.h"

void Curve::addPoint(double x_in, double y_in, double z_in,
		double x_r, double y_r, double z_r) {
	Point toAdd(x_in, y_in, z_in);

	Point toRot(x_r, y_r, z_r);

	addPoint(toAdd, toRot);
}

void Curve::addPoint(Point p, Point r) {
	if(!point_list.empty()) {
		double dist = distance(point_list.back(), p);
		total_distance += dist;
		step_lengths.push_back(dist);
	}

	point_list.push_back(p);

	rot_list.push_back(r);
}

void Curve::setTime(double time_in) {
	time = time_in;
}

void Curve::calculatePath() {
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

	for(size_t i = 0; i < rot_list.size() - 1; ++i) {
		double time_for_step = time * step_lengths[i] / total_distance;
		int numsteps = ceil(ACTIONS_PER_SECOND * time_for_step);

		Point step = Point(rot_list[i + 1].x - rot_list[i].x, rot_list[i + 1].y - rot_list[i].y, rot_list[i + 1].z - rot_list[i].z);
		step = step / numsteps; // Divide into numsteps pieces

		for(int j = 0; j < numsteps; ++j) {
			total_rot.push_back(rot_list[i] + (step * j));
		}
	}

	total_path.push_back(point_list.back());
	total_rot.push_back(rot_list.back());
}

void Curve::printPath() {
	if(total_path.empty())
		return;

	//for(auto it = total_path.begin(); it != total_path.end(); ++it) {
	for(size_t i = 0; i < total_path.size(); ++i) {
		std::cout << "(" << total_path[i].x << "," << total_path[i].y << "," << total_path[i].z << ") ";
		std::cout << "(" << total_rot[i].x << "," << total_rot[i].y << "," << total_rot[i].z << ")\n";
	}
}

double Curve::distance(const Point &p1, const Point &p2) {
	return std::sqrt(
		std::pow(p1.x - p2.x, 2) + 
		std::pow(p1.y - p2.y, 2) + 
		std::pow(p1.z - p2.z, 2)
	);
}
