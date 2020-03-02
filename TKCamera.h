//
//
#ifndef __TKCamera_h__
#define __TKCamera_h__

#include "TKPrefix.h"
#include "TKRay.h"

class TKCamera{
public:
	TKCamera(glm::vec3 lookfrom, glm::vec3 lookat, glm::vec3 vup, float vfov, float aspect){
		glm::vec3 u, v, w;
		float theta = vfov*M_PI/180.0f;
		float half_height = tan(0.5f*theta);
		float half_width = aspect * half_height;
		origin = lookfrom;
		w = glm::normalize(lookfrom-lookat);
		u = glm::normalize(glm::cross(vup, w));
		v = glm::cross(w, u);
		
		lower_left_corner = glm::vec3(-half_width, -half_height, -1.0f);
		lower_left_corner = origin - half_width*u - half_height*v - w;
		horizontal = 2.0f*half_width * u;
		vertical = 2.0f*half_height * v;
	}
	
	TKRay getRay(float u, float v){
		return TKRay(origin, lower_left_corner+u*horizontal+v*vertical-origin);
	}
	
	glm::vec3 origin;
	glm::vec3 lower_left_corner;
	glm::vec3 horizontal;
	glm::vec3 vertical;
};


#endif

