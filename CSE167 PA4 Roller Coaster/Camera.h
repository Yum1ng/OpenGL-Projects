#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> 
class Camera
{
public:
	Camera();
	~Camera();
	glm::mat4 original;
	glm::mat4 bearMatrix;
	glm::mat4 newCam();
	void orbit(float ang);
};

