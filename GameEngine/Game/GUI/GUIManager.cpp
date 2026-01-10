#define STB_TRUETYPE_IMPLEMENTATION
#include "GUIManager.h"
#include "glfw3.h"
#include "String"
#include "../../Shaders/ShaderManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "../GameContext.h"

void GUIManager::Init()
{

    Window* wnd = GAMECONTEXT.GetWindow();
    m_projection = glm::ortho(0.0f, (float)wnd->getWidth(), 0.0f, (float)wnd->getHeight());

    std::string fontPath = "Resources/Fonts/ARIAL.TTF";

    unsigned char* ttf_buffer = new unsigned char[1 << 20];
    FILE* f = fopen(fontPath.c_str(), "rb");
    if (!f)
    {
        printf("Couldn't load font: %s\n", fontPath.c_str());
        return;
    }
    fread(ttf_buffer, 1, 1 << 20, f);
    fclose(f);

    m_atlasWidth = 720;
    m_atlasHeight = 1280;

    unsigned char* bitmap = new unsigned char[m_atlasWidth * m_atlasHeight];

    int bakeResult = stbtt_BakeFontBitmap(ttf_buffer, 0, 48.0f, bitmap,
        m_atlasWidth, m_atlasHeight, 32, 96, charData);

    if (bakeResult <= 0) {
        printf("Failed to bake font bitmap (result: %d)\n", bakeResult);
        delete[] bitmap;
        return;
    }

    glGenTextures(1, &m_fontTexture);
    glBindTexture(GL_TEXTURE_2D, m_fontTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_atlasWidth, m_atlasHeight, 0,
        GL_RED, GL_UNSIGNED_BYTE, bitmap);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    delete[] bitmap;

    m_shader        = SHADER_MANAGER.GetShader(TEXT);
    m_shaderProgram = m_shader->getId();  
    m_projLocation  = glGetUniformLocation(m_shaderProgram, "projection");
    m_colorLocation = glGetUniformLocation(m_shaderProgram, "textColor");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4 * 256, nullptr, GL_DYNAMIC_DRAW); // Enough for ~256 chars
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GUIManager::DrawText(char* text, float x, float y, float scale, glm::vec3 color)
{
    if (!m_shaderProgram) return;

    glDisable(GL_DEPTH_TEST);

    glUseProgram(m_shaderProgram);

    glUniform3fv(m_colorLocation, 1, glm::value_ptr(color));
    glUniformMatrix4fv(m_projLocation, 1, GL_FALSE, glm::value_ptr(m_projection)); // Use cached ortho

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_fontTexture);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    std::vector<float> vertices;
    vertices.reserve(strlen(text) * 24); // 6 verts × 4 floats

    float xpos = x;
    float ypos = y;

    for (const char* c = text; *c; ++c)
    {
        if (*c >= 32 && *c < 128)
        {
            stbtt_aligned_quad q;
            stbtt_GetBakedQuad(charData, m_atlasWidth, m_atlasHeight,
                *c - 32, &xpos, &ypos, &q, 1); 

            std::swap(q.t0, q.t1);

            float x0 = q.x0 * scale;
            float x1 = q.x1 * scale;
            float y0 = q.y0 * scale;
            float y1 = q.y1 * scale;

            
            vertices.insert(vertices.end(), 
                {
                x0, y1, q.s0, q.t1,  // bottom-left
                x1, y0, q.s1, q.t0,  // top-right
                x0, y0, q.s0, q.t0,  // top-left

                x0, y1, q.s0, q.t1,  // bottom-left
                x1, y1, q.s1, q.t1,  // bottom-right
                x1, y0, q.s1, q.t0   // top-right
                });
        }
        else if (*c == '\n')
        {
            ypos -= 48.0f * scale;  
            xpos = x;               
        }
    }

    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices.size() / 4);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnable(GL_DEPTH_TEST);

}

GLuint GUIManager::LoadTexture(const std::string& path)
{
    auto it = m_loadedTextures.find(path);
    if (it != m_loadedTextures.end()) return it->second;

    int w, h, channels;
    unsigned char* data = stbi_load(path.c_str(), &w, &h, &channels, 4);  // Force RGBA
    if (!data) 
    {
        printf("Failed to load image: %s\n", path.c_str());
        return 0;
    }

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    stbi_image_free(data);
    m_loadedTextures[path] = tex;
    return tex;
}

void GUIManager::DrawImage(const std::string& path, float x, float y, float scale, const glm::vec3& tint)
{
    GLuint tex = LoadTexture(path);
    if (tex == 0) return;

    int w, h;
    DrawImage(tex, x, y, 64.0f * scale, 64.0f * scale, tint);
}

void GUIManager::DrawImage(GLuint textureID, float x, float y, float width, float height, const glm::vec3& tint)
{
    glDisable(GL_DEPTH_TEST);

    glUseProgram(m_shaderProgram);
    glUniform3fv(m_colorLocation, 1, glm::value_ptr(tint));  // Reuse textColor uniform as tint
    glUniformMatrix4fv(m_projLocation, 1, GL_FALSE, glm::value_ptr(m_projection));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    std::vector<float> vertices = 
    {
        x,         y + height, 0.0f, 0.0f,  // top-left
        x + width, y + height, 1.0f, 0.0f,  // top-right
        x,         y,          0.0f, 1.0f,  // bottom-left

        x + width, y + height, 1.0f, 0.0f,
        x + width, y,          1.0f, 1.0f,
        x,         y,          0.0f, 1.0f
    };

    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);
}


