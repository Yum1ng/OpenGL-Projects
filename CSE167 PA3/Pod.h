#pragma once
#include "Geode.h"
class Pod: public Geode
{
public:
	Pod();
	~Pod();
	void update(glm::mat4 C);
	void draw();
	void orbit(float);
	glm::mat4 rotation;
	glm::mat4 translation;
	//glm::mat4 scale;
	glm::mat4 scale1;

	void rotate(float ang, glm::vec3 rotation, glm::mat4 M0);
	void translate(glm::vec3 translation);
	void scale(glm::vec3 scale);

	Pod(OBJObject* todraw, GLint shaderID);
	GLint shader;
	OBJObject* toDraw;
	glm::mat4 M;
};

