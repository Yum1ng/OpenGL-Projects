#pragma once
#include "Group.h"
class MatrixTransform: public Group
{
public:
	glm::mat4 M;
	glm::mat4 R;
	glm::mat4 S;
	glm::mat4 T;


	MatrixTransform();
	~MatrixTransform();
	void update(glm::mat4 C);
	void draw();
	//test
	void rotate(float ang, glm::vec3 rotation, glm::mat4);
	void translate(glm::vec3 translation);
	void scale(glm::vec3 scale);
	void orbit(float);
	glm::mat4 rotation;
	glm::mat4 translation;
	//glm::mat4 scale;
	glm::mat4 scale1;
};

