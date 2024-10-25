#include <iostream>
#include <fstream>
#include <thread>
#include "vec3.h"
#include "color.h"
#include "ray.h"

using namespace std;

double hit_sphere(const point3& center, double radius, const ray& r) {
	vec3 oc = r.origin() - center;
	auto a = r.direction().length_squared(); // r^2
	auto b_half = dot(oc, r.direction());
	auto c = oc.length_squared() - radius * radius;
	auto discriminant = b_half * b_half - a * c;
	// If > 0, hits on 2 points, if == 0, it is tangent to the sphere, < 0, no intersection
	if (discriminant < 0) {
		return -1.0;
	}
	else {
		return (-b_half - std::sqrt(discriminant)) / a;
	}
}

color ray_color(const ray& r) {
	auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
	if (t > 0.0) {
		vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
		return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
	}
	vec3 unit_dir = unit_vector(r.direction());
	t = 0.5 * (unit_dir.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {

	// Image
	const auto aspect_ratio = 16.0 / 9.0;
	const auto img_width = 1080;
	const auto img_height = static_cast<int>(img_width / aspect_ratio);

	// Camera
	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;

	auto origin = point3(0, 0, 0);
	auto horizontal = vec3(viewport_width, 0, 0);
	auto vertical = vec3(0, viewport_height, 0);
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);


	ofstream ofs("img.ppm", ios_base::out | ios_base::binary);
	ofs << "P3\n" << img_width << " " << img_height << "\n255\n";

	for (int j = img_height - 1; j >= 0; --j) {
		cerr << "\rScanlines remaining: " << j << ' ' << flush;
		for (int i = 0; i < img_width; ++i) {
			auto u = double(i) / (img_width - 1);
			auto v = double(j) / (img_height - 1);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			color pixel_color = ray_color(r);
			write_color(ofs, pixel_color);
		}
	}
	
	ofs.close();
	cerr << "\nDone.\n";
	return EXIT_SUCCESS;

}