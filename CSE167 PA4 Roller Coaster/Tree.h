#pragma once
#include <string>
#include <cstring>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> 
#include "Cylinder.h"
#include "OBJObject.h"


using namespace std;
class Tree
{
public:
	Tree(GLuint shaderID);
	
	~Tree();
	string create(GLuint i, string curr, int start);
	OBJObject* cylinder_tree;
	string s = "F";
	string rule = "FF+[+F-F-F]-[-F+F+F]";
	void draw(string str);
	glm::mat4 toWorld;
	GLuint shaderprogram;
};

