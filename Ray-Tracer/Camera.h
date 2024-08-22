#pragma once
#include "ray-tracer.h"
#include "Hittable.h"

class Camera {
public:
    double  aspectRatio = 16.0 / 9.0;
    int     imageWidth = 400;
	int     samplesPerPixel = 200;

    void Render(const Hittable& world) {
        Initialize();

        std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

        for (int j = 0; j < imageHeight; j++) {
            std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
            for (int i = 0; i < imageWidth; i++) {
                Color pixelColor(0, 0, 0);
                for (int sample = 0; sample < samplesPerPixel; sample++) {
                    Ray r = GetRay(i, j);
                    pixelColor += RayColor(r, world);
                }
                WriteColor(std::cout, pixelSamplesScale * pixelColor);
            }
        }

        std::clog << "\rDone.                 \n";
    }

private:
    int         imageHeight;            // Rendered image height
    double      pixelSamplesScale;    // Color scale factor for a sum of pixel samples
    Point3      center;                 // Camera center
    Point3      pixel00_loc;            // Location of pixel 0, 0
    Vector3     pixelDelta_u;           // Offset to pixel to the right
    Vector3     pixelDelta_v;           // Offset to pixel below

    void Initialize() {
        imageHeight = int(imageWidth / aspectRatio);
        imageHeight = (imageHeight < 1) ? 1 : imageHeight;

        pixelSamplesScale = 1.0 / samplesPerPixel;

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

    Ray GetRay(int i, int j) const {
        // Construct a camera ray originating from the origin and directed at randomly sampled
        // point around the pixel location i, j.

        auto offset = SampleSquare();
        auto pixel_sample = pixel00_loc
            + ((i + offset.x()) * pixelDelta_u)
            + ((j + offset.y()) * pixelDelta_v);

        auto ray_origin = center;
        auto ray_direction = pixel_sample - ray_origin;

        return Ray(ray_origin, ray_direction);
    }

    Vector3 SampleSquare() const {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return Vector3(random_double() - 0.5, random_double() - 0.5, 0);
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