#include "ObjectPlacer.h"
#include "../Model Loading/ShaderTypes.h"

ObjectPlacer::ObjectPlacer() 
	: m_objectToPlace(nullptr), m_placePos(glm::vec3(0)), m_currentMesh(0)
{	
	m_highlightColor = glm::vec4(0.3f, 0.9f, 0.3f, 0.1f);

	m_meshes.push_back(m_loader.loadObj(MeshDefines::cube));
	m_meshes.push_back(m_loader.loadObj(MeshDefines::sphere));
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
	obj->SetMesh(m_meshes.at(m_currentMesh));
	obj->ComputeBoundingBox();
	obj->InitShader();
	GAMECONTEXT.AddObject(obj);
}

void ObjectPlacer::SwitchMesh(bool right)
{
	if (!m_objectToPlace)
	{
		m_objectToPlace = new GameObject();

		m_objectToPlace->SetVertexShader(ShaderTypes::ghostVertex);
		m_objectToPlace->SetFramentShader(ShaderTypes::ghostFragment);
		m_objectToPlace->SetMesh(m_meshes[m_currentMesh]);
		m_objectToPlace->ComputeBoundingBox();
		m_objectToPlace->InitShader();
		m_objectToPlace->SetPos(m_placePos);
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

		m_objectToPlace->SetMesh(m_meshes[m_currentMesh]);
	}
	
}

void ObjectPlacer::Update()
{
	//m_objectToPlace->Update();

	if (m_objectToPlace)
	{
		int numObj = GAMECONTEXT.GetObjectCount();

		for (int i = 0; i < numObj; ++i)
		{
			BoundingBox bb = GAMECONTEXT.GetObject(i)->GetBoundingBox();
			m_ray.RayCast(CAMERA.GetPos(), CAMERA.getCameraViewDirection(), 500.f, bb, m_placePos);
		}

		m_objectToPlace->SetPos(m_placePos);
		
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
	{
		m_objectToPlace->Render();
		GLuint color = glGetUniformLocation(m_objectToPlace->m_shader->getId(), "color");
		glUniform4fv(color, 1, glm::value_ptr(m_highlightColor));		
	}
		
}