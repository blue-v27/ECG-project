#include "Water.h"
#include "../Model Loading/TextureDefine.h"
#include "../Model Loading/ShaderTypes.h"
#include "../Model Loading/MeshDefines.h"
#include "GameContext.h"

Water::Water() : m_waveHeight(1.f), m_waveSpeed(1.f), m_waveLength(2.f)
{

}

void Water::Init(char* mesh)
{ 
    SetTexture(TextureDefine::Water);
    m_mesh = m_loader.loadObj(MeshDefines::water, GetTexture());

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

    GLuint MatrixID2 = glGetUniformLocation(m_shader->getId(), "MVP");
    GLuint ModelMatrixID = glGetUniformLocation(m_shader->getId(), "model");
    GLuint time = glGetUniformLocation(m_shader->getId(), "time");
    GLuint amplitude = glGetUniformLocation(m_shader->getId(), "amplitude");
    GLuint waveLength = glGetUniformLocation(m_shader->getId(), "waveLength");

    glm::vec3 renderPos = glm::vec3(0);

    glm::mat4 ModelMatrix = glm::translate(glm::mat4(1.0f), m_pos);
    ModelMatrix *= glm::scale(glm::mat4(1.0f), m_scale);
    glm::mat4 ProjectionMatrix = glm::perspective(90.0f, window->getWidth() * 1.0f / window->getHeight(), 0.1f, 10000.0f);
    glm::mat4 ViewMatrix = glm::lookAt(camera->getCameraPosition(),
        camera->getCameraPosition() + camera->getCameraViewDirection(),
        camera->getCameraUp());
    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

    glUniformMatrix4fv(MatrixID2, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
    glUniform1f(time, glfwGetTime());
    glUniform1f(amplitude, m_scale.x);
    glUniform1f(waveLength, m_scale.x);

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
