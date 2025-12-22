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
#include "BoundingBox.h"
#include "IGameObject.h"

class GameObject : public IGameObject
{
private:
	GLuint m_tex = 0;
	std::vector<Texture> m_textures;

	MeshLoaderObj m_loader;
	Mesh m_mesh;
	Shader* m_shader = nullptr;

	std::vector<GameObject*> m_children;
	GameObject* m_parent = nullptr;

	PhysicsMask* m_phyMask = nullptr;

	char* m_fragmentShader = nullptr;
	char* m_vertexShader   = nullptr;
public:
	glm::vec3 m_pos;
	glm::vec3 m_relativePos;
	glm::vec3 m_scale;

	glm::vec3 m_viewDirection;
	glm::vec3 m_up;
	glm::vec3 m_right;

	float m_rotationOx;
	float m_rotationOy;

	float m_mass;

	GameObject();

	void SetPos(glm::vec3 pos);

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

	void SetFramentShader(char* path) { m_fragmentShader = path; }
	void SetVertexShader(char* path)  { m_vertexShader = path; }

	void		SetChild(GameObject* obj) { m_children.push_back(obj); obj->SetParent(this); }
	size_t      GetChildCound()			  { return m_children.size(); }
	GameObject* GetChild(int index)		  { return m_children.at(index); }

	void		SetParent(GameObject* obj) { m_parent = obj; }
	GameObject* GetParrent()			   { return m_parent; }

	void		 InitPhysics()	  { m_phyMask = new PhysicsMask(m_pos); }
	PhysicsMask* GetPhysicsMask() { return m_phyMask; }

	BoundingBox m_boundingBox;

	BoundingBox GetBoundingBox() { return m_boundingBox; }

	void SetMesh(Mesh mesh) { m_mesh = mesh; }

	void SetTexture(char* texturePath)
	{
		m_tex = loadBMP(texturePath);
		m_textures.push_back(Texture());
		m_textures[0].id = m_tex;
		m_textures[0].type = "texture_diffuse";
	}

	void Render() override;
	void Init(char* mesh = nullptr) override;
	void Update() override;
	void ProcessInput(Window* window, float deltaTime) override;
};

