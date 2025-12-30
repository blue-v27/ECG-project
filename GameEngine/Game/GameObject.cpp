#include "GameObject.h"
#include "GameContext.h"
#include "../Model Loading/ShaderTypes.h"

GameObject::GameObject()
{
    m_pos			= glm::vec3(0);
	m_scale			= glm::vec3(1.f);
	m_viewDirection = glm::vec3(0);
	m_up			= glm::vec3(0);
	m_right			= glm::vec3(0);

	m_rotationOx = 0.0f;
	m_rotationOy = -90.0f;

	m_parent = nullptr;
	m_mass = 10;
    m_isActive = true;
    m_id = 0;

    snprintf(m_fragmentShader, 128, "%s", ShaderTypes::basicFragment);
    snprintf(m_vertexShader, 128, "%s", ShaderTypes::basicVertex);
}

GameObject::GameObject(GameObject* obj)
{
    snprintf(m_fragmentShader, 128, "%s", obj->m_fragmentShader);
    snprintf(m_vertexShader, 128, "%s", obj->m_vertexShader);
    m_pos = obj->m_pos;
    m_mesh = obj->m_mesh;
    m_textures = obj->m_textures;
    m_scale = obj->m_scale;
    m_mass = obj->m_mass;
    m_rotationOx = obj->m_rotationOx;
    m_rotationOy = obj->m_rotationOy;
    m_isActive = true;
    m_id = 0;
}

void GameObject::Update()
{
    if (m_phyMask)
        m_phyMask->UpdatePhysics();

    m_boundingBox.UpdateWorldPos(GetPos(), m_scale);

    if (GameObject* parrent = dynamic_cast<GameObject*>(GetParrent()))
    {
        m_pos = parrent->m_pos + m_relativePos;
    }
}

void GameObject::ProcessInput(Window* window, float deltaTime)
{
    
}

void GameObject::Init(Mesh* mesh)
{
    if (Camera* cam = dynamic_cast<Camera*>(this))
        return;

    if (mesh)
    {
        m_mesh = *mesh;
    }
    else
    {
        m_mesh = MESH_DEFINES.GetMesh(CUBE);
    }

    ComputeBoundingBox();
    InitShader();
}

void GameObject::SetPos(glm::vec3 pos)
{
    if (m_parent)
        SetRelativePos(pos);
    else
        m_pos = pos;
}

void GameObject::ComputeBoundingBox()
{
    m_boundingBox.AddVertexArray(m_mesh.vertices);
    m_boundingBox.ComputeMinMax();
}

void GameObject::Render()
{
    if (!m_shader) return;

    m_shader->use();
    glUseProgram(m_shader->getId());

    Window* window = GAMECONTEXT.GetWindow();
    Camera* camera = GAMECONTEXT.GetCamera();
    if (!window || !camera) return;

    GLuint MatrixID2     = glGetUniformLocation(m_shader->getId(), "MVP");
    GLuint ModelMatrixID = glGetUniformLocation(m_shader->getId(), "model");

    glm::vec3 renderPos = glm::vec3(0);

    glm::mat4 ModelMatrix = glm::translate(glm::mat4(1.0f), m_pos);
    ModelMatrix *= glm::scale(glm::mat4(1.0f), m_scale);
    glm::mat4 ProjectionMatrix = glm::perspective(GAMECONTEXT.GetFov(), window->getWidth() * 1.0f / window->getHeight(), 0.1f, 10000.0f);
    glm::mat4 ViewMatrix = glm::lookAt(camera->getCameraPosition(),
        camera->getCameraPosition() + camera->getCameraViewDirection(),
        camera->getCameraUp());
    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

    glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

    glm::vec4 lightColor = GAMECONTEXT.getLightColor();
    glm::vec3 lightPos = GAMECONTEXT.getLightPos();
    glUniform3f(glGetUniformLocation(m_shader->getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
    glUniform3f(glGetUniformLocation(m_shader->getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    glUniform3f(glGetUniformLocation(m_shader->getId(), "viewPos"),
        camera->getCameraPosition().x,
        camera->getCameraPosition().y,
        camera->getCameraPosition().z);

    m_mesh.draw(*m_shader);
}