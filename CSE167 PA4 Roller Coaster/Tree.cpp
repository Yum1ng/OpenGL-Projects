#include "Tree.h"
using namespace std;
#include <iostream>;
string result;
Tree::Tree(GLuint shaderID)
{
	toWorld = glm::mat4(1.0f);
	shaderprogram = shaderID;
	cylinder_tree = new OBJObject("S:/cse167/CSE167-Starter-Code-3-master/cylinder.obj");
	create(1, s, 0);
	cout << "string: " << result << endl;
	draw(result);
	cout << "size: " << sizeof(int) << endl;
}


Tree::~Tree()
{
}

string Tree::create(GLuint i, string curr, int start) {
	//cout << curr << endl;
	if (i == 0) {
		result = curr;
		return curr;
	}
	for (int j = start; j < curr.size(); j++) {
		if (curr[j] == 'F') {
			
			curr.replace(j, 1, rule);
			//curr.erase(j);
			//create(i - 1, curr, j+rule.size());
			j += rule.size();
		}
	}
	return create(i - 1, curr, 0);
}

void Tree::draw(string str) {
	int len = str.size();
	for (int i = 0; i < len; i++) {
		if (str[i] == 'F') {
			Cylinder * cy = new Cylinder(cylinder_tree, shaderprogram, toWorld);
			cy->draw();
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
			toWorld = glm::translate(glm::mat4(1.0), up)*toWorld;
		}
	}


}