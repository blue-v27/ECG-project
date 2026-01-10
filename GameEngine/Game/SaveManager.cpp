#include "SaveManager.h"
#include "Water.h"
#include "GameContext.h"

float randomFloat()
{
	return (float)(rand()) / (float)(RAND_MAX);
}

int randomInt(int a, int b)
{
	if (a > b)
		return randomInt(b, a);
	if (a == b)
		return a;
	return a + (rand() % (b - a));
}

float randomFloat(float a, float b)
{
	if (a > b)
		return randomFloat(b, a);
	if (a == b)
		return a;

	return (float)randomInt(a, b) + randomFloat();
}

void SaveManager::SaveObjects()
{
	m_objects = fopen("sceneObjects.txt", "w");

	int numObj = GAMECONTEXT.GetObjectCount();
	
	fprintf(m_objects, "Length: %d\n", numObj - 1);
	fprintf(m_objects, "\n");

	for (int i = 0; i < numObj; ++i)
	{
		WriteObjectInfo(GAMECONTEXT.GetObject(i));
		fprintf(m_objects, "\n");
	}

	fclose(m_objects);
}

void SaveManager::WriteObjectInfo(GameObject* obj)
{
	if (Player* player = dynamic_cast<Player*>(obj))
		return;

	fprintf(m_objects, "{\n");

	{
		fprintf(m_objects, "\tm_mesh:%d\n", MESH_DEFINES.GetMeshIndex(obj->m_mesh));
		glm::vec3 pos = obj->m_pos;
		fprintf(m_objects, "\tm_pos:%f %f %f\n", pos.x, pos.y, pos.z);
		fprintf(m_objects, "\tm_shader:%d\n", obj->m_shaderId);		
		glm::vec3 scale = obj->m_scale;
		fprintf(m_objects, "\tm_scale:%f %f %f\n", scale.x, scale.y, scale.z);
	}

	fprintf(m_objects, "}\n");
}

void SaveManager::LoadObjects()
{
	m_objects = fopen("sceneObjects.txt", "r");

	if (!m_objects)
		return;

	char line[256];
	float x, y, z;
	int ind;
	int shaderId;
	char name[128];

	GameObject* obj   = nullptr;
	Water*	    water = nullptr;

	while (fgets(line, sizeof(line), m_objects))
	{

		if (strchr(line, '}'))
		{
			if (water)
			{
				//water->ComputeBoundingBox();
				water->Init();
				//water->InitShader();
				GAMECONTEXT.AddObject(water);
				water = nullptr;
			}
			else
			{
				if (ind != GRASS && ind != FULLTRE && ind != TREE)
				{
					obj->ComputeBoundingBox();
				}
					
				obj->InitShader(shaderId);

				if (ind == GRASS)
					obj->m_scale.y = randomFloat(1.0f, 1.1f) /100.f;

				GAMECONTEXT.AddObject(obj);

				obj = nullptr;
			}
			continue;
		}

		//if (!obj) continue;

		if (sscanf(line, " m_mesh:%d", &ind) == 1)
		{
			if (ind == WATER)
				water = new Water();
			else
			{
				obj = new GameObject();
				obj->SetMesh(MESH_DEFINES.GetMesh(ind));
			}
		}
		else if (sscanf(line, " m_pos:%f %f %f", &x, &y, &z) == 3)
		{
			if(water)
				water->SetPos(glm::vec3(x, y, z));
			else
				obj->SetPos(glm::vec3(x,y,z));
		}
		else if (sscanf(line, " m_shader:%d", &shaderId) == 1)
		{
		}
		else if (sscanf(line, " m_scale:%f %f %f", &x, &y, &z) == 3)
		{
			if (water)
				water->SetScale(glm::vec3(x, y, z));
			else
				obj->SetScale(glm::vec3(x, y, z));
		}
	}

	fclose(m_objects);
}
