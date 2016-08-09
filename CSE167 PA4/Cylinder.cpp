#include "Cylinder.h"
#include <iostream>
using namespace std;


Cylinder::Cylinder()
{
}


Cylinder::~Cylinder()
{
}

Cylinder::Cylinder(OBJObject* todraw, GLint shaderID, glm::mat4 toworld)
{
	//this->M = glm::mat4(1.0f);
	this->M = toworld;
	this->parent = parent;
	toDraw = todraw;
	shader = shaderID;
}

void Cylinder::update(glm::mat4 C) {
	M = C;
}

void Cylinder::draw() {
	toDraw->toWorld = M;
	toDraw->draw(shader);
}
void Cylinder::orbit(float ang) {
	M = glm::rotate(glm::mat4(1.0f), ang / 180.0f*glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * M;
	//M = C;

}
void Cylinder::rotate(float ang, glm::vec3 torotate, glm::mat4 M0) {
	rotation = glm::rotate(glm::mat4(), ang / 180.0f * glm::pi<float>(), torotate);
	this->M = rotation*M0;
}
void Cylinder::translate(glm::vec3 totranslate) {
	translation = glm::translate(glm::mat4(), totranslate);
	this->M = translation*M;
}
void Cylinder::scale(glm::vec3 toscale) {
	scale1 = glm::scale(glm::mat4(), toscale);
	this->M = scale1*M;
}
