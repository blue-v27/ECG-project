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
    m_lastFramePos = m_pos;
    m_isDirty = true;
}

GameObject::GameObject(GameObject* obj)
{
    m_pos = obj->m_pos;
    m_mesh = obj->m_mesh;
    m_textures = obj->m_textures;
    m_scale = obj->m_scale;
    m_mass = obj->m_mass;
    m_rotationOx = obj->m_rotationOx;
    m_rotationOy = obj->m_rotationOy;
    m_isActive = true;
    m_id = 0;
    m_shaderId = obj->m_shaderId;
    m_rot = obj->m_rot;
}

GameObject::~GameObject()
{
    if (m_phyMask)
    {
        //delete m_phyMask;
        m_phyMask = nullptr;
    }
    if (m_shader)
    {
        //delete m_shader;
        m_phyMask = nullptr;
    }  
}

void GameObject::Update()
{
    m_lastFramePos = m_pos;

    if (m_phyMask && !CAMERA.FreeCam())
        m_phyMask->UpdatePhysics();

    if (m_lastFramePos != m_pos)
    {
        m_isDirty = true;
    }

    if (GameObject* parent = GetParrent())
    {
        if (parent->m_isDirty)
        {
            m_pos = CAMERA.getCameraPosition() + CAMERA.getCameraViewDirection() * m_relativePos;
            m_rot = CAMERA.GetRotation() * m_relativeRot;

            m_isDirty = true;
        }       
    }

    if (m_isDirty)
        for (GameObject* child : m_children)
            child->m_isDirty = true;

    if (m_isDirty)
        m_boundingBox.UpdateWorldPos(GetPos(), m_scale);
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
        m_mesh = MESH_DEFINES.GetMesh(MESH_CUBE);
    }

    ComputeBoundingBox();
    InitShader(m_shaderId);
}

void GameObject::SetPos(glm::vec3 pos)
{
    if (m_parent)
        SetRelativePos(pos);
    else
        m_pos = pos;

    m_isDirty = true;
}

void GameObject::SetRotation(glm::quat rot)
{
    if (m_parent)
        m_relativeRot = rot;
    else
        m_rot = rot;

    m_isDirty = true;
}

void GameObject::RotateX(float angle)
{
    if (m_parent)
        m_relativeRot = m_relativeRot * glm::angleAxis(angle, glm::vec3(1, 0, 0));
    else
    {
        m_rot         = m_rot * glm::angleAxis(angle, glm::vec3(1, 0, 0));
        m_relativeRot = m_rot;
    }

    m_isDirty = true;
}

void GameObject::RotateY(float angle)
{
    if (m_parent)
        m_relativeRot = m_relativeRot * glm::angleAxis(angle, glm::vec3(0, 1, 0));
    else
        m_rot = m_rot * glm::angleAxis(angle, glm::vec3(0, 1, 0));

    m_isDirty = true;
}

void GameObject::RotateZ(float angle)
{
    if (m_parent)
        m_relativeRot = m_relativeRot * glm::angleAxis(angle, glm::vec3(0, 0, 1));
    else
        m_rot = m_rot * glm::angleAxis(angle, glm::vec3(0, 0, 1));

    m_isDirty = true;
}

void GameObject::RecomputeModel()
{
    if (m_isDirty)
    {
        m_modelMatrix = glm::translate(glm::mat4(1.0f), m_pos);
        m_modelMatrix *= glm::mat4_cast(m_rot);
        m_modelMatrix *= glm::scale(glm::mat4(1.0f), m_scale);
        m_isDirty = false;
    }

    m_MVPmat = CAMERA.GetVPMat() * m_modelMatrix;

    glUniformMatrix4fv(m_shader->m_modelMatrixID, 1, GL_FALSE, &m_modelMatrix[0][0]);
    glUniformMatrix4fv(m_shader->m_MVPMatrixID,   1, GL_FALSE, &m_MVPmat[0][0]);
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
    if (!m_shader) 
        return;

    m_shader->use();

    Window* window = GAMECONTEXT.GetWindow();
    Camera* camera = GAMECONTEXT.GetCamera();
    
    if (!window || !camera) 
        return;

    RecomputeModel();   

    m_mesh.draw(*m_shader);
}