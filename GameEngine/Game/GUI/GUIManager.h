#pragma once
#pragma once
#include <glm.hpp>
#include <gtx\transform.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include "../fSingleton.h"
#include "stb_truetype.h"
#include "../../Model Loading/mesh.h"
#include <unordered_map>


class GUIManager : public fSingleton<GUIManager>
{
private:
    GLuint  m_fontTexture = 0;
    Shader* m_shader = nullptr;
    GLuint  m_shaderProgram = 0;
    GLuint  VAO = 0, VBO = 0;
    stbtt_bakedchar m_charData[96];


    int m_atlasWidth = 512;
    int m_atlasHeight = 512;

    GLint m_projLocation = -1;
    GLint m_colorLocation = -1;

    glm::mat4 m_projection = glm::ortho(0.0f, 800.0f, 0.0f, 800.0f);

    GLuint m_whiteTexture = 0;
    std::unordered_map<std::string, GLuint> m_loadedTextures;

public:
	void Init();
	void DrawText(char* text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.f));
    GLuint LoadTexture(char* path);
    void DrawImage(char* path, float x, float y, float scale = 1.0f, const glm::vec3& tint = glm::vec3(1.0f));
    void DrawImage(GLuint textureID, float x, float y, float width, float height, const glm::vec3& tint = glm::vec3(1.0f)); 

#define GUI GUIManager::Instance()
};

