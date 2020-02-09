#ifndef __TKSphere_h__
#define __TKSphere_h__

#include "TKHitable.h"
#include "TKMaterial.h"

class TKSphere: public TKHitable {
public:
	TKSphere(){};
	TKSphere(glm::vec3 cen, float r) : center(cen), radius(r) {};
	TKSphere(glm::vec3 cen, float r, TKMaterial *m);
	~TKSphere();
	
	virtual bool hit(const TKRay &ray, float t_min, float t_max, TKHitRecord &rec) const;
	glm::vec3 center;
	float radius;
	TKMaterial *material;
};
#endif


