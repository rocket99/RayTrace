#ifndef __TKHitable_h__
#define __TKHitable_h__

#include "TKPrefix.h"
#include "TKRay.h"

class TKMaterial;

struct TKHitRecord {
	float t;
	glm::vec3 p;
	glm::vec3 normal;
	TKMaterial *mat_ptr;
};

class TKHitable {
public:
	virtual bool hit(const TKRay & r, float t_min, float t_max, TKHitRecord &rec) const = 0;
};
#endif
