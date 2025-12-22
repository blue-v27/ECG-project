#include "Player.h"
#include "GameContext.h"

void Player::KeyboardMoveFront(float speed)
{
	m_pos.x += m_viewDirection.x * speed;
	m_pos.z += m_viewDirection.z * speed;
}

void Player::KeyboardMoveBack(float speed)
{
	m_pos.x -= m_viewDirection.x * speed;
	m_pos.z -= m_viewDirection.z * speed;
}

void Player::KeyboardMoveLeft(float speed)
{
	m_pos.x -= m_right.x * speed;
	m_pos.z -= m_right.z * speed;
}

void Player::KeyboardMoveRight(float speed)
{
	m_pos.x += m_right.x * speed;
	m_pos.z += m_right.z * speed;
}

void Player::KeyboardMoveUp(float speed)
{
	m_pos.y += m_up.y * speed;
}

void Player::KeyboardMoveDown(float speed)
{
	m_pos.y -= m_up.y * speed;
}

void Player::UpdateVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_rotationOy) * cos(glm::radians(m_rotationOx)));
	front.y = sin(glm::radians(m_rotationOx));
	front.z = sin(glm::radians(m_rotationOy)) * cos(glm::radians(m_rotationOx));

	SetDir  (glm::normalize(front));
	SetRight(glm::normalize(glm::cross(m_viewDirection, glm::vec3(0, 1, 0))));
	SetUp   (glm::normalize(glm::cross(m_right, m_viewDirection)));

	m_camera->UpdateVectors();
}

void Player::Jump()
{
	if (m_isGrounded)
	{
		GetPhysicsMask()->SetVelocityY(50.f);
		m_isGrounded = false;
	}
}

void Player::RotateOx(float angle)
{
	float rotationOx = GetRotationOx();
	rotationOx += angle;
	rotationOx = glm::clamp(rotationOx, -89.0f, 89.0f);
	SetRotationOx(rotationOx);
	UpdateVectors();

	m_camera->rotateOx(angle);
}

void Player::RotateOy(float angle)
{
	float rotationOy = GetRotationOy();
	rotationOy += angle;
	SetRotationOy(rotationOy);
	UpdateVectors();

	m_camera->rotateOy(angle);
}

void Player::ProcessInput(Window* window, float deltaTime)
{
	float speed = 30 * deltaTime;

	//translation
	if (window->isPressed(GLFW_KEY_W))
		KeyboardMoveFront(speed);
	if (window->isPressed(GLFW_KEY_S))
		KeyboardMoveBack(speed);
	if (window->isPressed(GLFW_KEY_A))
		KeyboardMoveLeft(speed);
	if (window->isPressed(GLFW_KEY_D))
		KeyboardMoveRight(speed);
	if (window->isPressed(GLFW_KEY_SPACE))
		Jump();
	if (window->isPressed(GLFW_KEY_LEFT_CONTROL))
		KeyboardMoveDown(speed);
	if (window->isPressed(GLFW_KEY_X))
		KeyboardMoveUp(speed);

	double x, y;
	window->getMousePos(x, y);

	double dx = x - GAMECONTEXT.GetMousePos().x;
	double dy = y - GAMECONTEXT.GetMousePos().y;

	GAMECONTEXT.SetMousePos(glm::vec2(x, y));

	const float sensitivity = 0.25f;

	RotateOy(dx * sensitivity);
	RotateOx(-dy * sensitivity);
}

void Player::Update()
{
	Window* wnd = GameContext::Instance().GetWindow();

	if (!wnd) return;

	ProcessInput(wnd, GAMECONTEXT.GetDeltaTime());

	GameObject::Update();
}

void Player::Render()
{
}




