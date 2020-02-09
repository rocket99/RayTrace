//
//
#ifndef __TKMaterial_h__
#define __TKMaterial_h__

#include "TKPrefix.h"
#include "TKRay.h"
#include "TKHitable.h"
class TKMaterial {
public:
	virtual bool scatter(const TKRay &ray_in, const TKHitRecord &rec,
						 glm::vec3 &attenuation, TKRay &scattered) const = 0;
};


class TKLambertian:public TKMaterial {
public:
	TKLambertian(glm::vec3 a):albedo(a){}
	virtual bool scatter(const TKRay &ray_in, const TKHitRecord &rec,
						 glm::vec3 &attenuation, TKRay &scattered) const;
	glm::vec3 albedo;
};

class TKMetal:public TKMaterial {
public:
	TKMetal(glm::vec3 a, float f) : albedo(a) {
		fuzz = f < 1.0f ? f : 1.0f;
	}
	virtual bool scatter(const TKRay &ray_in, const TKHitRecord &rec,
						 glm::vec3 &attenuation, TKRay &scattered) const;
	glm::vec3 albedo;
	float fuzz;
};

class TKDielectric : public TKMaterial {
public:
	TKDielectric(float ri):ref_idx(ri) {}
	virtual bool scatter(const TKRay &ray_in, const TKHitRecord &rec,
						 glm::vec3 &attenuation, TKRay &scattered) const;
	float ref_idx;
};

#endif
