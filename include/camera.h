#ifndef CAMERA_H
#define CAMERA_H

#include <Windows.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>



class Camera
{
public:
	Camera();
	Camera(float fov, float zNear, float zFar, float speed, float sensitivity, glm::vec3 beginPosition, glm::vec3 beginFront, int screenCenterX, int screenCenterY);

	void SetCamera(float fov, float zNear, float zFar, float speed, float sensitivity, glm::vec3 beginPosition, glm::vec3 beginFront, int screenCenterX, int screenCenterY);



	void GoFront(float& deltaTime);
	void GoBack(float& deltaTime);
	void GoLeft(float& deltaTime);
	void GoRight(float& deltaTime);

	void SetFront();

	float GetFOV();

	float GetNear();
	float GetFar();

	glm::vec3 GetPosition();
	glm::vec3 GetFront();

	void End();

	const glm::vec3 UP = glm::vec3(0, 1, 0);
private:
	// Field Of View
	float fov;

	void SetFOV(float fov);

	// Min and Max render distance
	float zNear;
	float zFar;

	float speed;
	float sensitivity;

	// moves
	glm::vec3 cameraPos;
	glm::vec3 frontPos;

	int screenCenterX;
	int screenCenterY;

	float xOffset;
	float yOffset;

	float yaw = 0;
	float pitch = 0;

	const float MAX_PITCH = 89.0f;

	glm::vec3 CalculateNewFront();

	POINT mousePosition;
};
#endif
