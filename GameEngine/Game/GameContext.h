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
#include "InteractiveGameObject.h"
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

    float m_fov       = 90.f;
    float m_targetFov = m_fov;

    bool m_isEditorActive = false;

    std::vector<GameObject*> m_objects;
    std::vector<InteractiveGameObject*> m_interactiveObjects;

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

    float GetFov()          { return m_fov; }
    void  SetFov(float fov) { m_fov = fov;  }

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

    void RemoveObject(GameObject* obj)
    {
        m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), obj), m_objects.end());
        delete obj;
        obj = nullptr;
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
    
    void UpdateFov();

    void Start();

    void Update();

    void Render();

#define GAMECONTEXT GameContext::Instance()
};