#pragma once

#include "Vector3.h"

class Ray {
public:
	Ray() = default;
	Ray(const Point3& origin, const Vector3& direction) : m_origin(origin), m_direction(direction) {}

	const Point3& GetOrigin() const { return m_origin; }
	const Point3& GetDirection() const { return m_direction; }

	Point3 At(double t) const { return m_origin + t * m_direction; }

private:
	Point3 m_origin;
	Vector3 m_direction;
};