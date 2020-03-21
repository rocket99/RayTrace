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


class TKMovingSphere:public TKHitable {
public:
	TKMovingSphere(){};
	TKMovingSphere(glm::vec3 cen0, glm::vec3 cen1,
				   float t0, float t1, float r, TKMaterial *m) {
		center0 = cen0; center1 = cen1;
		time0 = t0; time1 = t1;
		radius = r; material = m;
	}
	virtual bool hit(const TKRay &r, float t_min, float t_max, TKHitRecord &rec) const;
	glm::vec3 center(float time) const;
	
private:
	glm::vec3 center0, center1;
	float time0, time1;
	float radius;
	TKMaterial *material;
};
