#include "SaveManager.h"

#include "GameContext.h"

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
		glm::vec3 pos = obj->m_pos;
		fprintf(m_objects, "\tm_pos:%f %f %f\n", pos.x, pos.y, pos.z);
		fprintf(m_objects, "\tm_vertexShader:%s\n", obj->getVertexShader());
		fprintf(m_objects, "\tm_fragmentShader:%s\n", obj->GetFragmentShader());
		fprintf(m_objects, "\tm_mesh:%s\n", obj->m_mesh.GetPath());
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
	char name[128];

	GameObject* obj = nullptr;

	while (fgets(line, sizeof(line), m_objects))
	{
		if (strchr(line, '{'))
		{
			obj = new GameObject();
			continue;
		}

		if (strchr(line, '}'))
		{
			obj->ComputeBoundingBox();
			obj->InitShader();
			GAMECONTEXT.AddObject(obj);
			obj = nullptr;
			continue;
		}

		if (!obj) continue;

		if (sscanf(line, " m_pos:%f %f %f", &x, &y, &z) == 3)
		{
			obj->SetPos(glm::vec3(x,y,z));
		}
		else if (sscanf(line, " m_vertexShader:%127s", name) == 1)
		{
			obj->SetVertexShader(name);
		}
		else if (sscanf(line, " m_fragmentShader:%127s", name) == 1)
		{
			obj->SetFramentShader(name);
		}
		else if (sscanf(line, " m_mesh:%127s", name) == 1)
		{
			obj->SetMesh(obj->m_loader.loadObj(name));
		}
		if (sscanf(line, " m_scale:%f %f %f", &x, &y, &z) == 3)
		{
			obj->SetScale(glm::vec3(x, y, z));
		}
	}

	fclose(m_objects);
}
