#include "Cylinder.h"
#include <iostream>
using namespace std;


Cylinder::Cylinder()
{
}


Cylinder::~Cylinder()
{
}

Cylinder::Cylinder(OBJObject* todraw, GLint shaderID, glm::mat4 parent)
{
	this->M = glm::mat4(1.0f);
	this->parent = parent;
	toDraw = todraw;
	shader = shaderID;
}

void Cylinder::update(glm::mat4 C) {
	//M = C*M;
	//M = C*M;
	/*this->M = glm::rotate(this->M, 1 / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	cout << "Cylinder: #############" << endl;
	cout << "M[3][0]: " << M[3][0] << endl;
	cout << "M[3][1]: " << M[3][1] << endl;
	cout << "M[3][2]: " << M[3][2] << endl;*/
	/*glm::mat4 T_inv = glm::translate(glm::mat4(1.0f), glm::vec3(-parent[3][0], -parent[3][1], -parent[3][2]));
	glm::mat4 R = glm::rotate(glm::mat4(1.0f), 0.8f / 180.0f*glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(parent[3][0], parent[3][1], parent[3][2]));
	M = T * R * T_inv * this->M;

	parent = glm::rotate(glm::mat4(1.0f), 1.0f / 180.0f*glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * parent;*/
	//Geode::update(C);
	M = C;
}

void Cylinder::draw() {
	toDraw->toWorld = M;
	toDraw->draw(shader);
}
void Cylinder::orbit(float ang) {
	//update(glm::mat4()test);
	/*
	glm::mat4 T_inv = glm::translate(glm::mat4(1.0f), glm::vec3(-parent[3][0], -parent[3][1], -parent[3][2]));
	glm::mat4 R = glm::rotate(glm::mat4(1.0f), 0.8f / 180.0f*glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(parent[3][0], parent[3][1], parent[3][2]));
	M = T * R * T_inv * this->M;
	cout << "HERE" << endl;
	parent = glm::rotate(glm::mat4(1.0f), 0.5f / 180.0f*glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * parent;*/
	M = glm::rotate(glm::mat4(1.0f), ang / 180.0f*glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * M;
	Geode::update(M);
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
