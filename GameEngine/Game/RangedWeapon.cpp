#include "RangedWeapon.h"
#include "GameContext.h"
#include "Ray.h"
#include "../Shaders/ShaderManager.h"

RangedWeapon::RangedWeapon(float damange, float delay, float range) : Weapon(damange, delay, range)
{
	m_lineShader = SHADER_MANAGER.GetShader(LINE);
	m_bullet     = new Bullet();
	m_type	     = ObjectType::RangedWeapon;
	GAMECONTEXT.AddObject(m_bullet);
}

RangedWeapon::RangedWeapon()
{
	m_lineShader = SHADER_MANAGER.GetShader(LINE);
	m_bullet = new Bullet();
	m_type = ObjectType::RangedWeapon;
}

RangedWeapon::~RangedWeapon()
{

}

void RangedWeapon::Shoot()
{
	if (m_isActive)
	{
		if (!m_canAttack)
			return;

		Ray ray;
		std::vector<GameObject*> arr = GAMECONTEXT.GetObjectsInRange(CAMERA.GetPos(), 2 * m_range);

		m_bullet->BulletBeginShoot(m_pos, CAMERA.getCameraViewDirection(), 1000.f * GAMECONTEXT.GetDeltaTime());

		for (GameObject* obj : arr)
		{
			glm::vec3 hitPoint;
			if (ray.RayCast(CAMERA.GetPos() + glm::vec3(0.0f, 0.0f, 2.0f), CAMERA.getCameraViewDirection(), m_range, obj, hitPoint))
			{
				obj->GetDamage(m_damage);
				break;
			}
		}
	}
}

void RangedWeapon::GrabAnchor()
{
	if (m_isActive)
	{
		int numObj = GAMECONTEXT.GetObjectCount();
		Ray ray;
		for (int i = 0; i < numObj; ++i)
		{
			GameObject* obj = GAMECONTEXT.GetObject(i);
			glm::vec3 hitPoint;
			if (ray.RayCast(m_pos, CAMERA.getCameraViewDirection(), 200.f, obj, hitPoint))
			{
				if (obj->IsAnchor())
				{
					GetParrent()->GetPhysicsMask()->StartSwing(obj->GetPos());
					break;
				}

			}
		}

	}
}

void RangedWeapon::Update()
{
	if (m_isActive)
	{
		if (!m_canAttack)
		{
			if (glfwGetTime() - m_time > m_delay)
			{
				m_canAttack = true;
				m_time = glfwGetTime();
			}
		}

		ProcessInput(GAMECONTEXT.GetWindow(), GAMECONTEXT.GetDeltaTime());

		InteractiveGameObject::Update();
	}
}

void RangedWeapon::ProcessInput(Window* wnd, float dt)
{
	if (m_isActive)
	{

		if (GameObject* obj = GetParrent())
		{
			if (wnd->IsMouseReleased(0))
				Shoot();
			if (wnd->IsReleased(GLFW_KEY_Q))
				Drop();
			if (wnd->isMousePressed(1))
			{
				if (!GetParrent()->GetPhysicsMask()->isSwinging())
				{
					GrabAnchor();
				}
			}
			if (wnd->IsMouseReleased(1))
				if (GetParrent()->GetPhysicsMask()->isSwinging())
					GetParrent()->GetPhysicsMask()->StopSwinging();
		}
	}
}

void RangedWeapon::RenderLine()
{
	if (GameObject* obj = GetParrent())
	{
		m_lineShader->use();

		GLint colorLoc = glGetUniformLocation(m_lineShader->getId(), "lineColor");
		glUniform3f(colorLoc, 1.0f, 0.0f, 0.0f);

		glm::mat4 ModelMatrix = glm::mat4(1.0f);;
		glm::mat4 ProjectionMatrix = glm::perspective(GAMECONTEXT.GetFov(), GAMECONTEXT.GetWindow()->getWidth() * 1.0f / GAMECONTEXT.GetWindow()->getHeight(), 0.1f, 10000.0f);
		glm::mat4 ViewMatrix = glm::lookAt(CAMERA.getCameraPosition(),
			CAMERA.getCameraPosition() + CAMERA.getCameraViewDirection(),
			CAMERA.getCameraUp());
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		GLint mvpLoc = glGetUniformLocation(m_lineShader->getId(), "MVP");
		glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(MVP));

		glm::vec3 anchor = GetParrent()->GetPhysicsMask()->GetAnchor();
		float vertices[] = {
			m_pos.x, m_pos.y, m_pos.z,
			anchor.x, anchor.y, anchor.z
		};

		static GLuint VAO = 0, VBO = 0;
		if (VAO == 0)
		{
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		}

		glBindVertexArray(VAO);
		glLineWidth(5.0f);
		glDrawArrays(GL_LINES, 0, 2);
		glLineWidth(1.0f);
		
	}
}

void RangedWeapon::Render()
{
	if (m_isActive)
	{
		if (GameObject* obj = GetParrent())
		{
			if (obj->GetPhysicsMask()->isSwinging())
			{
				RenderLine();
			}
		}

		InteractiveGameObject::Render();
	}
}
