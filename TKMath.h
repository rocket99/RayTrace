//
//
#include "TKPrefix.h"

#ifndef __TKMath_h__
#define __TKMath_h__
class TKMath {
public:
	static glm::vec3 random_in_unit_sphere();
	static glm::vec3 reflect(const glm::vec3 &v, const glm::vec3 &n);
	static bool refract(const glm::vec3 &v, const glm::vec3 &n, float ni_over_nbt, glm::vec3 &refracted);
	static float schlick(float cosine, float ref_idx);
};

#endif
