//
//

#include "TKMaterial.h"
#include "TKMath.h"

bool TKLambertian::scatter(const TKRay &ray_in, const TKHitRecord &rec,
						   glm::vec3 &attenuation, TKRay &scattered) const {
	glm::vec3 target = rec.p+rec.normal+TKMath::random_in_unit_sphere();
	scattered = TKRay(rec.p, target-rec.p, ray_in.time());
	attenuation = albedo;
	return true;
}

bool TKMetal::scatter(const TKRay &ray_in, const TKHitRecord &rec,
					  glm::vec3 &attenuation, TKRay &scattered) const {
	glm::vec3 v = glm::normalize(ray_in.direction());
	glm::vec3 n = rec.normal;
	glm::vec3 reflected = reflect(v, n);// v - 2.0f*glm::dot(v, n)*n;
	scattered = TKRay(rec.p, reflected + fuzz*TKMath::random_in_unit_sphere());
	attenuation = albedo;
	return glm::dot(scattered.direction(), rec.normal) > 0.0;
}
	
bool TKDielectric::scatter(const TKRay &ray_in, const TKHitRecord &rec,
						   glm::vec3 &attenuation, TKRay &scattered) const {
	glm::vec3 outNormal;
	glm::vec3 reflect = TKMath::reflect(ray_in.direction(), rec.normal);
	float ni_over_nt;
	attenuation = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 refracted;
	float reflect_prob;
	float cosine;
	if(dot(ray_in.direction(), rec.normal) > 0){
		outNormal = -rec.normal;
		ni_over_nt = ref_idx;
		cosine = ref_idx*dot(ray_in.direction(), rec.normal)/ray_in.direction().length();
	}else{
		outNormal = rec.normal;
		ni_over_nt = 1.0f/ref_idx;
		cosine = -dot(ray_in.direction(), rec.normal)/ray_in.direction().length();
	}

	if(TKMath::refract(ray_in.direction(), outNormal, ni_over_nt, refracted)){
		reflect_prob = TKMath::schlick(cosine, ref_idx);
	}else{
		scattered = TKRay(rec.p, reflect);
		reflect_prob = 1.0f;
	}

	if(drand48() < reflect_prob){
		scattered = TKRay(rec.p, reflect);
	}else{
		scattered = TKRay(rec.p, refracted);
	}
	return true;
}





