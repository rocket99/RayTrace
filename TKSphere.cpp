#include "TKSphere.h"

TKSphere::TKSphere(glm::vec3 cen, float r, TKMaterial *m){
	center = cen;
	radius = r;
	material = m;
}

bool TKSphere::hit(const TKRay &ray, float t_min, float t_max, TKHitRecord &rec) const {
	glm::vec3 oc = ray.origin() - center;
	float a = glm::dot(ray.direction(), ray.direction());
	float b = glm::dot(oc, ray.direction());
	float c = glm::dot(oc, oc) - radius*radius;
	float  discriminant = b*b - a*c;
	if(discriminant > 0.0f){
		float temp = (-b - sqrt(b*b-a*c)) / a;
		if(temp < t_max && temp > t_min){
			rec.t = temp;
			rec.p = ray.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = material;
			return true;
		}
		temp = (-b + sqrt(b*b-a*c))/a;
		if(temp < t_max && temp > t_min){
			rec.t = temp;
			rec.p = ray.point_at_parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = material;
			return true;
		}
	}
	return false;
}


bool TKMovingSphere::hit(const TKRay &ray, float t_min, float t_max, TKHitRecord &rec) const {
	glm::vec3 oc = ray.origin() - center(ray.time());
	float a = glm::dot(ray.direction(), ray.direction());
	float b = glm::dot(oc, ray.direction());
	float c = glm::dot(oc, oc) - radius*radius;
	float  discriminant = b*b - a*c;
	if(discriminant > 0.0f){
		float temp = (-b - sqrt(b*b-a*c)) / a;
		if(temp < t_max && temp > t_min){
			rec.t = temp;
			rec.p = ray.point_at_parameter(rec.t);
			rec.normal = (rec.p - center(ray.time())) / radius;
			rec.mat_ptr = material;
			return true;
		}
		temp = (-b + sqrt(b*b-a*c))/a;
		if(temp < t_max && temp > t_min){
			rec.t = temp;
			rec.p = ray.point_at_parameter(rec.t);
			rec.normal = (rec.p - center(ray.time())) / radius;
			rec.mat_ptr = material;
			return true;
		}
	}
	return false;
}

glm::vec3 TKMovingSphere::center(float time) const {
	return center0 + ((time-time0)/(time1-time0))*(center1-center0);
}



