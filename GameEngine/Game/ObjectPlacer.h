#pragma once
#include "GameContext.h"
class ObjectPlacer
{
private:
	std::vector<char*> m_meshes;
	GameObject* m_objectToPlace;

	glm::vec3 m_placePos;
	glm::vec4 m_highlightColor;

	MeshLoaderObj m_loader;

	bool m_isActive = false;

public:
	ObjectPlacer();

	void PlaceObject();
	void RemoveObject();
	void SwitchMesh();
	void SwitchTexture();

	void isActive(bool val) { m_isActive = val; }
	bool isActive()			{ return m_isActive; }
};

