#include "vec2.h"

Vec2::Vec2()
	#ifdef __SSE2__
	: x(vec.xy[0]), y(vec.xy[1]) {
	vec.v = _mm_setr_pd(0.0, 0.0);
	#else
	: x(0.0), y(0.0) {
	#endif //__SSE2__
}

Vec2::Vec2(double xy)
	#ifdef __SSE2__
	: x(vec.xy[0]), y(vec.xy[1]) {
	vec.v = _mm_setr_pd(xy, xy);
	#else
	: x(xy), y(xy) {
	#endif //__SSE2__
}

Vec2::Vec2(double x, double y)
	#ifdef __SSE2__
	: x(vec.xy[0]), y(vec.xy[1]) {
	vec.v = _mm_setr_pd(x, y);
	#else
	: x(x), y(y) {
	#endif //__SSE2__
}

Vec2::~Vec2() {
}

void Vec2::operator=(const Vec2& other) {
	#ifdef __SSE2__
	vec.v = _mm_setr_pd(other.x, other.y);
	#else
	x = other.x;
	y = other.y;
	#endif //__SSE2__
}

void Vec2::operator+=(const Vec2& other) {
	*this = *this + other;
}

void Vec2::operator-=(const Vec2& other) {
	*this = *this - other;
}

void Vec2::operator*=(const Vec2& other) {
	*this = *this * other;
}

Vec2 Vec2::operator+(const Vec2& other) const {
	#ifdef __SSE2__
	Vec2 ret;
	ret.vec.v = _mm_add_pd(vec.v, other.vec.v);
	#else
	Vec2 ret(x + other.x, y + other.y);
	#endif //__SSE2__
	return ret;
}

Vec2 Vec2::operator-(const Vec2& other) const {
	#ifdef __SSE2__
	Vec2 ret;
	ret.vec.v = _mm_sub_pd(vec.v, other.vec.v);
	#else
	Vec2 ret(x - other.x, y - other.y);
	#endif //__SSE2__
	return ret;
}

Vec2 Vec2::operator-() const {
	#ifdef __SSE2__
	Vec2 ret;
	ret.vec.v = _mm_sub_pd(_mm_set1_pd(0.0), vec.v);
	#else
	Vec2 ret(-x, -y);
	#endif //__SSE2__
	return ret;
}

double Vec2::operator*(const Vec2& other) const {
	#ifdef __SSE4_1__
	vector ret;
	ret.v = _mm_dp_pd(vec.v, other.vec.v, 0xFF);
	return ret.xy[0];
	#else
	return x * other.x + y * other.y;
	#endif //__SSE4_1__
}

Vec2 Vec2::operator*(const double& other) const {
	#ifdef __SSE2__
	Vec2 ret;
	__m128d scalar = _mm_set1_pd(other);
	ret.vec.v = _mm_mul_pd(vec.v, scalar);
	#else
	Vec2 ret(other * x, other * y);
	#endif //__SSE2__
	return ret;
}

Vec2 Vec2::operator/(const double& other) const {
	#ifdef __SSE2__
	Vec2 ret;
	__m128d scalar = _mm_set1_pd(other);
	ret.vec.v = _mm_div_pd(vec.v, scalar);
	#else
	Vec2 ret(x / other, y / other);
	#endif //__SSE2__
	return ret;
}

double Vec2::length() const {
	#ifdef __SSE2__
	auto xy = std::make_unique<double[]>(2);
	__m128d tmp = _mm_mul_pd(vec.v, vec.v);
	_mm_storeu_pd(xy.get(), tmp);
	return sqrt(xy[0] + xy[1]);
	#else
	return sqrt(x * x + y * y);
	#endif //__SSE2__
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
