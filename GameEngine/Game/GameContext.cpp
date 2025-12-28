#include "GameContext.h"
#include "SubModes/SceneEditorSubMode.h"
#include "SaveManager.h"

void GameContext::UpdateFov()
{
    if (glm::abs(m_fov - m_targetFov) > 0.01f)
        m_fov += 10.f * m_deltaTime;
    if (glm::abs(m_fov - m_targetFov) < 0.01f);
        m_fov -= 10.f * m_deltaTime;
    if (m_fov != m_targetFov && glm::abs(m_fov - m_targetFov) <= 0.1f)
        m_fov = m_targetFov;
}

void GameContext::Start()
{
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
                obj->IUpdate();

                if (m_player)
                {
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
}

void GameContext::Render()
{
    if (m_objects.size())
    {
        for (GameObject* obj : m_objects)
        {
            if (obj)
            {
                obj->IRender();
            }
        }
    }
}
