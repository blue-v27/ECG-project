#pragma once
#include "GameContext.h"
class ObjectPlacer
{
private:
	std::vector<Mesh> m_meshes;
	GameObject* m_objectToPlace;

	glm::vec3 m_placePos;
	glm::vec4 m_highlightColor;

public:
	ObjectPlacer();

	void PlaceObject();
	void RemoveObject();
	void SwitchMesh();
	void SwitchTexture();
};

