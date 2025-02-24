#pragma once
#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
private:
	point3 center;
	double radius;
public:
	sphere() {}
	sphere(point3 c, double r) : center(c), radius(r) {};
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	auto a = r.direction().length_squared(); // r^2
	auto b_half = dot(oc, r.direction());
	auto c = oc.length_squared() - radius * radius;
	auto discriminant = b_half * b_half - a * c;
	if (discriminant < 0) return 0;
	auto sqrtd = std::sqrt(discriminant);

	auto root = (-b_half - sqrtd) / a;
	if (root < t_min || root > t_max) {
		root = (-b_half + sqrtd) / a;
		if (root < t_min || root > t_max)
			return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	vec3 outward_normal = (rec.p - center) / radius;
	rec.set_face_normal(r, outward_normal);

	return true;
}