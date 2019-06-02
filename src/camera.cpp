#include "camera.h"
#include "hello_myTriangle.h"

Camera::Camera() {}

Camera::Camera(float fov, float zNear, float zFar, float speed, float sensitivity, glm::vec3 beginPosition, glm::vec3 beginFront, int screenCenterX, int screenCenterY) :
zNear(zNear),
zFar(zFar),
speed(speed),
sensitivity(sensitivity),
cameraPos(beginPosition),
frontPos(beginFront),
screenCenterX(screenCenterX),
screenCenterY(screenCenterY)
{
	ShowCursor(FALSE);
	SetFOV(fov);
	SetCursorPos(screenCenterX, screenCenterY);
}

void Camera::SetCamera(float fov, float zNear, float zFar, float speed, float sensitivity, glm::vec3 beginPosition, glm::vec3 beginFront, int screenCenterX, int screenCenterY)
{
	ShowCursor(FALSE);
	SetFOV(fov);
	this->zNear = zNear;
	this->zFar = zFar;
	this->speed = speed;
	this->sensitivity = sensitivity;
	this->cameraPos = beginPosition;
	this->frontPos = beginFront;
	this->screenCenterX = screenCenterX;
	this->screenCenterY = screenCenterY;
}

void Camera::GoFront(float& deltaTime)
{
	cameraPos += frontPos * speed * deltaTime;
}

void Camera::GoBack(float& deltaTime)
{
	cameraPos -= frontPos * speed * deltaTime;
}

void Camera::GoLeft(float& deltaTime)
{
	cameraPos -= glm::normalize(glm::cross(frontPos, UP)) * speed * deltaTime;
}

void Camera::GoRight(float& deltaTime)
{
	cameraPos += glm::normalize(glm::cross(frontPos, UP)) * speed * deltaTime;
}

void Camera::SetFront()
{
	GetCursorPos(&mousePosition);

	xOffset = mousePosition.x - screenCenterX;
	yOffset = -mousePosition.y + screenCenterY;

	xOffset *= sensitivity;
	yOffset *= sensitivity;


	yaw += xOffset;
	pitch += yOffset;

	if (pitch > MAX_PITCH)
	{
		pitch = MAX_PITCH;
	}
	if (pitch < -MAX_PITCH)
	{
		pitch = -MAX_PITCH;
	}

	frontPos = CalculateNewFront();

	SetCursorPos(screenCenterX, screenCenterY);
}

float Camera::GetFOV()
{
	return fov;
}

float Camera::GetNear()
{
	return zNear;
}

float Camera::GetFar()
{
	return zFar;
}

glm::vec3 Camera::GetPosition()
{
	return cameraPos;
}

glm::vec3 Camera::GetFront()
{
	return frontPos;
}

void Camera::End()
{
	ShowCursor(TRUE);
}

void Camera::SetFOV(float fov)
{
	this->fov = glm::radians(fov);
}

glm::vec3 Camera::CalculateNewFront()
{
	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	return glm::normalize(front);
}
