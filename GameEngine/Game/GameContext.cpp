#include "GameContext.h"

void GameContext::Update()
{
    if (m_objects.size())
    {
        for (GameObject* obj : m_objects)
        {
            if (obj)
            {
                if (m_player)
                    m_player->GetPhysicsMask()->SetLastFramePos(m_player->m_pos);

                obj->IUpdate();

                if (m_player)
                {
                    if (Player* player = dynamic_cast<Player*>(obj))
                    {

                    }
                    else
                    {
                        if (m_player->m_boundingBox.HandleIntersection(m_player->m_pos, obj->GetBoundingBox(),
                            m_player->GetPhysicsMask()->GetVelocity()))
                        {
                            if (m_player->GetPhysicsMask()->GetVelocity().y <= 0)
                            {
                                m_player->SetGrounded(true);
                                m_player->GetPhysicsMask()->SetVelocityY(0.f);
                            }
                        }
                    }
                }

                if (Player* player = dynamic_cast<Player*>(obj))
                    player->GetPhysicsMask()->ComputeVelocity();

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
