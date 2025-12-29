#include "Water.h"
#include "../Model Loading/TextureDefine.h"
#include "../Model Loading/ShaderTypes.h"
#include "../Model Loading/MeshDefines.h"
#include "GameContext.h"

Water::Water() : m_waveHeight(1.f), m_waveSpeed(1.f), m_waveLength(2.f)
{

}

void Water::Init(Mesh* mesh)
{ 
    m_mesh = MESH_DEFINES.GetMesh(WATER);

    m_boundingBox.AddVertexArray(m_mesh.vertices);
    m_boundingBox.ComputeMinMax();

    m_shader = new Shader(ShaderTypes::waterVertex, ShaderTypes::waterFragment);
}

void Water::Render()
{
    if (!m_shader) 
        return;

    m_shader->use();
    glUseProgram(m_shader->getId());

    Window* window = GAMECONTEXT.GetWindow();
    Camera* camera = GAMECONTEXT.GetCamera();
    if (!window || !camera) 
        return;

    GLuint time = glGetUniformLocation(m_shader->getId(), "time");
    GLuint amplitude = glGetUniformLocation(m_shader->getId(), "amplitude");
    GLuint waveLength = glGetUniformLocation(m_shader->getId(), "waveLength");
    glUniform1f(time, glfwGetTime());
    glUniform1f(amplitude, m_scale.x);
    glUniform1f(waveLength, m_scale.x);

    GameObject::Render();
}
