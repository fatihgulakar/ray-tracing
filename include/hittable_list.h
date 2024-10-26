#pragma once
#include "hittable.h"

#include <memory>
#include <vector>

class hittable_list : public hittable {
private:
	std::vector<std::shared_ptr<hittable>> objects;
public:
	hittable_list() {}
	hittable_list(std::shared_ptr<hittable> obj) { add(obj); }
	void clear() { this->objects.clear(); }
	void add(std::shared_ptr<hittable> obj) { this->objects.push_back(obj); }

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
};

bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	hit_record temp_rec;
	bool hit_anything = false;
	auto closest = t_max;

	for (const auto& obj : this->objects) {
		if (obj->hit(r, t_min, t_max, temp_rec)) {
			hit_anything = true;
			closest = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}