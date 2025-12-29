#pragma once
#include "Ray.h"
class ObjectPlacer
{
private:
	GameObject* m_objectToPlace;

	glm::vec3 m_placePos;
	glm::vec4 m_placeColor;
	glm::vec4 m_highlightColor;

	bool m_isActive = false;
	int  m_currentMesh = 0;

	Ray m_ray;

public:
	ObjectPlacer();
	~ObjectPlacer();

	void PlaceObject();
	void RemoveObject();
	void SwitchMesh(bool right = true);
	void SwitchTexture();

	void Update();
	void RenderGhost();

	void isActive(bool val) { m_isActive = val; }
	bool isActive()			{ return m_isActive; }
};

