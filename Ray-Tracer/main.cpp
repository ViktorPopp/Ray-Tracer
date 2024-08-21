#include <iostream>
#include "color.h"
#include "Vector3.h"

int main() {

    /* Image */
    int imageWidth = 256;
    int imageHeight = 256;

	/* Render */
    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = 0; j < imageHeight; j++) {
        std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        for (int i = 0; i < imageWidth; i++) {
            auto pixelColor = color(double(i) / (imageWidth - 1), double(j) / (imageHeight - 1), 0);
            WriteColor(std::cout, pixelColor);
        }
    }

    std::clog << "\rDone.                 \n";
}