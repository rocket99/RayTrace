#include "TKRay.h"

TKRay::TKRay(){
	m_origin = glm::vec3(0.0, 0.0, 0.0);
	m_direction = glm::vec3(1.0, 0.0, 0.0);
}

TKRay::~TKRay(){}

TKRay::TKRay(const TKRay &ray){
	m_origin = ray.m_origin;
	m_direction = ray.m_direction;
}

TKRay::TKRay(const glm::vec3 &o, const glm::vec3 &d){
	m_origin = o;
	m_direction = d;
}

glm::vec3 TKRay::origin() const {
	return m_origin;
}

glm::vec3 TKRay::direction() const {
	return m_direction;
}

glm::vec3 TKRay::point_at_parameter(float t){
	return m_origin + m_direction * t;
}

glm::vec3 TKRay::point_at_parameter(float t) const {
	return m_origin + m_direction * t;
}
 
