#include "ObjectPlacer.h"

ObjectPlacer::ObjectPlacer() 
	: m_objectToPlace(nullptr), m_placePos(glm::vec3(0))
{	
	m_highlightColor = glm::vec4(255.f, 255.f, 255.f, 50.f);

	m_meshes.push_back(MeshDefines::cube);
	m_meshes.push_back(MeshDefines::sphere);
}
