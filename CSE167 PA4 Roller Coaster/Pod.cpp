#include "Pod.h"
#include <iostream>
#include <math.h>
using namespace std;


Pod::Pod()
{
}


Pod::~Pod()
{
}
Pod::Pod(OBJObject* todraw, GLint shaderID)
{
	cout << "yes" << endl;
	this->M = glm::mat4(1.0f);
	toDraw = todraw;
	shader = shaderID;

}

void Pod::update(glm::mat4 C) {
	M = C;
	//cout << "under pod update" << endl;
	cout << "yes good" << endl;
	//M = C;
	//this->M = glm::rotate(M, 5 / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	//this->M = glm::rotate(glm::mat4(1.0f), 2 / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Pod::orbit(float ang) {
	//this->M = glm::rotate(M, ang / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	M =  glm::rotate(M, ang / 180.0f*glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::rotate(glm::mat4(1.0f), ang / 180.0f*glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * M;
	//Geode::update(M);
}
void Pod::draw() {
	toDraw->toWorld = M;
	toDraw->draw(shader);
}
void Pod::rotate(float ang, glm::vec3 torotate, glm::mat4 M0) {
	rotation = glm::rotate(glm::mat4(), ang / 180.0f * glm::pi<float>(), torotate);
	this->M = rotation*M0;
}
void Pod::translate(glm::vec3 totranslate) {
	translation = glm::translate(glm::mat4(), totranslate);
	this->M = translation*M;
}
void Pod::scale(glm::vec3 toscale) {
	scale1 = glm::scale(glm::mat4(), toscale);
	toDraw -> toWorld = scale1* toDraw->toWorld;
//	this->M = scale1*M;
}
void Pod::move() {
	GLfloat g = -0.01f;
	GLfloat speed = sqrt(-2 * g * 3);
	//toDraw
}