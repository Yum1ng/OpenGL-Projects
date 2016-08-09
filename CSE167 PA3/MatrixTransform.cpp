#include "MatrixTransform.h"



MatrixTransform::MatrixTransform()
{
	M = glm::mat4(1.0f);
	R = glm::mat4(1.0f);
	S = glm::mat4(1.0f);
	T = glm::mat4(1.0f);
	
}


MatrixTransform::~MatrixTransform()
{
}

void MatrixTransform::update(glm::mat4 C) {
	//cout << "under mat-update" << endl;
	//M = C;
	//conmented out in rotate
	//glm::mat4 RST = T*S*R;
	//glm::mat4 toreturn =  RST*M ;
	// = C*M;
	//glm::mat4 toreturn = C*M;
	M = C*M; 
	cout << "C[3][0]" << C[3][0] << endl;
	cout << "C[3][0]" << C[3][1] << endl;
	cout << "C[3][0]" << C[3][2] << endl;
	Group::update(M);
}

void MatrixTransform::draw() {
	for (Node* n : children) {
		n->draw();
	}
}

void MatrixTransform::orbit(float ang) {
	Group::orbit(ang);
	/*for (Node* n : children) {
		this->M = glm::rotate(this->M, 2 / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
		
		//n->update(glm::rotate(this->M, 2 / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)));
	}*/
}

void MatrixTransform::rotate(float ang, glm::vec3 torotate, glm::mat4 origin) {
	rotation = glm::rotate(glm::mat4(), ang / 180.0f * glm::pi<float>(), torotate) * origin;
	R = glm::rotate(glm::mat4(), ang / 180.0f * glm::pi<float>(), torotate) * origin;
	update(rotation);
	//this->M = rotation*M;
}

void MatrixTransform::translate(glm::vec3 totranslate) {
	translation = glm::translate(glm::mat4(), totranslate);
	T = glm::translate(glm::mat4(), totranslate);
	//cout << "under mat-translate" << endl;
	//this->M = translation*M;
	update(translation);
}

void MatrixTransform::scale(glm::vec3 toscale) {
	scale1 = glm::scale(glm::mat4(), toscale);
	S = glm::scale(glm::mat4(), toscale);
	//this->M = scale1*M;
	update(scale1);
}
