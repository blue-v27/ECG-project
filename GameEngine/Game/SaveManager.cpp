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
	if (obj->m_type == ObjectType::Player)
		return;

	if (MESH_DEFINES.GetMeshIndex(obj->m_mesh) == MESH_SUN)
		return;

	if (obj->m_type == ObjectType::Bullet)
		return;

	fprintf(m_objects, "{\n");

	{
		fprintf(m_objects, "\tm_type:%d\n", (int)(obj->m_type));
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
	int mesh;
	int type;
	int anc;
	int shaderId;
	char name[128];

	GameObject* obj   = nullptr;

	while (fgets(line, sizeof(line), m_objects))
	{

		if (strchr(line, '}'))
		{
			if (mesh != MESH_GRASS && mesh != MESH_FULLTRE && mesh != MESH_TREE && mesh != MESH_CLIFF && mesh != MESH_WATER)
			{
				obj->ComputeBoundingBox();
			}

			obj->InitShader(shaderId);

			if (mesh == MESH_GRASS)
				obj->m_scale.y = randomFloat(1.0f, 1.1f) /100.f;

			if (mesh == MESH_GROUND)
			{
				obj->m_boundingBox.m_min.pos.y -= 10.f;
			}

			GAMECONTEXT.AddObject(obj);

			obj = nullptr;
		}

		//if (!obj) continue;

		if (sscanf(line, " m_type:%d", &type) == 1)
		{
			if(type == static_cast<int>(ObjectType::Basic))
				obj = new GameObject();
			if (type == static_cast<int>(ObjectType::Water))
				obj = new Water();
		}
		else if (sscanf(line, " m_mesh:%d", &mesh) == 1)
		{
			obj->SetMesh(MESH_DEFINES.GetMesh(mesh));
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
		else if (sscanf(line, " m_rot:%f %f %f %f", &xO, &yO, &zO, &wO) == 4)
		{
			//obj->SetRotation(glm::quat(xO, yO, zO, wO));
		}

	}

	fclose(m_objects);
}

void SaveManager::SaveInteractives()
{
	m_interactive = fopen("sceneInteractives.txt", "w");

	int numObj = GAMECONTEXT.GetInteractiveObjectCount();

	fprintf(m_interactive, "Length: %d\n", numObj - 1);
	fprintf(m_interactive, "\n");

	for (int i = 0; i < numObj; ++i)
	{
		WriteInteractiveInfo(GAMECONTEXT.GetInteractiveObject(i));
		fprintf(m_interactive, "\n");
	}

	fclose(m_interactive);
}

void SaveManager::WriteInteractiveInfo(InteractiveGameObject* obj)
{
	if (MESH_DEFINES.GetMeshIndex(obj->m_mesh) == MESH_PISTOL)
	{
		fprintf(m_interactive, "{\n");

		{
			if (RangedWeapon* weap = dynamic_cast<RangedWeapon*>(obj))
			{
				fprintf(m_interactive, "\tm_type:%d\n", (int)(obj->m_type));
				fprintf(m_interactive, "\tm_mesh:%d\n", MESH_DEFINES.GetMeshIndex(obj->m_mesh));
				glm::vec3 pos = obj->m_pos;
				fprintf(m_interactive, "\tm_pos:%f %f %f\n", pos.x, pos.y, pos.z);
				fprintf(m_interactive, "\tm_shader:%d\n", obj->m_shaderId);
				glm::vec3 scale = obj->m_scale;
				fprintf(m_interactive, "\tm_scale:%f %f %f\n", scale.x, scale.y, scale.z);
				fprintf(m_interactive, "\tm_anchor:%d\n", obj->IsAnchor());
				glm::quat orient = obj->m_rot;
				fprintf(m_interactive, "\tm_rot:%f %f %f %f\n", orient.x, orient.y, orient.z, orient.w);
				pos = weap->m_relativePos;
				fprintf(m_interactive, "\tm_relPos:%f %f %f\n", pos.x, pos.y, pos.z);
				bool hasParent = weap->GetParrent() != nullptr;
				fprintf(m_interactive, "\tm_hasParent:%d\n", hasParent);
				fprintf(m_interactive, "\tm_damage:%f\n", weap->m_damage);
				fprintf(m_interactive, "\tm_delay:%f\n", weap->m_delay);
				fprintf(m_interactive, "\tm_range:%f\n", weap->m_range);
			}

		}

		fprintf(m_interactive, "}\n");
	}
}

void SaveManager::LoadInteractives()
{
	InteractiveGameObject* obj = nullptr;

	m_interactive = fopen("sceneInteractives.txt", "r");

	if (!m_interactive)
		return;

	char  line[256];
	float x, y, z;
	float xO, yO, zO, wO;
	int   mesh;
	int   type;
	int   anc;
	int   shaderId;
	float val;
	char  name[128];

	RangedWeapon* wep = nullptr;

	while (fgets(line, sizeof(line), m_interactive))
	{
		//if (!obj) continue;

		if (sscanf(line, " m_type:%d", &type) == 1)
		{
			if (type == static_cast<int>(ObjectType::RangedWeapon))
				obj = new RangedWeapon();
		}

		if (type == static_cast<int>(ObjectType::RangedWeapon))
		{	
			if (sscanf(line, " m_mesh:%d", &mesh) == 1)
			{
				wep = new RangedWeapon();
				wep->SetMesh(MESH_DEFINES.GetMesh(mesh));
			}
			else if (sscanf(line, " m_shader:%d", &shaderId) == 1)
			{
			}
			else if (sscanf(line, " m_scale:%f %f %f", &x, &y, &z) == 3)
			{
				wep->SetScale(glm::vec3(x, y, z));
			}
			else if (sscanf(line, " m_anchor:%d", &anc) == 1)
			{
				wep->IsAnchor(anc);
			}
			else if (sscanf(line, " m_rot:%f %f %f %f", &xO, &yO, &zO, &wO) == 4)
			{
			}
			else if (sscanf(line, " m_relPos:%f %f %f", &x, &y, &z) == 3)
			{
				wep->SetRelativePos(glm::vec3(x, y, z));
			}
			else if (sscanf(line, " m_hasParent:%d", &anc) == 1)
			{
				GAMECONTEXT.GetPlayer()->SetChild(wep);
			}
			else if (sscanf(line, " tm_damage:%d", &val) == 1)
			{
				wep->SetDamage(val);
			}
			else if (sscanf(line, " tm_delay:%d", &val) == 1)
			{
				wep->SetDelay(val);
			}
			else if (sscanf(line, " tm_range:%d", &val) == 1)
			{
				wep->SetRange(val);
			}

			if (strchr(line, '}'))
			{
				//wep->ComputeBoundingBox();
				wep->InitShader(shaderId);

				GAMECONTEXT.AddInteractiveGameObject(wep);

				wep = nullptr;
			}
		}

	}

	fclose(m_interactive);
}
