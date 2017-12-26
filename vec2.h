#ifndef __VEC2_H__
#define __VEC2_H__

#include <cmath>
#include <memory>
#if defined(__SSE4_1__)
	#include <smmintrin.h>
#elif defined(__SSE2__)
	#include <emmintrin.h>
#endif

#ifdef __SSE2__
typedef union {
	__m128d v;
	double xy[2];
} vector;
#endif //__SSE2__

class Vec2 {
	#ifdef __SSE2__
	vector vec;
	#endif //__SSE2__
public:
	#ifdef __SSE2__
	double& x;
	double& y;
	#else
	double x;
	double y;
	#endif //__SSE2__

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
