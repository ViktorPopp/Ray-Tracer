#pragma once



class HitRecord {
public:
    Point3 p;
    Vector3 normal;
    double t;
    bool frontFace;

    void set_face_normal(const Ray& r, const Vector3& outwardNormal) {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.

        frontFace = Dot(r.GetDirection(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable {
public:
    virtual ~Hittable() = default;

    virtual bool Hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const = 0;
};