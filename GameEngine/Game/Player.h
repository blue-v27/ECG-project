#pragma once

#include <glm.hpp>
#include <gtx\transform.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include "..\Graphics\window.h"
#include "GameObject.h"
#include "..\Camera\Camera.h"

class Player : public GameObject
{
private:
	Camera* m_camera = nullptr;
	
	bool  m_isGrounded = false;
public:

	Player() = default;

	void	SetCamera(Camera* cam) { m_camera = cam; SetChild(m_camera); }
	Camera* GetCamera()			   { return m_camera; }

	void KeyboardMoveFront(float cameraSpeed);
	void KeyboardMoveBack(float cameraSpeed);
	void KeyboardMoveLeft(float cameraSpeed);
	void KeyboardMoveRight(float cameraSpeed);
	void KeyboardMoveUp(float cameraSpeed);
	void KeyboardMoveDown(float cameraSpeed);

	void RotateOx(float angle);
	void RotateOy(float angle);
	void UpdateVectors();

	void SetGrounded(bool val) { m_isGrounded = val; }
	bool IsGrounded() { return m_isGrounded; }

	void Jump();

	void ProcessInput(Window* window, float deltaTime) override;
	void Update() override;
	void Render() override;
};