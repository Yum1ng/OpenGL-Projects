#ifndef OBJOBJECT_H
#define OBJOBJECT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class OBJObject
{
public:
	//std::vector<int> indices;
	std::vector<GLint> indices;
	std::vector<glm::vec3> vertices;
	//std::vector<GLfloat> vertices;
	std::vector<glm::vec3> normals;
	//std::vector<GLfloat> normals;

	glm::mat4 toWorld;
	GLuint VBO, VAO, EBO, NORMAL;
	glm::vec3 lights = { 1.0f, 0.0f, 0.0f };
	glm::vec3 dirdirection = {-0.2f, -1.0f, -0.3f };
	glm::vec3 pointposition = { 5.0f, 5.0f, 0.5f };
	glm::vec3 camposition = { 0.0f, 0.0f, 20.0f };
	glm::vec3 cameradir = glm::vec3(0.0f, 0.0f, -20.0f);
	float innercut = 10.0f;
	float outercut = 12.5f;
	int pic = 1;
	float value = 1.0f;
	float minx, miny, minz, maxx, maxy, maxz;
	float angle;
	float psize = 1.0f;
	void spin(float);
	void update();
	OBJObject(const char* filepath);
	OBJObject();	
	void parse(const char* filepath);
	
	void draw(GLuint);
	void move(double, double);
	void orbit(glm::vec3, float);
	void scroll(double);
	void moveup();
	void movedown();
	void moveleft();
	void moveright();
	void movein();
	void moveout();
	void orbitzclockw();
	void orbitzcounterclockw();
	void scaleup();
	void scaledown();
	void reset();
	unsigned char* loadPPM(const char* filename, int& width, int& height);
	void loadTexture(const char* filename, int& twidth, int& theight);
	std::vector<GLfloat> get_vertices() {
		//return vertices;
	}
	std::vector<GLfloat> get_normals() {
		//return normals;
	}
	glm::mat4 get_world(){
		return toWorld;
	}
};

#endif