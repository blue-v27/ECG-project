#pragma once

#include <glm.hpp>
#include <gtx\transform.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include "..\Graphics\window.h"
#include "vector"
#include "..\Model Loading\mesh.h"
#include "..\Model Loading\texture.h"
#include "..\Model Loading\meshLoaderObj.h"
#include "..\Model Loading\MeshDefines.h"
#include "..\Shaders\shader.h"
#include "GameObject.h"
#include "..\Camera\camera.h"    
#include "Player.h"

class GameContext
{
private:
    GameContext() = default;
    ~GameContext() = default;

private:
    Window* m_window = nullptr;
    Camera* m_camera = nullptr;

    float m_mousePosX = 400.0f;
    float m_mousePosY = 400.0f;

    float m_deltaTime = 0.f;

    std::vector<GameObject*> m_objects;

    glm::vec3 m_lightPos;
    glm::vec4 m_lightColor;
    
    Player* m_player = nullptr;
public:
    static GameContext& Instance()
    {
        static GameContext instance; 
        return instance;
    }

    GameContext(const GameContext&) = delete;
    GameContext& operator=(const GameContext&) = delete;
    GameContext(GameContext&&) = delete;
    GameContext& operator=(GameContext&&) = delete;

    void    SetWindow(Window* wnd) { m_window = wnd; }
    Window* GetWindow() const      { return m_window; }

    void    SetCamera(Camera* camera) { m_camera = camera; }
    Camera* GetCamera()               { return m_camera; }

    void SetLightColor(glm::vec4 col) { m_lightColor = col; }
    void SetLightPos(glm::vec3 pos)   { m_lightPos = pos; }

    glm::vec3 getLightPos()   { return m_lightPos; }
    glm::vec4 getLightColor() { return m_lightColor; }

    glm::vec2 GetMousePos() const { return glm::vec2(m_mousePosX, m_mousePosY);}

    void SetMousePos(glm::vec2 pos)
    {
        m_mousePosX = pos.x;
        m_mousePosY = pos.y;
    }

    void AddPlayer(Player* player)
    {
        m_player = player;
    }

    void AddObject(GameObject* obj)
    {
        m_objects.push_back(obj);
    }

    size_t GetObjectCount() const
    {
        return m_objects.size();
    }

    GameObject* GetObject(size_t index)
    {
        return m_objects.at(index);
    }

    void SetDeltaTime(float time) { m_deltaTime = time; }
    float GetDeltaTime() { return m_deltaTime; }
    

    void Update();

    void Render();

#define GAMECONTEXT GameContext::Instance()
};