#pragma once

#include "Hittable.h"

class sphere : public Hittable {
public:
    sphere(const Point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}

    bool Hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const override {
        Vector3 oc = center - r.GetOrigin();
        auto a = r.GetDirection().LengthSquared();
        auto h = Dot(r.GetDirection(), oc);
        auto c = oc.LengthSquared() - radius * radius;

        auto discriminant = h * h - a * c;
        if (discriminant < 0)
            return false;

        auto sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (h - sqrtd) / a;
        if (root <= ray_tmin || ray_tmax <= root) {
            root = (h + sqrtd) / a;
            if (root <= ray_tmin || ray_tmax <= root)
                return false;
        }

        rec.t = root;
        rec.p = r.At(rec.t);
        Vector3 outwardNormal = (rec.p - center) / radius;
        rec.set_face_normal(r, outwardNormal);

        return true;
    }

private:
    Point3 center;
    double radius;
};