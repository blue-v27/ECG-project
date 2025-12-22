#include "GameContext.h"

void GameContext::Update()
{
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
