#include "Group.h"
#include <vector>;
using namespace std;


Group::Group()
{
}


Group::~Group()
{
}
void Group::addChild(Node* node) {
	children.push_back(node);
}
void Group::removeChild(Node* node) {
	for (auto it1 = children.begin(); it1 != children.end(); ++it1) {
		if (*it1 == node) {
			children.erase(it1);
			break;
		}
	}
}
void Group::update(glm::mat4 C) {
	for (int i = 0; i < children.size(); i++){
		children[i]->update(C);
		
	//	cout << "updating" << endl;
	}
}
void Group::draw() {
	for (int i = 0; i < children.size(); i++) {
		children[i]->draw();
	}
}
void Group::orbit(float ang) {
	for (int i = 0; i < children.size(); i++) {
		children[i]->orbit(ang);
	}
}
