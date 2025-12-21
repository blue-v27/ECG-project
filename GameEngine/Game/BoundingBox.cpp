#include "BoundingBox.h"

void BoundingBox::ComputeMinMax()
{
	size_t len = m_vertices.size();

	glm::vec3 min = glm::vec3(INT_MAX);
	glm::vec3 max = glm::vec3(INT_MIN);

	for (int i = 0; i < len; ++i)
	{
		glm::vec3 vert = m_vertices.at(i).pos;

		min = glm::vec3(vert.x < min.x ? vert.x : min.x,
						vert.y < min.y ? vert.y : min.y,
						vert.z < min.z ? vert.z : min.z);

		max = glm::vec3(vert.x > max.x ? vert.x : max.x,
						vert.y > max.y ? vert.y : max.y,
						vert.z > max.z ? vert.z : max.z);
	}

	m_min.pos = min;
	m_max.pos = max;

	m_worldMax = max;
	m_worldMin = min;
}

bool BoundingBox::IsIntersecting(BoundingBox other)
{
	// Check if bounding box is valid
	if (other.m_worldMax == other.m_worldMin)
		return false;

	bool overlapX = m_worldMin.x <= other.m_worldMax.x && m_worldMax.x >= other.m_worldMin.x;

	bool overlapY = m_worldMin.y <= other.m_worldMax.y && m_worldMax.y >= other.m_worldMin.y;

	bool overlapZ = m_worldMin.z <= other.m_worldMax.z && m_worldMax.z >= other.m_worldMin.z;

	return overlapX && overlapY && overlapZ;

}

void BoundingBox::UpdateWorldPos(glm::vec3 delta)
{
	m_worldMin = m_min.pos + delta;
	m_worldMax = m_max.pos + delta;
}

bool BoundingBox::HandleIntersection(glm::vec3& pos, BoundingBox other, glm::vec3 velocity)
{
	if (!IsIntersecting(other))
		return false;

	// If we are coliding we need to compute a counter force 
	// Check overlap values
	float overlapLeft	  = other.m_worldMax.x - m_worldMin.x;
	float overlapRight	  = m_worldMax.x - other.m_worldMin.x;
	float overlapTop	  = m_worldMax.y - other.m_worldMin.y;
	float overlapBottom	  = other.m_worldMax.y - m_worldMin.y;
	float overlapForward  = m_worldMax.z - other.m_worldMin.z;
	float overlapBackward = other.m_worldMax.z - m_worldMin.z;

	// If any overlap is negative than there is no collission
	if (overlapLeft <= 0 || overlapRight <= 0 || overlapTop <= 0 || overlapBottom <= 0 ||
		overlapForward <= 0 || overlapBackward <= 0)
		return false;

	// Check for penetraion
	float penX = overlapLeft < overlapRight ? overlapLeft : -overlapRight;
	float penY = overlapBottom < overlapTop ? overlapBottom : -overlapTop;
	float penZ = overlapBackward < overlapForward ? overlapBackward : -overlapForward;

	// Add peneteration to the player to keep it in place

	float minPen = std::min(std::abs(penX), std::min(std::abs(penY), std::abs(penZ)));
	
	if (std::abs(penX) == minPen)
		pos.x += penX;
	else if (std::abs(penY) == minPen)		
		pos.y += penY;
	else
		pos.z += penZ;

	return true;
}
