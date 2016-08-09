#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}
glm::mat4 Camera::newCam() {
	glm::mat4 tmp = glm::inverse(bearMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 2.0, 0.0)));
	return tmp;
}

void Camera::orbit(float ang) {
	//toWorld = glm::rotate(toWorld, ang / 180.0f*glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	//toWorld = glm::rotate(glm::mat4(1.0f), ang / 180.0f*glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * toWorld;
	bearMatrix = glm::rotate(bearMatrix, ang / 180.0f*glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	bearMatrix = glm::rotate(glm::mat4(1.0f), ang / 180.0f*glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * bearMatrix;
	//Geode::update(M);
}
