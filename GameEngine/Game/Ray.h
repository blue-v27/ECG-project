#pragma once
#include "GameContext.h"

class Ray
{
public:
	glm::vec3 m_origin;
	glm::vec3 m_direction;

	Ray();

	void RayCast(glm::vec3 origin, glm::vec3 direction, float range, BoundingBox other, glm::vec3& outHitPoint);
};

