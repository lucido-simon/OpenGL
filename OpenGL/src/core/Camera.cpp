#include "../GLErrorManager.h"

#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"

Camera::Camera()
{
	position = glm::vec3(1.f);
	rotation = glm::vec3(1.f);

	computeViewMatrix();

}

void Camera::computeViewMatrix()
{
	cameraMatrix = glm::rotate(glm::mat4(1.f), glm::radians(rotation.x), { 0, 1, 0 });
	cameraMatrix = glm::rotate(cameraMatrix, glm::radians(rotation.y), { 1, 0, 0 });
	cameraMatrix = glm::translate(cameraMatrix, position);
}

void Camera::computeViewMatrix(glm::vec3& position, glm::vec3& rotation)
{
	this->position = position;
	this->rotation = rotation;

	cameraMatrix = glm::rotate(glm::mat4(1.f), glm::radians(rotation.x), { 0, 1, 0 });
	cameraMatrix = glm::rotate(cameraMatrix, glm::radians(rotation.y), { 1, 0, 0 });
	cameraMatrix = glm::translate(cameraMatrix, position);
}

glm::mat4 Camera::getViewMatrix()
{
	computeViewMatrix();
	return cameraMatrix;
}

glm::mat4 Camera::getViewMatrix(glm::vec3& position, glm::vec3& rotation)
{
	computeViewMatrix(position, rotation);
	return cameraMatrix;
}

void Camera::translate(const glm::vec3& vector)
{
	position += vector;
}

void Camera::rotate(const glm::vec3& vector)
{
	rotation += vector;
}

void Camera::setPosition(const glm::vec3& vector)
{
	position = glm::vec3(vector);
}

void Camera::setRotation(const glm::vec3& vector)
{
	rotation = glm::vec3(vector);
}
