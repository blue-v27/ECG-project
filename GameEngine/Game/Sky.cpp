#include "Sky.h"
#include "GameContext.h"

void Sky::Start()
{
	m_shader = SHADER_MANAGER.GetShader(SKY);
	
    std::vector<const char*> faces
    { 
        "Resources/Textures/right.bmp", 
        "Resources/Textures/left.bmp", 
        "Resources/Textures/top.bmp", 
        "Resources/Textures/bottom.bmp", 
        "Resources/Textures/front.bmp", 
        "Resources/Textures/back.bmp" 
    };

    cubemapTexture = loadCubemap(faces);

    // Cube vertices for skybox
    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);
}

void Sky::Render()
{
    if (!m_shader) return;

    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);  // skybox drawn behind everything
    m_shader->use();

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

    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

    // 3?? Draw the cube
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    // 4?? Re-enable standard depth testing
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
}
