//
//
#include "TKMath.h"

glm::vec3 TKMath::random_in_unit_sphere(){
	glm::vec3 p;
	do{
		p = 2.0f*glm::vec3(drand48(), drand48(), drand48())-glm::vec3(1.0f, 1.0f, 1.0f);
	}while(p.x*p.x+p.y*p.y+p.z*p.z >= 1.0f);
	return p;
}

glm::vec3 TKMath::reflect(const glm::vec3 &v, const glm::vec3 &n){
	return v- 2.0f*glm::dot(v, n)*n;
}

bool TKMath::refract(const glm::vec3 &v, const glm::vec3 &n, float ni_over_nt, glm::vec3 &refracted){
	glm::vec3 uv = glm::normalize(v);
	float dt = dot(uv, n);
	float discriminant = 1.0f-ni_over_nt*ni_over_nt*(1-dt*dt);
	if(discriminant > 0){
		refracted = ni_over_nt*(uv - n*dt) - n*sqrt(discriminant);
		return true;
	}
	return false;
}

float TKMath::schlick(float cosine, float ref_idx){
	float r0 = (1.0-ref_idx)/(1+ref_idx);
	r0 = r0*r0;
	return r0+(1-r0)*pow((1-cosine), 5);
}

glm::vec3 TKMath::random_in_unit_disk(){
	glm::vec3 p;
	do{
		p = 2.0f*glm::vec3(drand48(), drand48(), 0.0f) - glm::vec3(1.0, 1.0, 0.0);
	}while(dot(p, p) >= 1.0f);
	return p;
}


