#include "GameContext.h"
#include "SubModes/SceneEditorSubMode.h"
#include "SaveManager.h"
#include "../Model Loading/MeshDefines.h"
#include "GUI/Hud.h"
#include "GUI/GUIManager.h"
#include "Sky.h"
#include "../Shaders/ShaderManager.h"
#include "QuestManager.h"

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
                glm::vec3 d = bb.GetCenter() - pos;
                if (glm::dot(d, d) > range * range)
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

    if (&SHADER_MANAGER)
        SHADER_MANAGER.Start();

    if (&SAVE_MANAGER)
        SAVE_MANAGER.LoadObjects();

    if (&SKYBOX)
        SKYBOX.Start();

    if (&QUEST_MANAGER)
        QUEST_MANAGER.Start();
}

void GameContext::InitLights()
{
    int numShaders = SHADER_MANAGER.GetShaderCount();

    for (int i = 0; i < numShaders; ++i)
    {
        if (SHADER_MANAGER.GetShader(i)->UseLights())
            SHADER_MANAGER.GetShader(i)->CacheLights(m_lights.size());
    }
}

void GameContext::UpdateLights()
{
    int numShaders = SHADER_MANAGER.GetShaderCount();

    for (int i = 0; i < numShaders; ++i)
    {
        if (Shader* shader = SHADER_MANAGER.GetShader(i))
        {
            if (shader->UseLights())
            {
                shader->use();

                int numLights = GAMECONTEXT.GetLightCount();
                glUniform1i(shader->m_numLights, numLights);

                for (int i = 0; i < numLights; ++i)
                {
                    Light* light = GAMECONTEXT.GetLight(i);

                    glUniform3fv(shader->m_lights[i].color, 1, &light->GetLightColor()[0]);
                    glUniform3fv(shader->m_lights[i].position, 1, &light->GetPos()[0]);
                    glUniform1f(shader->m_lights[i].ka, light->GetIntensity());
                    glUniform1f(shader->m_lights[i].kd, light->GetDifCoef());
                    glUniform1f(shader->m_lights[i].ks, light->GetSpecIntensity());
                }

                Camera* cam = GAMECONTEXT.GetCamera();
                glUniform3fv(shader->m_viewPos, 1, &cam->getCameraPosition()[0]);
            }          
        }
    }
    
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
            if (obj && obj->m_isActive)
            {                       
                if (m_player)
                {
                    BoundingBox bb = obj->GetBoundingBox();
                    glm::vec3    d = bb.GetCenter() - m_player->m_pos;
                    if (glm::dot(d, d) > 100.f * 100.f)
                        continue;


                    float x = 1;
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
                    glm::vec3 d = bb.GetCenter() - m_player->m_pos;
                    if (glm::dot(d, d) > 100.f * 100.f)
                        continue;
                }

                iobj->Update();           

                if (iobj->IsPhysicsEnable())
                {
                    for (GameObject* obj : m_objects)
                    {
                        if (iobj->m_id == obj->m_id)
                            continue;

                        if (m_player->AsGameObject() == iobj->GetParrent())
                            continue;

                        if (obj->m_boundingBox.GetMax().x - obj->m_boundingBox.GetMin().x == 0.f)
                            continue;

                        if (iobj->m_boundingBox.HandleIntersection(iobj->m_pos, obj->GetBoundingBox()))
                        {
                            iobj->GetPhysicsMask()->SetVelocityY(0.f);
                        }
                    }                 
                }

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

    if (m_lights.size())
    {
        for (Light* light : m_lights)
        {
            light->Update();
        }
    }

    UpdateLights();
}

void GameContext::Render()
{
    SKYBOX.Render();

    if (m_lights.size())
    {
        for (Light* light : m_lights)
            light->Render();
    }

    if (m_objects.size())
    {
        for (GameObject* obj : m_objects)
        {
            if (obj && obj->m_isActive)
            {
                BoundingBox bb = obj->GetBoundingBox();
                glm::vec3    d = bb.GetCenter() - CAMERA.GetPos();
                if (glm::dot(d, d) > 750.f * 750.f)
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
            glm::vec3    d = bb.GetCenter() - CAMERA.GetPos();
            if (glm::dot(d, d) > 750.f * 750.f)
                continue;

            iobj->Render();

            Ray ray;
            glm::vec3 hitPoint;
            if (ray.RayCast(CAMERA.GetPos(), CAMERA.getCameraViewDirection(), 200.f, iobj, hitPoint))
            {
                if (iobj->IsPickable())
                {
                    GUI.DrawText("PRESS E TO PICKUP", 400.f, 600.f, 1.f);
                    if (GAMECONTEXT.GetWindow()->IsReleased(GLFW_KEY_E))
                        iobj->PickUp(m_player);
                }
                    
            }
        }
    }

   

    if (&HUD)
        HUD.Render();

    char fpsS[100] = { 0 };
    float fps = 1.f / m_deltaTime;
    sprintf(fpsS, "%d", (int)fps);
    GUI.DrawText(fpsS, 20.f * 2, 700.f * 2, .5f);

    char dir[50] = { 0 };
    sprintf(dir, "%f, %f, %f", CAMERA.getCameraViewDirection().x, CAMERA.getCameraViewDirection().y, CAMERA.getCameraViewDirection().z);
    GUI.DrawText(dir, 500, 500, .5f);

    if (&QUEST_MANAGER)
        QUEST_MANAGER.RenderQuestText();
}
