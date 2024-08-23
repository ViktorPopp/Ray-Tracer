#pragma once
#include "ray-tracer.h"
#include "Ray.h"
#include "Material.h"

class HitRecord {
public:
    Point3 p;
    Vector3 normal;
    double t;
    std::shared_ptr<Material> material;
    bool frontFace;

    void SetFaceNormal(const Ray& r, const Vector3& outwardNormal) {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.

        frontFace = Dot(r.GetDirection(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable {
public:
    virtual ~Hittable() = default;

    virtual bool Hit(const Ray& r, Interval ray_t, HitRecord& rec) const = 0;
};