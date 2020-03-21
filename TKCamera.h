//
//
#ifndef __TKCamera_h__
#define __TKCamera_h__

#include "TKPrefix.h"
#include "TKMath.h"
#include "TKRay.h"

class TKCamera{
public:
	TKCamera(glm::vec3 lookfrom, glm::vec3 lookat,
			 glm::vec3 vup, float vfov, float aspect,
			 float aperture, float focus_dist, float t0, float t1){
		time0 = t0;
		time1 = t1;
		lens_radius = aperture * 0.5f;
	   
		float theta = vfov*M_PI/180.0f;
		float half_height = tan(0.5f*theta);
		float half_width = aspect * half_height;
		origin = lookfrom;
		w = glm::normalize(lookfrom-lookat);
		u = glm::normalize(glm::cross(vup, w));
		v = glm::cross(w, u);
		
		lower_left_corner = origin - half_width*focus_dist*u - half_height*focus_dist*v - w*focus_dist;
		horizontal = 2.0f * half_width * focus_dist * u;
		vertical   = 2.0f * half_height * focus_dist * v;
	}
	
	TKRay getRay(float s, float t){
		glm::vec3 rd = lens_radius * TKMath::random_in_unit_disk();
		glm::vec3 offset = u*rd.x + v*rd.y;
		float time = time0+drand48()*(time1-time0);
		return TKRay(origin + offset,
					 lower_left_corner + s*horizontal + t*vertical - origin - offset, time);
	}
	
	glm::vec3 origin;
	glm::vec3 lower_left_corner;
	glm::vec3 horizontal;
	glm::vec3 vertical;
	glm::vec3 u, v, w;
	float lens_radius;
	float time0, time1;
};


#endif

