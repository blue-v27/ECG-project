#include "ObjectPlacer.h"
#include "../Model Loading/ShaderTypes.h"

ObjectPlacer::ObjectPlacer() 
	: m_objectToPlace(nullptr), m_placePos(glm::vec3(0)), m_currentMesh(0)
{	
	m_highlightColor = glm::vec4(255.f, 255.f, 255.f, 50.f);

	m_meshes.push_back(MeshDefines::cube);
	m_meshes.push_back(MeshDefines::sphere);
}

ObjectPlacer::~ObjectPlacer()
{
	delete m_objectToPlace;
	m_objectToPlace = nullptr;
}

void ObjectPlacer::PlaceObject()
{
	GameObject* obj = new GameObject(m_objectToPlace);
	obj->SetFramentShader(ShaderTypes::basicFragment);
	obj->SetVertexShader(ShaderTypes::basicVertex);
	obj->Init(m_meshes.at(m_currentMesh));
	GAMECONTEXT.AddObject(obj);
}

void ObjectPlacer::SwitchMesh(bool right)
{
	if (!m_objectToPlace)
	{
		m_objectToPlace = new GameObject();

		m_objectToPlace->SetVertexShader(ShaderTypes::ghostVertex);
		m_objectToPlace->SetFramentShader(ShaderTypes::ghostFragment);
		m_objectToPlace->Init(m_meshes[1]);
		m_objectToPlace->SetPos(CAMERA.GetPos() + 200.f * CAMERA.getCameraViewDirection());
	}
	else
	{
		if (right)
		{
			if (m_currentMesh < m_meshes.size() - 1)
				m_currentMesh++;
			else
				m_currentMesh = 0;
		}
		else
		{
			if (m_currentMesh > 0)
				m_currentMesh--;
			else
				m_currentMesh = m_meshes.size() - 1;
		}

		Mesh mesh = m_loader.loadObj(m_meshes.at(m_currentMesh));
		m_objectToPlace->SetMesh(mesh);
	}
	
}

void ObjectPlacer::Update()
{
	//m_objectToPlace->Update();

	if (m_objectToPlace)
	{
		m_objectToPlace->SetPos(CAMERA.GetPos() + 200.f * CAMERA.getCameraViewDirection());
		
		if (GAMECONTEXT.GetWindow()->isMousePressed(GLFW_MOUSE_BUTTON_1))
		{
			PlaceObject();
		}
	}

	if (GAMECONTEXT.GetWindow()->isReleased(GLFW_KEY_P))
	{
		SwitchMesh(true);
	}
}

void ObjectPlacer::RenderGhost()
{
	if (m_objectToPlace)
		m_objectToPlace->Render();
}