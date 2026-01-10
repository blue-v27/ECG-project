#include "camera.h"
#include "..\Game\GameContext.h"

void Camera::keyboardMoveFront(float cameraSpeed)
{
	m_pos += m_viewDirection * cameraSpeed;
}

void Camera::keyboardMoveBack(float cameraSpeed)
{
	m_pos -= m_viewDirection * cameraSpeed;
}

void Camera::keyboardMoveLeft(float cameraSpeed)
{
	m_pos -= m_right * cameraSpeed;
}

void Camera::keyboardMoveRight(float cameraSpeed)
{
	m_pos += m_right * cameraSpeed;
}

void Camera::keyboardMoveUp(float cameraSpeed)
{
	m_pos += m_up * cameraSpeed;
}

void Camera::keyboardMoveDown(float cameraSpeed)
{
	m_pos -= m_up * cameraSpeed;
}

void Camera::SetPos(glm::vec3 pos)
{
	if (m_targetObject)
		m_relativePos = pos;
	else
		m_pos = pos;
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
}


void Camera::rotateOx(float angle)
{	
	m_rotationOx += angle;
//	m_rotationOx = glm::clamp(m_rotationOx, -89.0f, 89.0f);
	UpdateVectors();
}

void Camera::rotateOy (float angle)
{
	m_rotationOy += angle;
	UpdateVectors();
}

void Camera::MoveCamera(float angle)
{
	int xpos, ypos;
}

void Camera::RecomputeMatrices()
{
	m_projectionMat = glm::perspective(GAMECONTEXT.GetFov(), GAMECONTEXT.GetWindow()->getWidth() * 1.0f / GAMECONTEXT.GetWindow()->getHeight(), 0.1f, 10000.0f);
	m_viewMat	    = glm::lookAt(m_pos, m_pos + m_viewDirection, m_up);
}

void Camera::Update()
{
	if (m_targetObject && !m_freeCam)
	{
		m_pos = m_targetObject->GetPos() + m_relativePos;
		m_rot = m_targetObject->m_rot;
	}

	if (m_freeCam)
		ProcessInput(GAMECONTEXT.GetWindow(), GAMECONTEXT.GetDeltaTime());

	RecomputeMatrices();
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(m_pos, m_pos + m_viewDirection, m_up);
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

	GAMECONTEXT.SetFov(90.f);
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


