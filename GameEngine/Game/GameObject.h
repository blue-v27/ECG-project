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
#include "BoundingBox.h"
#include "IGameObject.h"
#include "..\Shaders\ShaderManager.h"

enum class ObjectType { Basic, Player, Light, RangedWeapon, Water, Bullet };

class GameObject : public IGameObject
{
private:
	GLuint m_tex = 0;
	std::vector<Texture> m_textures;

	std::vector<GameObject*> m_children;
	GameObject* m_parent = nullptr;

	PhysicsMask* m_phyMask = nullptr;
public:
	glm::vec3 m_pos;
	glm::vec3 m_relativePos;
	glm::vec3 m_lastFramePos;
	glm::vec3 m_scale;
	glm::vec4 m_color;
	glm::mat4 m_lastFrameVP = glm::mat4(1.f);
	glm::mat4 m_MVPmat		= glm::mat4(1.f);

	glm::vec3 m_viewDirection;
	glm::vec3 m_up;
	glm::vec3 m_right;
	int m_id;

	glm::quat m_rot;
	glm::quat m_relativeRot;

	ObjectType m_type;

	float m_rotationOx;
	float m_rotationOy;

	bool m_isActive   = true;
	bool m_usePhysics = false;
	bool m_isDynamic  = false;
	bool m_isDirty	  = true;

	float m_mass;
	float m_health = 100.f;
	int   m_shaderId = 0;
	float m_isAnchor;

	Mesh		  m_mesh;
	Shader*		  m_shader = nullptr;

	glm::mat4 m_modelMatrix = glm::mat4(1.f);

	GameObject();
	GameObject(GameObject* obj);
	~GameObject();

	void	  SetPos(glm::vec3 pos);
	glm::vec3 GetPos()						{ return m_pos; }
	void	  SetRelativePos(glm::vec3 pos) { m_relativePos = pos; m_isDirty = true; }
	glm::vec3 GetRelativePos()				{ return m_relativePos; }

	void	  SetColor(glm::vec4 col) { m_color = col; }
	glm::vec4 GetColor()			  { return m_color; }

	void	  SetRotation(glm::quat rot);
	glm::quat GetRotation()			     { return m_rot; }
	
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);

	void	  SetScale(glm::vec3 scale) { m_scale = scale; m_isDirty = true;}
	glm::vec3 GetScale()				{ return m_scale; }

	void	  SetDir(glm::vec3 pos) { m_viewDirection = pos; m_isDirty = true;}
	glm::vec3 GetDir()				{ return m_viewDirection; }

	void	  SetUp(glm::vec3 pos) { m_up = pos; m_isDirty = true;}
	glm::vec3 GetUp()			   { return m_up; }

	void	  SetRight(glm::vec3 pos) { m_right = pos; m_isDirty = true;}
	glm::vec3 GetRight()			  { return m_right; }

	void RecomputeModel();

	void IsAnchor(bool val) { m_isAnchor = val; }
	bool IsAnchor()			{ return m_isAnchor; }

	void  SetRotationOx(float rot) { m_rotationOx = rot; m_isDirty = true;}
	float GetRotationOx()		   { return m_rotationOx; }

	void  SetRotationOy(float rot) { m_rotationOy = rot; m_isDirty = true;}
	float GetRotationOy()		   { return m_rotationOy; }

	void  SetShaderId(int shaderId) { m_shaderId = shaderId; }
	void  InitShader(int ShaderId)  { m_shader = SHADER_MANAGER.GetShader(ShaderId); m_shaderId = ShaderId; }

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
	BoundingBox m_renderBoundingBox;

	BoundingBox GetBoundingBox() { return m_boundingBox; }
	void ComputeBoundingBox(float height = 100.f);

	BoundingBox GetRenderBoundingBox() { return m_renderBoundingBox; }
	void ComputeRenderBoundingBox();

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

