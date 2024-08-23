#include "ray-tracer.h"
#include "Hittable.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"

int main()
{
	HittableList world;
	auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
	auto material_center = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
	auto material_left = make_shared<Metal>(Color(0.8, 0.8, 0.8));
	auto material_right = make_shared<Metal>(Color(0.8, 0.6, 0.2));

	world.Add(make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.Add(make_shared<Sphere>(Point3(0.0, 0.0, -1.2), 0.5, material_center));
	world.Add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
	world.Add(make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));

	Camera camera;

	camera.aspectRatio = 16.0 / 9.0;
	camera.imageWidth = 400;
	camera.samplesPerPixel = 100;
	camera.maxDepth = 50;

	camera.Render(world);
}