#include "SaveManager.h"
#include "Water.h"
#include "GameContext.h"
#include "Inventory.h"
#include "Watch.h"
#include "Light.h"

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
		fprintf(m_objects, "\tm_past:%d\n", obj->m_isInPast);
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
			if (mesh != MESH_GRASS && mesh != MESH_FULLTRE && mesh != MESH_TREE && mesh != MESH_CLIFF && mesh != MESH_WATER && mesh != MESH_BUILD1
				&& mesh != MESH_BUILD2 && mesh != MESH_BUILD3)
			{
				obj->ComputeBoundingBox();
			}

			//obj->ComputeRenderBoundingBox();

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
			if(type == (int)(ObjectType::Basic))
				obj = new GameObject();
			if (type == (int)(ObjectType::Water))
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
			obj->InitShader(shaderId);
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
		else if (sscanf(line, " m_past:%d:", &anc) == 1)
		{
			obj->m_isInPast = anc;
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
	if (obj->m_type == ObjectType::RangedWeapon)
	{
		fprintf(m_interactive, "{\n");

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
			fprintf(m_interactive, "\tm_droped:%d\n", weap->IsPickable());
		}

		fprintf(m_interactive, "}\n");
	}

	if (obj->m_type == ObjectType::Watch)
	{
		fprintf(m_interactive, "{\n");

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
		pos = obj->m_relativePos;
		fprintf(m_interactive, "\tm_relPos:%f %f %f\n", pos.x, pos.y, pos.z);
		bool hasParent = obj->GetParrent() != nullptr;
		fprintf(m_interactive, "\tm_hasParent:%d\n", hasParent);
		fprintf(m_interactive, "\tm_droped:%d\n", obj->IsPickable());

		fprintf(m_interactive, "}\n");
	}

	if (obj->m_type == ObjectType::Light)
	{
		fprintf(m_interactive, "{\n");

		if (Light* light = dynamic_cast<Light*>(obj))
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
			fprintf(m_interactive, "\tm_ka:%f\n", obj->m_shaderId);
			fprintf(m_interactive, "\tm_kd:%f\n", obj->m_shaderId);
			fprintf(m_interactive, "\tm_ks:%f\n", obj->m_shaderId);
			glm::vec4 color = obj->m_color;
			fprintf(m_interactive, "\tm_color:%f %f %f %f\n", color.x, color.y, color.z, color.w);
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

	RangedWeapon* wep   = nullptr;
	Watch*		  watch	= nullptr;
	Light*		  light = nullptr;

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
			else if (sscanf(line, " m_pos:%f %f %f", &x, &y, &z) == 3)
			{
				wep->SetPos(glm::vec3(x, y, z));
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
				//wep->m_relativeRot == glm::quat(xO, yO, zO, wO);
			}
			else if (sscanf(line, " m_relPos:%f %f %f", &x, &y, &z) == 3)
			{
				wep->SetRelativePos(glm::vec3(x, y, z));
			}
			else if (sscanf(line, " m_hasParent:%d", &anc) == 1)
			{
				if (anc)
				{
					GAMECONTEXT.GetPlayer()->SetChild(wep);
					INVETORY.AddGun(wep);
				}

			}
			else if (sscanf(line, " m_damage:%f", &val) == 1)
			{
				wep->SetDamage(val);
			}
			else if (sscanf(line, " m_delay:%f", &val) == 1)
			{
				wep->SetDelay(val);
			}
			else if (sscanf(line, " m_range:%f", &val) == 1)
			{
				wep->SetRange(val);
			}
			else if (sscanf(line, " m_droped:%d", &anc) == 1)
			{
				//wep->IsPickable(val);
				if (anc)
				{
					wep->IsPickable(true);
					wep->InitPhysics();
				}

			}

			if (strchr(line, '}'))
			{
				wep->ComputeBoundingBox();
				wep->InitShader(shaderId);
				wep->RotateX(90.f);
				wep->RotateZ(-90.f);
				GAMECONTEXT.AddInteractiveGameObject(wep);


				wep = nullptr;
			}
		}

		if (type == static_cast<int>(ObjectType::Watch))
		{	
			if (sscanf(line, " m_mesh:%d", &mesh) == 1)
			{
				watch = new Watch();
				watch->SetMesh(MESH_DEFINES.GetMesh(mesh));
			}
			else if (sscanf(line, " m_pos:%f %f %f", &x, &y, &z) == 3)
			{
				watch->SetPos(glm::vec3(x, y, z));
			}
			else if (sscanf(line, " m_shader:%d", &shaderId) == 1)
			{
			}
			else if (sscanf(line, " m_scale:%f %f %f", &x, &y, &z) == 3)
			{
				watch->SetScale(glm::vec3(x, y, z));
			}
			else if (sscanf(line, " m_anchor:%d", &anc) == 1)
			{
				watch->IsAnchor(anc);
			}
			else if (sscanf(line, " m_rot:%f %f %f %f", &xO, &yO, &zO, &wO) == 4)
			{
				//wep->m_relativeRot == glm::quat(xO, yO, zO, wO);
			}
			else if (sscanf(line, " m_relPos:%f %f %f", &x, &y, &z) == 3)
			{
				watch->SetRelativePos(glm::vec3(x, y, z));
			}
			else if (sscanf(line, " m_hasParent:%d", &anc) == 1)
			{
				if (anc)
				{
					GAMECONTEXT.GetPlayer()->SetChild(watch);
					INVETORY.AddWatch(watch);
				}
					
			}
			else if (sscanf(line, " m_droped:%d", &anc) == 1)
			{
				//wep->IsPickable(val);
				if (anc)
				{
					watch->IsPickable(true);
					watch->InitPhysics();
				}
					
			}

			if (strchr(line, '}'))
			{
				watch->ComputeBoundingBox();
				watch->InitShader(shaderId);
				watch->RotateX(90.f);
				watch->RotateZ(-90.f);
				GAMECONTEXT.AddInteractiveGameObject(watch);
				
				watch = nullptr;
			}
		}

		if (type == static_cast<int>(ObjectType::Light))
		{
			if (sscanf(line, " m_mesh:%d", &mesh) == 1)
			{
				light = new Light();
				light->SetMesh(MESH_DEFINES.GetMesh(mesh));
			}
			else if (sscanf(line, " m_pos:%f %f %f", &x, &y, &z) == 3)
			{
				light->SetPos(glm::vec3(x, y, z));
			}
			else if (sscanf(line, " m_shader:%d", &shaderId) == 1)
			{
				light->InitShader(shaderId);
			}
			else if (sscanf(line, " m_scale:%f %f %f", &x, &y, &z) == 3)
			{
				light->SetScale(glm::vec3(x, y, z));
			}
			else if (sscanf(line, " m_ka:%f", &val) == 1)
			{
				light->SetIntensity(val);
			}
			else if (sscanf(line, " m_kd:%f", &val) == 1)
			{
				light->SetDifCoef(val);
			}
			else if (sscanf(line, " m_ks:%f", &val) == 1)
			{
				light->SetSpecIntensity(val);
			}
			else if (sscanf(line, " m_scale:%f %f %f", &xO, &yO, &zO, &wO) == 4)
			{
				light->SetColor(glm::vec4(xO, yO, zO, wO));
			}


			if (strchr(line, '}'))
			{
				light->ComputeBoundingBox();
				
				GAMECONTEXT.SetLight(light);

				light = nullptr;
			}
		}

	}

	fclose(m_interactive);
}
