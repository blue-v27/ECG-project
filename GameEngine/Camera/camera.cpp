#include "camera.h"

Camera::Camera(glm::vec3 m_pos)
{
	this->m_viewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	this->m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->m_right = glm::cross(m_viewDirection, m_up);
	this->m_rotationOx = 0.0f;
	this->m_rotationOy = -90.0f;
}

Camera::Camera()
{
	this ->m_viewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	this ->m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->m_right = glm::cross(m_viewDirection, m_up);
	this->m_rotationOx = 0.0f;
	this->m_rotationOy = -90.0f;
}

Camera::Camera(glm::vec3 m_pos, glm::vec3 m_viewDirection, glm::vec3 m_up)
{
	this->m_pos = m_pos;
	this->m_viewDirection = m_viewDirection;
	this->m_up = m_up;
	this->m_right = glm::cross(m_viewDirection, m_up);
}

Camera::~Camera()
{
}

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

void Camera::UpdateVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_rotationOy)) * cos(glm::radians(m_rotationOx));
	front.y = sin(glm::radians(m_rotationOx));
	front.z = sin(glm::radians(m_rotationOy)) * cos(glm::radians(m_rotationOx));

	m_viewDirection = glm::normalize(front);
	m_right = glm::normalize(glm::cross(m_viewDirection, glm::vec3(0, 1,0) ));
	m_up = glm::normalize(glm::cross(m_right, m_viewDirection));
}


void Camera::rotateOx(float angle)
{	
	m_rotationOx += angle;
	m_rotationOx = glm::clamp(m_rotationOx, -89.0f, 89.0f);
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


