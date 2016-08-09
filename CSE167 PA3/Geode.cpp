#include "Geode.h"
#include <iostream>
#include <cstdio>
using namespace std;


//glm::mat4 Geode::M;
Geode::Geode()
{
	
}


Geode::~Geode()
{
}

Geode::Geode(OBJObject* todraw, GLint shaderID)
{
	//printf("!!!!!!!!!!!!!!!!%s\n", filepath);
	M = glm::mat4(1.0f);
	toDraw = todraw;
	shader = shaderID;

}

void Geode::update(glm::mat4 C) {
	//M = C*M;
	//cout << "2222" << endl;
	//Geode::M = C* Geode::M;
	//Geode::M = C;
	M = C;
}

void Geode::move(int mod) {
	/*switch (mod) {
	case(1) :
		rotation = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
		translation = glm::translate(glm::mat4(), glm::vec3(1.0f, 0.0f, 0.0f));
		scale = glm::scale(glm::mat4(), glm::vec3(2.5, 0.5, 0.5f));
		this->M = translation * scale * rotation * glm::mat4(1.0f);
		cout << "1" << endl;
		break;
	case(2) :
		rotation = glm::rotate(glm::mat4(), 90.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
		translation = glm::translate(glm::mat4(), glm::vec3(-1.0f, 0.0f, 0.0f));
		scale = glm::scale(glm::mat4(), glm::vec3(2.5, 0.5, 0.5f));
		this->M = translation * scale * rotation * glm::mat4(1.0f);
		cout << "2" << endl;
		break;
	case(3) :
		rotation = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
		translation = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -1.0f));
		scale = glm::scale(glm::mat4(), glm::vec3(0.5f, 0.5f, 2.5f));
		this->M = translation * scale * rotation * glm::mat4(1.0f);
		cout << "3" << endl;
		break;
	}*/
}
void Geode::rotate(float ang, glm::vec3 torotate, glm::mat4 M0) {
	rotation = glm::rotate(glm::mat4(), ang / 180.0f * glm::pi<float>(), torotate);
	M = rotation*M0;
}
void Geode::translate(glm::vec3 totranslate) {
	translation = glm::translate(glm::mat4(), totranslate);
	M = translation*M;
}
void Geode::scale(glm::vec3 toscale) {
	scale1 = glm::scale(glm::mat4(), toscale);
	M = scale1*M;
}

void Geode::draw() {
	toDraw->toWorld = M;
	toDraw->draw(shader);
}
