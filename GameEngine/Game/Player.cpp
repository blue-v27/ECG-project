#include "Player.h"
#include "GameContext.h"

void Player::KeyboardMoveFront(float speed)
{
	glm::vec3 pos = GetPos();
	glm::vec3 dir = GetDir();
	pos.x += dir.x * speed;
	pos.z += dir.z * speed;
	SetPos(pos);
}

void Player::KeyboardMoveBack(float speed)
{
	glm::vec3 pos = GetPos();
	pos.x -= GetDir().x * speed;
	pos.z -= GetDir().z * speed;
	SetPos(pos);
}

void Player::KeyboardMoveLeft(float speed)
{
	glm::vec3 pos = GetPos();
	pos.x -= GetRight().x * speed;
	pos.z -= GetRight().z * speed;
	SetPos(pos);
}

void Player::KeyboardMoveRight(float speed)
{
	glm::vec3 pos = GetPos();
	pos.x += GetRight().x * speed;
	pos.z += GetRight().z * speed;
	SetPos(pos);
}

void Player::KeyboardMoveUp(float speed)
{
	glm::vec3 pos = GetPos();
	pos.y += GetUp().y * speed;
	SetPos(pos);
}

void Player::KeyboardMoveDown(float speed)
{
	glm::vec3 pos = GetPos();
	pos.y -= GetUp().y * speed;
	SetPos(pos);
}

void Player::UpdateVectors()
{
	glm::vec3 front;
	float rotationOy = GetRotationOy();
	float rotationOx = GetRotationOx();
	front.x = cos(glm::radians(rotationOy) * cos(glm::radians(rotationOx)));
	front.y = sin(glm::radians(rotationOx));
	front.z = sin(glm::radians(rotationOy)) * cos(glm::radians(rotationOx));

	SetDir  (glm::normalize(front));
	SetRight(glm::normalize(glm::cross(GetDir(), glm::vec3(0, 1, 0))));
	SetUp   (glm::normalize(glm::cross(GetRight(), GetDir())));

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




