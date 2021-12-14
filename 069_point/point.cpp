#include <cmath>
#include <cstdio>

#include "point.hpp"

void Point::move(double dx, double dy) {
	x = x + dx;
	y = y + dy;
}

double Point::distanceFrom(const Point & p) {
	double dx = p.x - x;
	double dy = p.y - y;
	return (std::sqrt)(dx * dx + dy * dy);
}
