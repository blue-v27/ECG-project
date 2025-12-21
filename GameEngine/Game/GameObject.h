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
public:

	GameObject() = default;

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

