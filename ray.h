#pragma once
#include "vec3.h"

class ray
{
private:
	vec3 orig;
	vec3 dir;
public:
	ray() {}
	ray(const point3& orig, const vec3& dir) : orig(orig), dir(dir) {}
	point3 origin() const { return this->orig; }
	vec3 direction() const { return this->dir; }
	point3 at(double t) const { return this->orig + t * this->dir; }


};