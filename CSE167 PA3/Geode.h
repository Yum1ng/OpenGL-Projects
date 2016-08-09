#pragma once
#include "Node.h"
#include "OBJObject.h"
class Geode: public Node
{
public:
	Geode();
	~Geode();

	Geode(OBJObject* todraw, GLint shaderID);
	GLint shader;
	OBJObject* toDraw;
	
	glm::mat4 rotation;
	glm::mat4 translation;
	//glm::mat4 scale;
	glm::mat4 scale1;

	glm::mat4 M;
	void rotate(float ang, glm::vec3 rotation, glm::mat4 M0);
	void translate(glm::vec3 translation);
	void scale(glm::vec3 scale);

	void update(glm::mat4 C);
	void draw();
	void move(int);

};

