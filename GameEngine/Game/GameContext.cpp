#include "GameContext.h"
#include "SubModes/SceneEditorSubMode.h"
#include "SaveManager.h"
#include "../Model Loading/MeshDefines.h"
#include "GUI/Hud.h"

std::vector<GameObject*> GameContext::GetObjectsInRange(glm::vec3 pos, float range)
{
    std::vector<GameObject*> arr;

    if (m_objects.size())
    {
        for (GameObject* obj : m_objects)
        {
            if (obj)
            {
                BoundingBox bb = obj->GetBoundingBox();
                if (glm::distance(pos, bb.GetMax()) > range &&
                    glm::distance(pos, obj->m_pos) > range &&
                    glm::distance(pos, bb.GetMin()) > range)
                    continue;

                arr.push_back(obj);
            }
        }
    }

    return arr;
}

void GameContext::Start()
{
    if (&MESH_DEFINES)
        MESH_DEFINES.Start();

    if (&SAVE_MANAGER)
        SAVE_MANAGER.LoadObjects();
}

void GameContext::Update()
{
    if (&CAMERA)
        CAMERA.Update();

    if(&SCENE_EDITOR)
        SCENE_EDITOR.Update();

    if (m_window->IsReleased(GLFW_KEY_ENTER))
        SCENE_EDITOR.ToggleEditMode();   

    PhysicsMask* mask = nullptr;

    if(m_player)
        mask = m_player->GetPhysicsMask();

    if (mask)
        mask->SetLastFramePos(m_player->m_pos);

    if (m_objects.size())
    {
        for (GameObject* obj : m_objects)
        {
            if (obj)
            {                       
                if (m_player)
                {
                    BoundingBox bb = obj->GetBoundingBox();
                    if (glm::distance(m_player->m_pos, bb.GetMax()) > 100.f &&
                        glm::distance(m_player->m_pos, obj->m_pos) > 100.f &&
                        glm::distance(m_player->m_pos, bb.GetMin()) > 100.f)
                        continue;

                    obj->IUpdate();

                    if (Player* player = dynamic_cast<Player*>(obj))
                    {

                    }
                    else
                    {
                        glm::vec3 velocity = glm::vec3(100);
                                              
                        if(mask)
                            velocity = mask->GetVelocity();

                        if (m_player->m_boundingBox.HandleIntersection(m_player->m_pos, obj->GetBoundingBox(), velocity))
                        {
                            if (mask && mask->GetVelocity().y <= 0)
                            {
                                m_player->SetGrounded(true);
                                mask->SetVelocityY(0.f);
                            }
                        }
                    }
                }

                if (Player* player = dynamic_cast<Player*>(obj))
                    if(PhysicsMask* pMask = player->GetPhysicsMask())
                        pMask->ComputeVelocity();
            }
        }
    }

    if (m_interactiveObjects.size())
    {
        for (InteractiveGameObject* iobj : m_interactiveObjects)
        {          
            if (m_player)
            {
                if (iobj->GetParrent() != m_player)
                {
                    BoundingBox bb = iobj->GetBoundingBox();
                    if (glm::distance(m_player->m_pos, bb.GetMax()) > 100.f &&
                        glm::distance(m_player->m_pos, iobj->m_pos) > 100.f &&
                        glm::distance(m_player->m_pos, bb.GetMin()) > 100.f)
                        continue;
                }

                iobj->Update();

                if (iobj->GetParrent() == m_player->AsGameObject())
                {

                }
                else
                {
                    glm::vec3 velocity = glm::vec3(100);

                    if (mask)
                        velocity = mask->GetVelocity();

                    if (iobj->HandleIntersection(m_player->AsGameObject(), velocity))
                    {
                        if (mask && mask->GetVelocity().y <= 0)
                        {
                            m_player->SetGrounded(true);
                            mask->SetVelocityY(0.f);
                        }
                    }
                }

            }
        }
    }
}

void GameContext::Render()
{
    if (m_objects.size())
    {
        for (GameObject* obj : m_objects)
        {
            if (obj)
            {
                BoundingBox bb = obj->GetBoundingBox();
                if (glm::distance(CAMERA.GetPos(), bb.GetMax()) > 750.f &&
                    glm::distance(CAMERA.GetPos(), obj->m_pos) > 750.f &&
                    glm::distance(CAMERA.GetPos(), bb.GetMin()) > 750.f)
                    continue;

                obj->IRender();
            }
        }
    }

    if (m_interactiveObjects.size())
    {
        for (InteractiveGameObject* iobj : m_interactiveObjects)
        {
            BoundingBox bb = iobj->GetBoundingBox();
            if (glm::distance(CAMERA.GetPos(), bb.GetMax()) > 750.f &&
                glm::distance(CAMERA.GetPos(), iobj->m_pos) > 750.f &&
                glm::distance(CAMERA.GetPos(), bb.GetMin()) > 750.f)
                continue;

            iobj->Render();
        }
    }

    if (&HUD)
        HUD.Render();
}
