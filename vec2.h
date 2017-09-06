#ifndef __VEC2_H__
#define __VEC2_H__

#include <cmath>

class Vec2 {
public:
	double x;
	double y;

	Vec2();
	Vec2(double xy);
	Vec2(double x, double y);
	~Vec2();

	void operator=(const Vec2& other);
	void operator+=(const Vec2& other);
	void operator-=(const Vec2& other);
	void operator*=(const Vec2& other);
	Vec2 operator+(const Vec2& other) const;
	Vec2 operator-() const;
	Vec2 operator-(const Vec2& other) const;
	double operator*(const Vec2& other) const;
	Vec2 operator*(const double& other) const;
	Vec2 operator/(const double& other) const;

	double length() const;
	Vec2 normal() const;
	Vec2 normalize() const;

	double project_onto(const Vec2& other) const;
};

#endif //__VEC2_H__
