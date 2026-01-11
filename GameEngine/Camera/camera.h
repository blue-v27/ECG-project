#pragma once

#include <glm.hpp>
#include <gtx\transform.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include "..\Graphics\window.h"
#include "..\Game\GameObject.h"
#include "..\Game\fSingleton.h"

class Camera : public fSingleton<Camera>
{
private:
	glm::vec3 m_viewDirection = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_up			  = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 m_right		  = glm::cross(m_viewDirection, m_up);
	glm::vec3 m_pos			  = glm::vec3(0);
	glm::vec3 m_relativePos	  = glm::vec3(0);

	float m_rotationOx = 0.0f;
	float m_rotationOy = -90.0f;

	glm::quat m_rot;
	
	bool m_freeCam = false;
	
	GameObject* m_targetObject = nullptr;

	glm::mat4 m_projectionMat	  = glm::mat4(1.f);
	glm::mat4 m_viewMat			  = glm::mat4(1.f);
	glm::mat4 m_ViewPorjectionMat = glm::mat4(1.f);

	public:
		glm::mat4 getViewMatrix();
		glm::vec3 getCameraPosition();
		glm::vec3 getCameraViewDirection();
		glm::vec3 getCameraUp();

		void ProcessInput(Window* window, float deltaTime);

		void keyboardMoveFront(float cameraSpeed);
		void keyboardMoveBack(float cameraSpeed);
		void keyboardMoveLeft(float cameraSpeed);
		void keyboardMoveRight(float cameraSpeed);
		void keyboardMoveUp(float cameraSpeed);
		void keyboardMoveDown(float cameraSpeed);

		void	  SetPos(glm::vec3 pos);
		glm::vec3 GetPos() { return m_pos; }

		void      SetRotatation(glm::quat rot)		{ m_rot = rot; }
		void      SetRotatation(float ox, float oy) { m_rotationOx = ox; m_rotationOy = oy; }
		glm::quat GetRotation()						{ return m_rot; }

		bool FreeCam()		   { return m_freeCam; }
		void FreeCam(bool val) { m_freeCam = val; }

		void UpdateVectors();

		void SetTarget(GameObject* obj) { m_targetObject = obj; }

		void rotateOx(float angle);
		void rotateOy(float angle);

		void MoveCamera(float angle);

		glm::mat4 GetProjectionMat() { return m_projectionMat; }
		glm::mat4 GetViewMat()       { return m_viewMat; }
		glm::mat4 GetVPMat()         { return m_viewMat; }

		void RecomputeMatrices();

		void Update();

#define CAMERA Camera::Instance()
};

