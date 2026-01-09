#include "Sky.h"
#include "GameContext.h"
void Sky::Start()
{
	m_shader = new Shader(ShaderTypes::skyVertex, ShaderTypes::skyFragment);
	m_mesh = MESH_DEFINES.GetMesh(SKY);
}

void Sky::Render()
{
    if (!m_shader) return;

    m_shader->use();
    glUseProgram(m_shader->getId());

    Window* window = GAMECONTEXT.GetWindow();
    Camera* camera = GAMECONTEXT.GetCamera();
    if (!window || !camera) return;

    glm::mat4 ProjectionMatrix = glm::perspective(GAMECONTEXT.GetFov(), window->getWidth() * 1.0f / window->getHeight(),
                                                   0.1f, 10000.0f);

    glm::vec3 camPos = camera->getCameraPosition();
    glm::vec3 camTarget = camPos + camera->getCameraViewDirection();
    glm::vec3 camUp = camera->getCameraUp();

    glm::mat4 ViewMatrix = glm::lookAt(camPos, camTarget, camUp);

    ViewMatrix = glm::mat4(glm::mat3(ViewMatrix));

    GLuint ProjectionLoc = glGetUniformLocation(m_shader->getId(), "projection");
    GLuint ViewLoc = glGetUniformLocation(m_shader->getId(), "view");

    glUniformMatrix4fv(ProjectionLoc, 1, GL_FALSE, &ProjectionMatrix[0][0]);
    glUniformMatrix4fv(ViewLoc, 1, GL_FALSE, &ViewMatrix[0][0]);

    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_FALSE);  

    m_mesh.draw(*m_shader); 

    glDepthMask(GL_TRUE);    
    glDepthFunc(GL_LESS);   
}
