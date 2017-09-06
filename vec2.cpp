#include "vec2.h"

Vec2::Vec2() {
	x = 0.0f;
	y = 0.0f;
}

Vec2::Vec2(double xy) {
	x = xy;
	y = xy;
}

Vec2::Vec2(double x, double y) {
	this->x = x;
	this->y = y;
}

Vec2::~Vec2() {
}

void Vec2::operator=(const Vec2& other) {
	x = other.x;
	y = other.y;
}

void Vec2::operator+=(const Vec2& other) {
	(*this) = (*this) + other;
}

void Vec2::operator-=(const Vec2& other) {
	(*this) = (*this) - other;
}

void Vec2::operator*=(const Vec2& other) {
	(*this) = (*this) * other;
}

Vec2 Vec2::operator+(const Vec2& other) const {
	return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(const Vec2& other) const {
	return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator-() const {
	return Vec2(-x, -y);
}

double Vec2::operator*(const Vec2& other) const {
	return x * other.x + y * other.y;
}

Vec2 Vec2::operator*(const double& other) const {
	return Vec2(x * other, y * other);
}

Vec2 Vec2::operator/(const double& other) const {
	return Vec2(x / other, y / other);
}

double Vec2::length() const {
	return sqrt(x * x + y * y);
}

Vec2 Vec2::normal() const {
	return Vec2(y, -x);
}

Vec2 Vec2::normalize() const {
	return *this / length();
}

double Vec2::project_onto(const Vec2& other) const {
	return ((*this) * other) / other.length();
}
