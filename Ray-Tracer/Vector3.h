#pragma once

class Vector3 {
public:
    double e[3];

    Vector3() : e{ 0,0,0 } {}
    Vector3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    Vector3 operator-() const { return Vector3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    Vector3& operator+=(const Vector3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    Vector3& operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    Vector3& operator/=(double t) {
        return *this *= 1 / t;
    }

    double Length() const {
        return std::sqrt(LengthSquared());
    }

    double LengthSquared() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    bool NearZero() const {
        // Return true if the vector is close to zero in all dimensions.
        auto s = 1e-8;
        return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
    }

    static Vector3 Random() {
        return Vector3(random_double(), random_double(), random_double());
    }

    static Vector3 Random(double min, double max) {
        return Vector3(random_double(min, max), random_double(min, max), random_double(min, max));
    }
};

// point3 is just an alias for Vector3, but useful for geometric clarity in the code.
using Point3 = Vector3;

// Vector Utility Functions
inline std::ostream& operator<<(std::ostream& out, const Vector3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline Vector3 operator+(const Vector3& u, const Vector3& v) {
    return Vector3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vector3 operator-(const Vector3& u, const Vector3& v) {
    return Vector3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vector3 operator*(const Vector3& u, const Vector3& v) {
    return Vector3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vector3 operator*(double t, const Vector3& v) {
    return Vector3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline Vector3 operator*(const Vector3& v, double t) {
    return t * v;
}

inline Vector3 operator/(const Vector3& v, double t) {
    return (1 / t) * v;
}

inline double Dot(const Vector3& u, const Vector3& v) {
    return u.e[0] * v.e[0]
        + u.e[1] * v.e[1]
        + u.e[2] * v.e[2];
}

inline Vector3 Cross(const Vector3& u, const Vector3& v) {
    return Vector3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vector3 UnitVector(const Vector3& v) {
    return v / v.Length();
}

inline Vector3 RandomInUnitSphere() {
    while (true) {
        auto p = Vector3::Random(-1, 1);
        if (p.LengthSquared() < 1)
            return p;
    }
}

inline Vector3 RandomUnitVector() {
    return UnitVector(RandomInUnitSphere());
}

inline Vector3 RandomOnHemisphere(const Vector3& normal) {
    Vector3 onUnitSphere = RandomUnitVector();
    if (Dot(onUnitSphere, normal) > 0.0) // In the same hemisphere as the normal
        return onUnitSphere;
    else
        return -onUnitSphere;
}

inline Vector3 Reflect(const Vector3& v, const Vector3& n) {
    return v - 2 * Dot(v, n) * n;
}