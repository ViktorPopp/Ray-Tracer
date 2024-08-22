#pragma once
#include "ray-tracer.h"
#include "Hittable.h"

class Camera {
public:
    double  aspectRatio = 16.0 / 9.0;
    int     imageWidth = 400;

    void Render(const Hittable& world) {
        Initialize();

        std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

        for (int j = 0; j < imageHeight; j++) {
            std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
            for (int i = 0; i < imageWidth; i++) {
                auto pixelCenter = pixel00_loc + (i * pixelDelta_u) + (j * pixelDelta_v);
                auto rayDirection = pixelCenter - center;
                Ray ray(center, rayDirection);

                Color pixelColor = RayColor(ray, world);
                WriteColor(std::cout, pixelColor);
            }
        }

        std::clog << "\rDone.                 \n";
    }

private:
    int         imageHeight;   // Rendered image height
    Point3      center;   // Camera center
    Point3      pixel00_loc;    // Location of pixel 0, 0
    Vector3     pixelDelta_u;   // Offset to pixel to the right
    Vector3     pixelDelta_v;   // Offset to pixel below

    void Initialize() {
        imageHeight = int(imageWidth / aspectRatio);
        imageHeight = (imageHeight < 1) ? 1 : imageHeight;

        center = Point3(0, 0, 0);

        // Determine viewport dimensions.
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(imageWidth) / imageHeight);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        auto viewport_u = Vector3(viewport_width, 0, 0);
        auto viewport_v = Vector3(0, -viewport_height, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixelDelta_u = viewport_u / imageWidth;
        pixelDelta_v = viewport_v / imageHeight;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left =
            center - Vector3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixelDelta_u + pixelDelta_v);
    }

    Color RayColor(const Ray& r, const Hittable& world) const {
        HitRecord rec;
        if (world.Hit(r, Interval(0, infinity), rec)) {
            return 0.5 * (rec.normal + Color(1, 1, 1));
        }

        Vector3 unitDirection = UnitVector(r.GetDirection());
        auto a = 0.5 * (unitDirection.y() + 1.0);
        return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
    }
};