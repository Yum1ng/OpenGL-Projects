#ifndef CURVE_H
#define CURVE_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <vector>

class Curve
{
public:
	Curve();
	~Curve();

	Curve(glm::vec3, glm::vec3, glm::vec3, glm::vec3);

	glm::mat4 toWorld;
	GLuint VBO, VAO, VCO, VDO;
	Curve* prev;
	Curve* next;

	glm::mat4x3 m;
	glm::vec3 control_point1;
	glm::vec3 control_point2;
	glm::vec3 control_point3;
	glm::vec3 control_point4;
	float max = -1.0f;
	glm::vec3 highest;
	float maxtime = 0;

	float angle;
	glm::vec4 cal_ct(float t);
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> q_vertices;

	std::vector<glm::vec3> point_vertices;
	void draw(GLuint);
	void drawPoints(GLuint, GLuint);
	void update(GLuint, glm::vec3);

};
#endif
