#ifndef SKYBOX_H
#define SKYBOX_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

class skybox
{
public:
	skybox();
	~skybox();
	static GLuint textureID;
	GLuint skyboxVAO, skyboxVBO;
	glm::mat4 toWorld;
	//GLuint VBO, VAO, EBO;
	float angle;

	void draw(GLuint);
	unsigned char* loadPPM(const char* filename, int& width, int& height);
	void loadTexture(const char* filename, int& twidth, int& theight);
	GLuint loadCubemap(std::vector<const GLchar*> faces);

};

#endif
