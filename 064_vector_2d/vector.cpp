#include "vector.hpp"

#include <cmath>
#include <cstdio>

void Vector2D::initVector(double x_init, double y_init){
	x = x_init;
	y = y_init;
}

double Vector2D::getMagnitude() const{
	double result;
	result = (std::sqrt)(x * x + y * y);
	return result;
}

Vector2D Vector2D::operator+(const Vector2D & rhs) const {
	Vector2D answer;
	answer.x = x + rhs.x;
	answer.y = y + rhs.y;
	return answer;
}

Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
	x += rhs.x;
	y += rhs.y;
	return *this;
}

double Vector2D::dot(const Vector2D & rhs) const{
	double result;
	result = x * rhs.x + y * rhs.y;
	return result;
}

void Vector2D::print() const{
	printf("<%.2f, %.2f>", x, y);
}


