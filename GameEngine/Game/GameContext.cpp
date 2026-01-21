#include "GameContext.h"
#include "SubModes/SceneEditorSubMode.h"
#include "SaveManager.h"
#include "../Model Loading/MeshDefines.h"
#include "GUI/Hud.h"
#include "GUI/GUIManager.h"
#include "Sky.h"
#include "../Shaders/ShaderManager.h"
#include "QuestManager.h"
#include "Inventory.h"


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

void GameContext::BuildOctree()
{
    BoundingBox worldBounds;
    worldBounds.SetWorldMin(glm::vec3(-5000));
    worldBounds.SetWorldMax(glm::vec3(5000));

    m_octTree = new OctreeNode(worldBounds);

    for (GameObject* obj : m_objects)
        m_octTree->Insert(obj);

}

void GameContext::TimeTravel()
{
    if (m_isInPast)m_isInPast = false;
        else m_isInPast = true;

    SKYBOX.SwitchCubeMap();
}

void GameContext::Start()
{
    BoundingBox bb;
    bb.SetWorldMax(glm::vec3(-87.f, 1000.f, 100.f));
    bb.SetWorldMin(glm::vec3(-89.f, -10.f, -80.f));
    m_worldBounds.push_back(bb);

    BoundingBox bb1;
    bb1.SetWorldMax(glm::vec3(90.f,  1000.f, -79.f));
    bb1.SetWorldMin(glm::vec3(-89.f, -10.f, -82.f));
    m_worldBounds.push_back(bb1);

    BoundingBox bb2;
    bb2.SetWorldMax(glm::vec3(89.f, 1000.f, 100.f));
    bb2.SetWorldMin(glm::vec3(87.f, -10.f, -80.f));
    m_worldBounds.push_back(bb2);

    BoundingBox bb3;
    bb3.SetWorldMax(glm::vec3(90.f, 1000.f,  82.f));
    bb3.SetWorldMin(glm::vec3(-89.f, -10.f, 60.f));
    m_worldBounds.push_back(bb3);

    BoundingBox bb4;
    bb.SetWorldMax(glm::vec3(76, 70, -22));
    bb.SetWorldMin(glm::vec3(38, 0, -79));
    m_worldBounds.push_back(bb);

    BoundingBox bb5;
    bb1.SetWorldMax(glm::vec3(72, 70, 55));
    bb1.SetWorldMin(glm::vec3(36, 0, -3));
    m_worldBounds.push_back(bb1);

    BoundingBox bb6;
    bb2.SetWorldMax(glm::vec3(8, 297, -15));
    bb2.SetWorldMin(glm::vec3(-25, 0, -78));
    m_worldBounds.push_back(bb2);

    BoundingBox bb7;
    bb3.SetWorldMax(glm::vec3(8, 189, 66));
    bb3.SetWorldMin(glm::vec3(-27, 0, 0));
    m_worldBounds.push_back(bb3);

    BoundingBox bb8;
    bb.SetWorldMax(glm::vec3(-66, 189, -35));
    bb.SetWorldMin(glm::vec3(-104, 0, -104));
    m_worldBounds.push_back(bb);

    BoundingBox bb9;
    bb1.SetWorldMax(glm::vec3(-65, 287, 73));
    bb1.SetWorldMin(glm::vec3(-65, 0, -4));
    m_worldBounds.push_back(bb1);

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

    std::vector<GameObject*> nearby;
    if(m_player)
        m_octTree->Query(m_player->GetBoundingBox(), nearby);

    printf("%f %f %f\n", CAMERA.GetPos().x, CAMERA.GetPos().y, CAMERA.GetPos().z);

    if (nearby.size())
    {
        for (GameObject* obj : nearby)
        {
            if (obj && obj->m_isActive)
            {                       
                if (m_player)
                {
                    obj->IUpdate();

                    if (obj->m_type != ObjectType::Player && obj->m_isInPast == m_isInPast)
                    {
                        glm::vec3 velocity = glm::vec3(100);

                        if (mask)
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

                    if (obj->m_type == ObjectType::Player)
                        if (PhysicsMask* pMask = obj->GetPhysicsMask())
                            pMask->ComputeVelocity();
                }
            }
        }
    }

    if (m_player)
    {
        for (int i = 0; i < m_worldBounds.size(); ++i)
        {
            if (i < 4)
            {
                glm::vec3 velocity = glm::vec3(100);
                velocity = m_player->GetPhysicsMask()->GetVelocity();

                m_player->m_boundingBox.HandleIntersection(m_player->m_pos, m_worldBounds.at(i), velocity);
            }
            else if (!m_isInPast)
            {
                glm::vec3 velocity = glm::vec3(100);
                velocity = m_player->GetPhysicsMask()->GetVelocity();

                m_player->m_boundingBox.HandleIntersection(m_player->m_pos, m_worldBounds.at(i), velocity);
            }

        }
    }

    if (m_player->GetPos().y < -15.f)
        m_player->SetPos(glm::vec3(0, 0, 0));
   

    if (m_interactiveObjects.size())
    {
        for (InteractiveGameObject* iobj : m_interactiveObjects)
        {          
            if (m_player)
            {
                iobj->Update();           

                if (iobj->IsPhysicsEnable())
                {
                    for (GameObject* obj : nearby)
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
            if(light->m_isDirty)
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
            if (obj && obj->m_isActive && obj->m_isInPast == m_isInPast)
            {
                BoundingBox bb = obj->GetBoundingBox();
                glm::vec3    d = obj->GetBoundingBox().GetCenter() - CAMERA.GetPos();
                if (glm::dot(d, d) > 750.f * 750.f)
               //if(!CAMERA.AABBInFrustum(bb.GetCenter(), bb.GetOffset(), CAMERA.GetFrustum()))
                    continue;

                obj->IRender();
            }
        }
    }

    if (m_interactiveObjects.size())
    {
        for (InteractiveGameObject* iobj : m_interactiveObjects)
        {
            if (iobj && iobj->m_isActive)
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
                        {
                            if (iobj->m_type == ObjectType::Watch && QUEST_MANAGER.GetCurrentQuest() != 1)
                                return;

                            iobj->PickUp(m_player);
                            INVETORY.Add(iobj);
                        }
                            
                    }

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

    CAMERA.IsDirty(false);
}
