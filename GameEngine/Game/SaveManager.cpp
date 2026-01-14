#include "SaveManager.h"
#include "Water.h"
#include "GameContext.h"
#include "RangedWeapon.h"

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
	if (obj->m_type == ObjectType::Player)
		return;

	if (MESH_DEFINES.GetMeshIndex(obj->m_mesh) == MESH_SUN)
		return;

	fprintf(m_objects, "{\n");

	{
		fprintf(m_objects, "\tm_mesh:%d\n", MESH_DEFINES.GetMeshIndex(obj->m_mesh));
		glm::vec3 pos = obj->m_pos;
		fprintf(m_objects, "\tm_pos:%f %f %f\n", pos.x, pos.y, pos.z);
		fprintf(m_objects, "\tm_shader:%d\n", obj->m_shaderId);		
		glm::vec3 scale = obj->m_scale;
		fprintf(m_objects, "\tm_scale:%f %f %f\n", scale.x, scale.y, scale.z);
		fprintf(m_objects, "\tm_anchor:%d\n", obj->IsAnchor());
		glm::quat orient = obj->m_rot;
		fprintf(m_objects, "\tm_rot:%f %f %f %f\n", orient.x, orient.y, orient.z, orient.w);
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
	float xO, yO, zO, wO;
	int ind;
	int anc;
	int shaderId;
	char name[128];

	GameObject* obj   = nullptr;
	Water*	    water = nullptr;

	while (fgets(line, sizeof(line), m_objects))
	{

		if (strchr(line, '}'))
		{
			if (ind != MESH_GRASS && ind != MESH_FULLTRE && ind != MESH_TREE && ind != MESH_CLIFF)
			{
				obj->ComputeBoundingBox();
			}

			obj->InitShader(shaderId);

			if (ind == MESH_GRASS)
				obj->m_scale.y = randomFloat(1.0f, 1.1f) /100.f;

			if (ind == MESH_GROUND)
			{
				obj->m_boundingBox.m_min.pos.y -= 10.f;
			}

			GAMECONTEXT.AddObject(obj);

			obj = nullptr;
		}

		//if (!obj) continue;

		if (sscanf(line, " m_mesh:%d", &ind) == 1)
		{
			obj = new GameObject();
			obj->SetMesh(MESH_DEFINES.GetMesh(ind));
		}
		else if (sscanf(line, " m_pos:%f %f %f", &x, &y, &z) == 3)
		{
			obj->SetPos(glm::vec3(x,y,z));
		}
		else if (sscanf(line, " m_shader:%d", &shaderId) == 1)
		{
		}
		else if (sscanf(line, " m_scale:%f %f %f", &x, &y, &z) == 3)
		{
			obj->SetScale(glm::vec3(x, y, z));
		}
		else if (sscanf(line, " m_anchor:%d", &anc) == 1)
		{
			obj->IsAnchor(anc);
		}
		else if (sscanf(line, " m_anchor:%d", &anc) == 1)
		{
			obj->IsAnchor(anc);
		}
		else if (sscanf(line, " m_rot:%f %f %f %f", &xO, &yO, &zO, &wO) == 4)
		{
			//obj->SetRotation(glm::quat(xO, yO, zO, wO));
		}

	}

	fclose(m_objects);
}

void SaveManager::SaveInteractives()
{
	m_objects = fopen("sceneInteractives.txt", "w");

	int numObj = GAMECONTEXT.GetInteractiveObjectCount();

	fprintf(m_objects, "Length: %d\n", numObj - 1);
	fprintf(m_objects, "\n");

	for (int i = 0; i < numObj; ++i)
	{
		WriteInteractiveInfo(GAMECONTEXT.GetInteractiveObject(i));
		fprintf(m_objects, "\n");
	}

	fclose(m_objects);
}

void SaveManager::WriteInteractiveInfo(InteractiveGameObject* obj)
{
	if (MESH_DEFINES.GetMeshIndex(obj->m_mesh) == MESH_PISTOL)
	{
		RangedWeapon* weap = dynamic_cast<RangedWeapon*>(obj);

		fprintf(m_objects, "{\n");

		{
			fprintf(m_objects, "\tm_mesh:%d\n", MESH_PISTOL);
			glm::vec3 pos = weap->m_pos;
			fprintf(m_objects, "\tm_pos:%f %f %f\n", pos.x, pos.y, pos.z);
			pos = weap->m_relativePos;
			fprintf(m_objects, "\tm_relPos:%f %f %f\n", pos.x, pos.y, pos.z);
			fprintf(m_objects, "\tm_shader:%d\n", weap->m_shaderId);
			glm::vec3 scale = weap->m_scale;
			fprintf(m_objects, "\tm_scale:%f %f %f\n", scale.x, scale.y, scale.z);
			glm::quat orient = weap->m_relativeRot;
			fprintf(m_objects, "\tm_rot:%f %f %f %f\n", orient.x, orient.y, orient.z, orient.w);
			bool hasParent = weap->GetParrent() != nullptr;
			fprintf(m_objects, "\tm_hasParent:%d\n", hasParent);
			fprintf(m_objects, "\tm_damage:%f\n", weap->m_damage);
			fprintf(m_objects, "\tm_delay:%f\n", weap->m_delay);
			fprintf(m_objects, "\tm_range:%f\n", weap->m_range);
		}

		fprintf(m_objects, "}\n");
	}
}

void SaveManager::LoadInteractives()
{
}
