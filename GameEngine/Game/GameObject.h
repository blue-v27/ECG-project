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

	std::vector<GameObject*> m_children;
	GameObject* m_parent = nullptr;

	PhysicsMask* m_phyMask = nullptr;

	char m_fragmentShader[128] = {0};
	char m_vertexShader[128]   = {0};
public:
	glm::vec3 m_pos;
	glm::vec3 m_relativePos;
	glm::vec3 m_scale;

	glm::vec3 m_viewDirection;
	glm::vec3 m_up;
	glm::vec3 m_right;
	int m_id;

	glm::quat m_rot;
	glm::quat m_relativeRot;

	float m_rotationOx;
	float m_rotationOy;

	bool m_isActive   = true;
	bool m_usePhysics = false;

	float m_mass;
	float m_health = 100.f;

	Mesh		  m_mesh;
	Shader*		  m_shader = nullptr;

	GameObject();
	GameObject(GameObject* obj);
	~GameObject();

	void	  SetPos(glm::vec3 pos);
	glm::vec3 GetPos()						{ return m_pos; }
	void	  SetRelativePos(glm::vec3 pos) { m_relativePos = pos; }
	glm::vec3 GetRelativePos()				{ return m_relativePos; }

	void	  SetRotation(glm::quat rot);
	glm::quat GetRotation()			     { return m_rot; }
	
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);

	void	  SetScale(glm::vec3 scale) { m_scale = scale; }
	glm::vec3 GetScale()				{ return m_scale; }

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

	void  SetFramentShader(char* path) { sprintf(m_fragmentShader, "%s", path); }
	void  SetVertexShader(char* path)  { sprintf(m_vertexShader, "%s", path); }
	char* GetFragmentShader()		   { return m_fragmentShader; }
	char* getVertexShader()			   { return m_vertexShader; }
	void  InitShader()				   { m_shader = new Shader(m_vertexShader, m_fragmentShader); }

	void		SetChild(GameObject* obj) { m_children.push_back(obj); obj->SetParent(this); }
	size_t      GetChildCound()			  { return m_children.size(); }
	GameObject* GetChild(int index)		  { return m_children.at(index); }

	void		SetParent(GameObject* obj) { m_parent = obj; }
	GameObject* GetParrent()			   { return m_parent; }
	void		RemoveParrentLink();
	void		RemoveChild(GameObject* obj);

	void		 InitPhysics()	   { m_phyMask = new PhysicsMask(m_pos); m_usePhysics = true; }
	PhysicsMask* GetPhysicsMask()  { return m_phyMask; }
	bool		 IsPhysicsEnable() { if (PhysicsMask* mask = m_phyMask) return true; return false; }
	void		 DisablePhysics();

	BoundingBox m_boundingBox;

	BoundingBox GetBoundingBox() { return m_boundingBox; }
	void ComputeBoundingBox();

	void SetMesh(Mesh mesh) { m_mesh = mesh; }

	void SetTexture(char* texturePath)
	{
		m_tex = loadBMP(texturePath);
		m_textures.push_back(Texture());
		m_textures[0].id = m_tex;
		m_textures[0].type = "texture_diffuse";
	}

	std::vector<Texture> GetTexture() { return m_textures; }

	void GetDamage(float damage) { m_health -= damage; }

	GameObject* AsGameObject() { return this; }

	void Render() override;
	void Init(Mesh* mesh = nullptr) override;
	void Update() override;
	void ProcessInput(Window* window, float deltaTime) override;
};

