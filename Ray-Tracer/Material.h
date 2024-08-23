#pragma once
#include "ray-tracer.h"
#include "Hittable.h"

class Material {
public:
    virtual ~Material() = default;

    virtual bool Scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const {
        return false;
    }
};

class Lambertian : public Material {
public:
    Lambertian(const Color& albedo) : albedo(albedo) {}

    bool Scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override {
        auto scatterDirection = rec.normal + RandomUnitVector();
        // Catch degenerate scatter direction
        if (scatterDirection.NearZero())
            scatterDirection = rec.normal;

        scattered = Ray(rec.p, scatterDirection);
        attenuation = albedo;
        return true;
    }

private:
    Color albedo;
};

class Metal : public Material {
public:
    Metal(const Color& albedo) : albedo(albedo) {}

    bool Scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered)
        const override {
        Vector3 reflected = Reflect(r_in.GetDirection(), rec.normal);
        scattered = Ray(rec.p, reflected);
        attenuation = albedo;
        return true;
    }

private:
    Color albedo;
};