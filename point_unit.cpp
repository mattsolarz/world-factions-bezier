#include <iostream>

#include "Body.h"

using namespace std;

int main(void) {

	Body b(5);

	b.addPoint(0,0,0,0,0,0);
	b.addPoint(30,30,30,90,90,90);
	b.addPoint(0,40,90,45,45,45);
	b.addPoint(0,40,100,90,90,90);

	b.calculatePath();

	b.printPath();

	return 0;
}
