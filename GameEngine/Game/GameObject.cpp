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
    m_color         = glm::vec4(1);
        
	m_rotationOx = 0.0f;
	m_rotationOy = -90.0f;

	m_parent = nullptr;
	m_mass = 10;
    m_isActive = true;
    m_id = 0;
    m_health = 100.f;
    m_isAnchor = false;

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

GameObject::~GameObject()
{
    delete m_phyMask;
    m_phyMask = nullptr;
    delete m_shader;
    m_phyMask = nullptr;
}

void GameObject::Update()
{
    if (m_phyMask)
        m_phyMask->UpdatePhysics();

    m_boundingBox.UpdateWorldPos(GetPos(), m_scale);

    if (GameObject* parent = dynamic_cast<GameObject*>(GetParrent()))
    {
        m_pos = CAMERA.getCameraPosition() + CAMERA.getCameraViewDirection() * m_relativePos;
        m_rot = CAMERA.GetRotation() * m_relativeRot;
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

void GameObject::SetRotation(glm::quat rot)
{
    if (m_parent)
        m_relativeRot = rot;
    else
        m_rot = rot;
}

void GameObject::RotateX(float angle)
{
    if (m_parent)
        m_relativeRot = m_relativeRot * glm::angleAxis(angle, glm::vec3(1, 0, 0));
    else
        m_rot = m_rot * glm::angleAxis(angle, glm::vec3(1, 0, 0));
}

void GameObject::RotateY(float angle)
{
    if (m_parent)
        m_relativeRot = m_relativeRot * glm::angleAxis(angle, glm::vec3(0, 1, 0));
    else
        m_rot = m_rot * glm::angleAxis(angle, glm::vec3(0, 1, 0));
}

void GameObject::RotateZ(float angle)
{
    if (m_parent)
        m_relativeRot = m_relativeRot * glm::angleAxis(angle, glm::vec3(0, 0, 1));
    else
        m_rot = m_rot * glm::angleAxis(angle, glm::vec3(0, 0, 1));
}

void GameObject::RemoveParrentLink()
{
    if (m_parent)
    {
        m_parent->RemoveChild(this);
        m_parent = nullptr;
    }
        
}

void GameObject::RemoveChild(GameObject* obj)
{
    m_children.erase(std::remove(m_children.begin(), m_children.end(), obj), m_children.end());
}

void GameObject::DisablePhysics()
{
    delete m_phyMask;
    m_phyMask = nullptr;
    m_usePhysics = false;
}

void GameObject::ComputeBoundingBox(float height)
{
    m_boundingBox.AddVertexArray(m_mesh.vertices);
    m_boundingBox.ComputeMinMax(height);
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
    ModelMatrix *= glm::mat4_cast(m_rot);
    ModelMatrix *= glm::scale(glm::mat4(1.0f), m_scale);

    glm::mat4 ProjectionMatrix = glm::perspective(GAMECONTEXT.GetFov(), window->getWidth() * 1.0f / window->getHeight(), 0.1f, 10000.0f);
    glm::mat4 ViewMatrix = glm::lookAt(camera->getCameraPosition(),
        camera->getCameraPosition() + camera->getCameraViewDirection(),
        camera->getCameraUp());
    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

    glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

    glm::vec4 lightColor = GAMECONTEXT.GetLight()->GetColor();
    glm::vec3 lightPos   = GAMECONTEXT.GetLight()->GetPos();
    glUniform3f(glGetUniformLocation(m_shader->getId(), "lightColor"), lightColor.x, lightColor.y, lightColor.z);
    glUniform3f(glGetUniformLocation(m_shader->getId(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    glUniform3f(glGetUniformLocation(m_shader->getId(), "viewPos"),
        camera->getCameraPosition().x,
        camera->getCameraPosition().y,
        camera->getCameraPosition().z);

    m_mesh.draw(*m_shader);
}