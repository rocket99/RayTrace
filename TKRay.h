#ifndef __TKRay_h__
#define __TKRay_h__

#include "TKPrefix.h"

class TKRay {
public:
	TKRay();
	~TKRay();
	TKRay(const TKRay &ray);
	TKRay(const glm::vec3 &o, const glm::vec3 &d);
	
	glm::vec3 origin() const;
	glm::vec3 direction() const;
	glm::vec3 point_at_parameter(float t);
	glm::vec3 point_at_parameter(float t) const ;
private:
	glm::vec3 m_origin;
	glm::vec3 m_direction;
};

#endif
