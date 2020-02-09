//
//
#ifndef __TKCamera_h__
#define __TKCamera_h__

#include "TKPrefix.h"
#include "TKRay.h"

class TKCamera{
public:
	TKCamera(){
		lower_left_corner = glm::vec3(-2.0f, -1.0f, -1.0f);
		horizontal = glm::vec3(4.0f, 0.0f ,0.0f);
		vertical = glm::vec3(0.0f, 2.0f, 0.0f);
		origin = glm::vec3(0.0f, 0.0f ,0.0f);
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

