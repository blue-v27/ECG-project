#include "Ray.h"

Ray::Ray()
{
	m_origin = CAMERA.GetPos();
	m_direction = CAMERA.getCameraViewDirection();
}

void Ray::RayCast(glm::vec3 origin, glm::vec3 direction, float range, BoundingBox other, glm::vec3& outHitPoint)
{
	glm::vec3 otherMin = other.GetMin();
	glm::vec3 otherMax = other.GetMax();

	float tmin = 0;
	float tmax = range;

	for (int i = 0; i < 3; ++i)
	{
		if (std::abs(direction[i]) >= 0.0001f)
		{
			float t1 = (otherMin[i] - origin[i]) / direction[i];
			float t2 = (otherMax[i] - origin[i]) / direction[i];

			tmin = std::max(std::min(t1, t2), tmin);
			tmax = std::min(std::max(t1, t2), tmax);
		}
		else
		{
			if (origin[i] < otherMin[i] || origin[i] > otherMax[i])
				return;
		}		
	}

	tmin = std::max(tmin, 0.0f);
	tmax = std::min(tmax, range);

	if (tmin > tmax)
		return;

	outHitPoint = origin + direction * tmin;
}
