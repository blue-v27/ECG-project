#pragma once

#include <glm.hpp>
#include <gtx\transform.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include "..\Graphics\window.h"
#include "..\Model Loading\mesh.h"
#include "..\Model Loading\texture.h"
#include "..\Model Loading\meshLoaderObj.h"
#include "..\Model Loading\MeshDefines.h"
#include "..\Shaders\shader.h"
#include "vector"
#include "PhysicsMask.h"

class IGameObject
{
private:
	std::vector<IGameObject*> m_children;
	IGameObject*			  m_parent = nullptr;

	PhysicsMask* m_phyMask = nullptr;
public:

	IGameObject();

	glm::vec3 m_pos;
	glm::vec3 m_relativePos;
	glm::vec3 m_scale;

	glm::vec3 m_viewDirection;
	glm::vec3 m_up;
	glm::vec3 m_right;

	float m_rotationOx;
	float m_rotationOy;

	float m_mass;

	void SetPos(glm::vec3 pos) 
	{ 
		if (m_parent)
			SetRelativePos(pos);
		else
			m_pos = pos;
	}

	glm::vec3 GetPos()						{ return m_pos; }	
	void	  SetRelativePos(glm::vec3 pos) { m_relativePos = pos; }
	glm::vec3 GetRelativePos()				{ return m_relativePos; }

	void	  SetDir(glm::vec3 pos) { m_viewDirection = pos; }
	glm::vec3 GetDir()				{ return m_viewDirection; }

	void	  SetUp(glm::vec3 pos) { m_up = pos; }
	glm::vec3 GetUp()			   { return m_up; }

	void	  SetRight(glm::vec3 pos) { m_right = pos; }
	glm::vec3 GetRight()			  { return m_right; }

	void  SetRotationOx(float rot) { m_rotationOx = rot; }
	float GetRotationOx()		   { return m_rotationOx; }

	void  SetRotationOy(float rot) { m_rotationOy = rot; }
	float GetRotationOy()		   { return m_rotationOy; }

	void		 SetChild(IGameObject* obj) { m_children.push_back(obj); obj->SetParent(this); }
	size_t       GetChildCound()			{ return m_children.size(); }
	IGameObject* GetChild(int index)	    { return m_children.at(index); }

	void		 SetParent(IGameObject* obj) { m_parent = obj; }
	IGameObject* GetParrent()				 { return m_parent; }

	void		 InitPhysics()	  { m_phyMask = new PhysicsMask(m_pos); }
	PhysicsMask* GetPhysicsMask() { return m_phyMask; }

	virtual void ProcessInput(Window* window, float deltaTime) = 0;
	virtual void Update() = 0;
	virtual void Init(char* mesh = nullptr) = 0;
	virtual void Render() = 0;

	void IProcessInput(Window* window, float deltaTime);
	void IUpdate();
	void IInit(char* mesh = nullptr);
	void IRender();
};