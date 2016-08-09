#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <vector>

class point
{
public:
	point();
	~point();
	void drawPoints(GLuint, GLuint);

	point(glm::vec3);
	glm::mat4 toWorld;
	GLuint VBO, VAO;

	std::vector<glm::vec3> point_vertices;
	glm::vec3 pointposition;
	glm::vec3 move(GLfloat x, GLfloat y, glm::vec3 vx, glm::vec3 vy);
};

