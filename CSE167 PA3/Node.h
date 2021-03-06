#pragma once
#ifndef _NODE_H_
#define _NODE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

class Node
{
public:
	virtual void draw() = 0;
	virtual void update(glm::mat4) = 0;
	virtual void orbit(float) = 0;
};

#endif

