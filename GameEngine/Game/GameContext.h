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
#include "fSingleton.h"
#include "Light.h"
#include "OctTree.h"
#include "DataSturctures/fArray.h"

class GameContext : public fSingleton<GameContext>
{
private:
    Window* m_window = nullptr;
    Camera* m_camera = nullptr;

    float m_mousePosX = 400.0f;
    float m_mousePosY = 400.0f;

    float m_deltaTime = 0.f;

    float m_fov = 90.f;
    float m_targetFov = m_fov;

    bool m_isEditorActive = false;

    Array<GameObject*> m_objects;
    Array<GameObject*> m_objectsToRemove;
    Array<InteractiveGameObject*> m_interactiveObjects;
    Array<Light*> m_lights;

    Player* m_player = nullptr;

    bool m_isInPast = true;
    //OctreeNode* m_octTree = nullptr;

    std::vector<BoundingBox> m_worldBounds;

public:

    float getHeight() { return m_window->getHeight(); }

    void    SetWindow(Window* wnd) { m_window = wnd; }
    Window* GetWindow() const { return m_window; }

    void    SetCamera(Camera* camera) { m_camera = camera; }
    Camera* GetCamera() { return m_camera; }

    float GetFov()          { return m_fov; }
    void  SetFov(float fov) { m_fov = fov; }

    Player* GetPlayer() { return m_player; }

    void   SetLight(Light* obj)  { m_lights.PushLast(obj); }
    size_t GetLightCount()       { return m_lights.GetSize(); }
    Light* GetLight(int index)   { return m_lights.GetAt(index); }

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
        m_objects.PushLast(obj);
        if (m_objects.GetSize() > 1)
            obj->m_id = m_objects.GetAt(m_objects.GetSize() - 1)->m_id + 1;
    }

    void AddInteractiveGameObject(InteractiveGameObject* iobj)
    {
        m_interactiveObjects.PushLast(iobj);
        if (m_objects.GetSize() > 1)
            iobj->m_id = m_interactiveObjects.GetAt(m_interactiveObjects.GetSize() - 1)->m_id + 1;
    }

    void RemoveObject()
    {
#if 0
        if (m_objectsToRemove.GetSize())
        {
            for (GameObject* obj : m_objectsToRemove)
            {
               /* auto it = std::find(m_objects.begin(), m_objects.end(), obj);
                if (it != m_objects.end())
                {
                    delete* it;
                    m_objects.erase(it);
                    obj = nullptr;
                }*/
                obj->m_isActive = false;
            }

            m_objectsToRemove.clear();
        }    
#endif
    }

    void MarkForRemoval(GameObject* obj)
    {
        if (m_objectsToRemove.GetSize())
        {
            size_t size = m_objectsToRemove.GetSize();
            for(int i = 0; i < size; ++i)
                if (m_objectsToRemove.GetAt(i) == obj)
                    return;
        }

        m_objectsToRemove.PushLast(obj);
    }

    size_t GetObjectCount()
    {
        return m_objects.GetSize();
    }

    size_t GetInteractiveObjectCount()
    {
        return m_interactiveObjects.GetSize();
    }

    std::vector<GameObject*> GetObjectsInRange(glm::vec3 pos, float range);

    GameObject* GetObject(size_t index)
    {
        return m_objects.GetAt(index);
    }

    InteractiveGameObject* GetInteractiveObject(size_t index)
    {
        return m_interactiveObjects.GetAt(index);
    }

    void BuildOctree();

    void  SetDeltaTime(float time) { m_deltaTime = time; }
    float GetDeltaTime() { return m_deltaTime; }

    void TimeTravel();
    bool IsInPast() { return m_isInPast; }
    
    void UpdateFov()
    {
        if (glm::abs(m_fov - m_targetFov) > 0.01f)
            m_fov += 10.f * m_deltaTime;
        if (glm::abs(m_fov - m_targetFov) < 0.01f);
        m_fov -= 10.f * m_deltaTime;
        if (m_fov != m_targetFov && glm::abs(m_fov - m_targetFov) <= 0.1f)
            m_fov = m_targetFov;
    }
    void Start();
    void InitLights();
    void UpdateLights();
    void Update();
    void Render();

#define GAMECONTEXT GameContext::Instance()
};