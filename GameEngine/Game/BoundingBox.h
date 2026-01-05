#pragma once

#include "vector"
#include <glm.hpp>
#include <gtx\transform.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include "..\Model Loading\mesh.h"

class BoundingBox
{
private:
	std::vector<Vertex> m_vertices;

	Vertex m_min;
	Vertex m_max;

	glm::vec3 m_worldMin;
	glm::vec3 m_worldMax;
	glm::vec3 m_intersectionPoint;
public:

	BoundingBox() = default;

	void   AddVertexArray(std::vector<Vertex> vertArr) { m_vertices = vertArr; }
	void   AddVertex(Vertex vert)					   { m_vertices.push_back(vert); }
	size_t GetVertexCount()							   { return m_vertices.size(); }
	Vertex GetVertexAt(int index)					   { return m_vertices.at(index); }

	void   SetMax(Vertex max) { m_max = max; }
	glm::vec3 GetMax()			 { return m_worldMax; }

	void   SetMin(Vertex min) { m_min = min; }
	glm::vec3 GetMin()		   { return m_worldMin; }

	void ComputeMinMax(float height);
	bool IsIntersecting(BoundingBox other);
	void UpdateWorldPos(glm::vec3 delta, glm::vec3 scale);
	bool HandleIntersection(glm::vec3& pos, BoundingBox other, glm::vec3 velocity = glm::vec3(100));
	glm::vec3 GetIntersectionPoint() { return m_intersectionPoint; }
};

