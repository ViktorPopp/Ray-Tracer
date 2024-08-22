#include <iostream>
#include "Color.h"
#include "Vector3.h"
#include "Ray.h"

double HitSphere(const Point3& center, double radius, const Ray& r) {
    Vector3 oc = center - r.GetOrigin();
    auto a = Dot(r.GetDirection(), r.GetDirection());
    auto b = -2.0 * Dot(r.GetDirection(), oc);
    auto c = Dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return -1.0;
    }
    else {
        return (-b - std::sqrt(discriminant)) / (2.0 * a);
    }
}

Color RayColor(const Ray& r) {
    auto t = HitSphere(Point3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        Vector3 N = UnitVector(r.At(t) - Vector3(0, 0, -1));
        return 0.5 * Color(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    Vector3 unitDirection = UnitVector(r.GetDirection());
    auto a = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);
}


int main()
{
    /* Image */
    auto aspectRatio = 16.0 / 9.0;
    int imageWidth = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int imageHeight = int(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    /* Camera */
    auto focalLength = 1.0;
    auto viewportHeight = 2.0;
    auto viewportWidth = viewportHeight * (double(imageWidth) / imageHeight);
    auto cameraCenter = Point3(0, 0, 0);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = Vector3(viewportWidth, 0, 0);
    auto viewport_v = Vector3(0, -viewportHeight, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixelDelta_u = viewport_u / imageWidth;
    auto pixelDelta_v = viewport_v / imageHeight;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = cameraCenter - Vector3(0, 0, focalLength) - viewport_u / 2 - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixelDelta_u + pixelDelta_v);

	/* Render */
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++) {
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        for (int i = 0; i < imageWidth; i++) {
            auto pixelCenter = pixel00_loc + (i * pixelDelta_u) + (j * pixelDelta_v);
            auto rayDirection = pixelCenter - cameraCenter;
            Ray ray(cameraCenter, rayDirection);

            Color pixelColor = RayColor(ray);
            WriteColor(std::cout, pixelColor);
        }
    }

    std::clog << "\rDone.                 \n";
}