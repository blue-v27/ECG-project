#include "camera.h"
#include "..\Game\GameContext.h"

void Camera::keyboardMoveFront(float cameraSpeed)
{
	m_pos	 += m_viewDirection * cameraSpeed;
	m_isDirty = true;
}

void Camera::keyboardMoveBack(float cameraSpeed)
{
	m_pos	 -= m_viewDirection * cameraSpeed;
	m_isDirty = true;
}

void Camera::keyboardMoveLeft(float cameraSpeed)
{
	m_pos	 -= m_right * cameraSpeed;
	m_isDirty = true;
}

void Camera::keyboardMoveRight(float cameraSpeed)
{
	m_pos	 += m_right * cameraSpeed;
	m_isDirty = true;
}

void Camera::keyboardMoveUp(float cameraSpeed)
{
	m_pos	 += m_up * cameraSpeed;
	m_isDirty = true;
}

void Camera::keyboardMoveDown(float cameraSpeed)
{
	m_pos	 -= m_up * cameraSpeed;
	m_isDirty = true;
}

void Camera::SetPos(glm::vec3 pos)
{
	if (m_targetObject)
		m_relativePos = pos;
	else
		m_pos = pos;

	m_isDirty = true;
}

void Camera::UpdateVectors()
{
	float yaw   = glm::radians(m_rotationOy);
	float pitch = glm::radians(m_rotationOx);

	glm::quat qYaw   = glm::angleAxis(yaw, glm::vec3(0, 1, 0));
	glm::quat qPitch = glm::angleAxis(pitch, glm::vec3(1, 0, 0));

	m_rot = qYaw * qPitch;
	m_rot = glm::normalize(m_rot);

	glm::vec3 front = m_rot * glm::vec3(0, 0, -1);
	glm::vec3 right = m_rot * glm::vec3(1, 0, 0);
	glm::vec3 up    = m_rot * glm::vec3(0, 1, 0);

	m_viewDirection = glm::normalize(front);
	m_right			= glm::normalize(right);
	m_up			= glm::normalize(up);

	m_isDirty = true;
}


void Camera::rotateOx(float angle)
{	
	m_rotationOx += angle;
	if (angle)
	{
		UpdateVectors();
		m_isDirty = true;
	}
}

void Camera::rotateOy (float angle)
{
	m_rotationOy += angle;
	if (angle)
	{
		UpdateVectors();
		m_isDirty = true;
	}
}

void Camera::MoveCamera(float angle)
{
	int xpos, ypos;
}

void Camera::UpdateFrustum()
{
	const glm::mat4& m = m_ViewPorjectionMat;

	m_frustum.planes[0] = glm::vec4(
		m[0][3] + m[0][0],
		m[1][3] + m[1][0],
		m[2][3] + m[2][0],
		m[3][3] + m[3][0]
	);

	m_frustum.planes[1] = glm::vec4(
		m[0][3] - m[0][0],
		m[1][3] - m[1][0],
		m[2][3] - m[2][0],
		m[3][3] - m[3][0]
	);

	m_frustum.planes[2] = glm::vec4(
		m[0][3] + m[0][1],
		m[1][3] + m[1][1],
		m[2][3] + m[2][1],
		m[3][3] + m[3][1]
	);

	m_frustum.planes[3] = glm::vec4(
		m[0][3] - m[0][1],
		m[1][3] - m[1][1],
		m[2][3] - m[2][1],
		m[3][3] - m[3][1]
	);

	m_frustum.planes[4] = glm::vec4(
		m[0][3] + m[0][2],
		m[1][3] + m[1][2],
		m[2][3] + m[2][2],
		m[3][3] + m[3][2]
	);

	m_frustum.planes[5] = glm::vec4(
		m[0][3] - m[0][2],
		m[1][3] - m[1][2],
		m[2][3] - m[2][2],
		m[3][3] - m[3][2]
	);

	for (int i = 0; i < 6; ++i)
	{
		float len = glm::length(glm::vec3(m_frustum.planes[i]));
		m_frustum.planes[i] /= len;
	}
}

void Camera::RecomputeMatrices()
{
	m_projectionMat		= glm::perspective(m_fov, GAMECONTEXT.GetWindow()->getWidth() * 1.0f / GAMECONTEXT.GetWindow()->getHeight(), 0.1f, 10000.0f);
	m_viewMat			= glm::lookAt(m_pos, m_pos + m_viewDirection, m_up);
	m_ViewPorjectionMat = m_projectionMat * m_viewMat;
}

void Camera::Update()
{
	if (m_targetObject && !m_freeCam && m_targetObject->m_isDirty)
	{
		m_pos     = m_targetObject->GetPos() + m_relativePos;
		m_rot     = m_targetObject->m_rot;
		m_isDirty = true;
	}

	if (m_freeCam)
		ProcessInput(GAMECONTEXT.GetWindow(), GAMECONTEXT.GetDeltaTime());

	if (m_isDirty)
	{
		RecomputeMatrices();
		UpdateFrustum();
	}
	
}

glm::mat4 Camera::getViewMatrix()
{
	return m_viewMat;
}

glm::vec3 Camera::getCameraPosition()
{
	return m_pos;
}

glm::vec3 Camera::getCameraViewDirection()
{
	return m_viewDirection;
}

glm::vec3 Camera::getCameraUp()
{
	return m_up;
}

void Camera::ProcessInput(Window* window, float deltaTime)
{
	float speed = 300 * deltaTime;

	if (window->isPressed(GLFW_KEY_W))
		keyboardMoveFront(speed);

	if (window->isPressed(GLFW_KEY_S))
		keyboardMoveBack(speed);

	if (window->isPressed(GLFW_KEY_A))
		keyboardMoveLeft(speed);

	if (window->isPressed(GLFW_KEY_D))
		keyboardMoveRight(speed);

	if (window->isPressed(GLFW_KEY_LEFT_CONTROL))
		keyboardMoveDown(speed);

	if (window->isPressed(GLFW_KEY_X))
		keyboardMoveUp(speed);

	double x, y;
	window->getMousePos(x, y);

	double dx = x - GAMECONTEXT.GetMousePos().x;
	double dy = y - GAMECONTEXT.GetMousePos().y;

	GAMECONTEXT.SetMousePos(glm::vec2(x, y));

	const float sensitivity = 2.5f;

	rotateOy(-dx * sensitivity);
	rotateOx(-dy * sensitivity);
}

bool Camera::AABBInFrustum(glm::vec3& center, glm::vec3& offset, Frustum& frustum)
{
	for (int i = 0; i < 6; ++i)
	{
		const glm::vec3 normal = glm::vec3(frustum.planes[i]);
		const float     d = frustum.planes[i].w;

		float r = offset.x * std::abs(normal.x) + offset.y * std::abs(normal.y) + offset.z * std::abs(normal.z);

		float s = glm::dot(normal, center) + d;

		if (s + r < 0)
			return false;
	}

	return true;
}


