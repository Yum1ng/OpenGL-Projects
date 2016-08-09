#include "OBJObject.h"
#include "Window.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
using namespace std;

OBJObject::OBJObject() {}

struct DirLight {
	glm::vec3 direction = { -0.2f, -1.0f, -0.3f };
	glm::vec3 ambient = { 0.3f, 0.24f, 0.14f };
	glm::vec3 diffuse = { 0.7f, 0.42f, 0.26f };
	glm::vec3 specular = { 0.5f, 0.5f, 0.5f };
};
OBJObject::OBJObject(const char *filepath) 
{
	cout << "here-1" << endl;
	this->toWorld = glm::mat4(1.0f);
	this->angle = 0.0f;
	cout << filepath << endl;
	parse(filepath);
	// Create buffers/arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &NORMAL);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLint), &indices[0], GL_STATIC_DRAW);
	


	glVertexAttribPointer(0,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
		3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
		GL_FLOAT, // What type these components are
		GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
		sizeof(glm::vec3), // Offset between consecutive vertex attributes. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
		(GLvoid*)0); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, NORMAL);
	glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
		3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
		GL_FLOAT, // What type these components are
		GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
		sizeof(glm::vec3), // Offset between consecutive vertex attributes. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
		(GLvoid*)0); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.
	glEnableVertexAttribArray(1);
	

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
	loadTexture("S:/cse167/ely_nevada/nevada_bk.ppm", Window::width, Window::height);
}

void OBJObject::update()
{
	//spin(0.0005f);
}

void OBJObject::spin(float deg)
{
	this->angle += deg;
	if (this->angle > 360.0f || this->angle < -360.0f) this->angle = 0.0f;
	// This creates the matrix to rotate the cube
	//glm::mat4 rotation = 
	this->toWorld = glm::rotate(toWorld, this->angle / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 1.0f, 1.0f));
}

void OBJObject::parse(const char *filepath) 
{
	cout << "here0" << endl;
	FILE * fp;
	glm::vec3 v3;
	glm::vec3 rgb;
	GLint face[3];
	glm::vec3 face2;
	GLint facex, facey, facez;
	unsigned int facex1, facey1, facez1;
	GLfloat x, y, z, r, g, b;
	char c1, c2;
	fp = fopen(filepath, "r");
	while (1) {
		c1 = fgetc(fp);
		if (c1 == '\n') {
			continue;
		}
		c2 = fgetc(fp);
		if ((c1 == EOF) || (c2 == EOF)) {
			fclose(fp);
			cout << "end of file" << endl;
			break;
		}

		else if (((c1 == 'v') && (c2 == ' '))) {
			fscanf(fp, "%f %f %f %f %f %f", &x, &y, &z, &r, &g, &b);
			if (x > maxx) maxx = x;
			if (y > maxy) maxy = y;
			if (z > maxz) maxz = z;
			if (x < minx) minx = x;
			if (y < miny) miny = y;
			if (z < minz) minz = z;
		}
		else if (((c1 == 'v') && (c2 == 'n'))) {
			fscanf(fp, " %f %f %f", &x, &y, &z);
			v3.x = x;
			v3.y = y;
			v3.z = z;
			v3 = glm::normalize(v3);
			v3.x += 1.0;
			v3.y += 1.0;
			v3.z += 1.0;
			v3.x /= 2.0;
			v3.y /= 2.0;
			v3.z /= 2.0;
			normals.push_back(v3);
		}
		else if (((c1 == 'f') && (c2 == ' '))) {
			fscanf(fp, " %u//%u %u//%u %u//%u", &facex, &facex1, &facey, &facey1, &facez, &facez1);
			face[0] = facex - 1;
			face[1] = facey - 1;
			face[2] = facez - 1;
			indices.push_back(face[0]);
			indices.push_back(face[1]);
			indices.push_back(face[2]);
		}
	}
	float avgx = (maxx + minx) / 2;
	float avgy = (maxy + miny) / 2;
	float avgz = (maxz + minz) / 2;
	fp = fopen(filepath, "r");
	while (1) {
		c1 = fgetc(fp);
		if (c1 == '\n') {
			continue;
		}
		c2 = fgetc(fp);
		if ((c1 == EOF) || (c2 == EOF)) {
			fclose(fp);
			cout << "end of file" << endl;
			break;
		}

		else if (((c1 == 'v') && (c2 == ' '))) {
			fscanf(fp, "%f %f %f %f %f %f", &x, &y, &z, &r, &g, &b);
			v3.x = (x - avgx)/(maxx - minx);
			v3.y = (y - avgy)/(maxy - miny);
			v3.z = (z - avgz)/(maxz - minz);
			vertices.push_back(v3);
		}
	}
	cout << "HERE really??" << endl;
	return;
}

void OBJObject::draw(GLuint shaderProgram)
{
	/*glMatrixMode(GL_MODELVIEW);

	// Push a save state onto the matrix stack, and multiply in the toWorld matrix
	glPushMatrix();
	glMultMatrixf(&(toWorld[0][0]));

	glBegin(GL_TRIANGLES);
	for (unsigned int i = 0; i < indices.size(); i++)
	{
		glColor3f(normals[indices[i] - 1].x, normals[indices[i] - 1].y, normals[indices[i] - 1].z);
		glNormal3f(normals[indices[i] - 1].x, normals[indices[i] - 1].y, normals[indices[i] - 1].z);
		glVertex3f(vertices[indices[i] - 1].x, vertices[indices[i] - 1].y, vertices[indices[i] - 1].z);
	}
	glEnd();

	// Pop the save state off the matrix stack
	// This will undo the multiply we did earlier
	glPopMatrix();*/

	// Calculate combination of the model (toWorld), view (camera inverse), and perspective matrices
	//glClearColor(0.75f, 0.52f, 0.3f, 1.0f);
	glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
	glm::vec3 LightColors[] = {
		glm::vec3(1.0f, 0.6f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 1.0, 0.0),
		glm::vec3(0.2f, 0.2f, 1.0f)
	};
		// Directional light
	if (pic == 1) {
		glUniform3f(glGetUniformLocation(shaderProgram, "dirLight.ambient"), 0.01f, 0.01f, 0.01f);

		glUniform3f(glGetUniformLocation(shaderProgram, "dirLight.diffuse"), 0.7f, 0.42f, 0.26f);

		glUniform3f(glGetUniformLocation(shaderProgram, "dirLight.specular"), 0.5f, 0.5f, 0.5f);

		glUniform3f(glGetUniformLocation(shaderProgram, "pointLight.ambient"), LightColors[0].x * 0.1, LightColors[0].y * 0.1, LightColors[0].z * 0.1);

		glUniform3f(glGetUniformLocation(shaderProgram, "pointLight.diffuse"), LightColors[0].x, LightColors[0].y, LightColors[0].z);

		glUniform3f(glGetUniformLocation(shaderProgram, "pointLight.specular"), LightColors[0].x, LightColors[0].y, LightColors[0].z);

		glUniform3f(glGetUniformLocation(shaderProgram, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);

		glUniform3f(glGetUniformLocation(shaderProgram, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);

		glUniform3f(glGetUniformLocation(shaderProgram, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
	}
	else if (pic == 2) {
		glUniform3f(glGetUniformLocation(shaderProgram, "dirLight.ambient"), 0.8f, 0.54f, 0.44f);

		glUniform3f(glGetUniformLocation(shaderProgram, "dirLight.diffuse"), 0.3f, 0.22f, 0.56f);

		glUniform3f(glGetUniformLocation(shaderProgram, "dirLight.specular"), 0.2f, 1.0f, 0.0f);

		glUniform3f(glGetUniformLocation(shaderProgram, "pointLight.ambient"), LightColors[0].x * 0.2, LightColors[0].y * 0.2, LightColors[0].z * 0.2);

		glUniform3f(glGetUniformLocation(shaderProgram, "pointLight.diffuse"), LightColors[0].x, LightColors[0].y+0.3, LightColors[0].z+0.3);

		glUniform3f(glGetUniformLocation(shaderProgram, "pointLight.specular"), LightColors[0].x + 0.5, LightColors[0].y+0.5, LightColors[0].z+0.5);

		glUniform3f(glGetUniformLocation(shaderProgram, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);

		glUniform3f(glGetUniformLocation(shaderProgram, "spotLight.diffuse"), 0.5f, 1.0f, 1.0f);

		glUniform3f(glGetUniformLocation(shaderProgram, "spotLight.specular"), 0.5f, 1.0f, 1.0f);
	}
	else if (pic == 3) {
		glUniform3f(glGetUniformLocation(shaderProgram, "dirLight.ambient"), 0.18f, 0.94f, 0.64f);

		glUniform3f(glGetUniformLocation(shaderProgram, "dirLight.diffuse"), 0.3f, 0.52f, 0.56f);

		glUniform3f(glGetUniformLocation(shaderProgram, "dirLight.specular"), 0.2f, 0.3f, 1.0f);

		glUniform3f(glGetUniformLocation(shaderProgram, "pointLight.ambient"), LightColors[0].x * 0.4, LightColors[0].y * 0.4, LightColors[0].z * 0.4);

		glUniform3f(glGetUniformLocation(shaderProgram, "pointLight.diffuse"), LightColors[0].x+0.5, LightColors[0].y + 0.2, LightColors[0].z + 0.5);

		glUniform3f(glGetUniformLocation(shaderProgram, "pointLight.specular"), LightColors[0].x + 0.1, LightColors[0].y + 0.2, LightColors[0].z + 0.3);

		glUniform3f(glGetUniformLocation(shaderProgram, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);

		glUniform3f(glGetUniformLocation(shaderProgram, "spotLight.diffuse"), 0.2f, 0.4f, 1.0f);

		glUniform3f(glGetUniformLocation(shaderProgram, "spotLight.specular"), 0.3f, 0.6f, 1.0f);
	}

	
		glUniform3f(glGetUniformLocation(shaderProgram, "lights"), lights.x, lights.y, lights.z);

	glUniform3f(glGetUniformLocation(shaderProgram, "dirLight.direction"), dirdirection.x, dirdirection.y, dirdirection.z);

	
	// Point light 1
	
	glUniform3f(glGetUniformLocation(shaderProgram, "pointLight.position"), pointposition.x, pointposition.y, pointposition.z);



	glUniform1f(glGetUniformLocation(shaderProgram, "pointLight.constant"), 1.0f);

	glUniform1f(glGetUniformLocation(shaderProgram, "pointLight.linear"), 0.09);

	glUniform1f(glGetUniformLocation(shaderProgram, "pointLight.quadratic"), 0.032);

	//glm::vec3 camerapos = glm::vec3( 0.0f, 0.0f, 20.0f);
	//glm::vec3 cameradir = glm::vec3( 0.0f, 0.0f, -10.0f);
	glUniform3f(glGetUniformLocation(shaderProgram, "spotLight.position"), camposition.x, camposition.y, camposition.z);

	glUniform3f(glGetUniformLocation(shaderProgram, "spotLight.direction"), cameradir.x, cameradir.y, cameradir.z);

	glUniform1f(glGetUniformLocation(shaderProgram, "spotLight.constant"), 1.0f);

	glUniform1f(glGetUniformLocation(shaderProgram, "spotLight.linear"), 0.09);

	glUniform1f(glGetUniformLocation(shaderProgram, "spotLight.quadratic"), 0.0032);

	glUniform1f(glGetUniformLocation(shaderProgram, "spotLight.cutOff"), glm::cos(glm::radians(innercut*value)));

	glUniform1f(glGetUniformLocation(shaderProgram, "spotLight.outerCutOff"), glm::cos(glm::radians(outercut*value)));

	glm::mat4 MVP = Window::P * Window::V * toWorld;
	glm::vec3 viewPos = { 0.0f, 0.0f, 20.0f };
	// We need to calculate this because as of GLSL version 1.40 (OpenGL 3.1, released March 2009), gl_ModelViewProjectionMatrix has been
	// removed from the language. The user is expected to supply this matrix to the shader when using modern OpenGL.
	GLuint MatrixtoWorldID = glGetUniformLocation(shaderProgram, "model");
	GLuint MatrixVID = glGetUniformLocation(shaderProgram, "view");
	GLuint MatrixMID = glGetUniformLocation(shaderProgram, "projection");
	GLuint ViewID = glGetUniformLocation(shaderProgram, "viewPos");
	glUniformMatrix4fv(MatrixMID, 1, GL_FALSE, &Window::P[0][0]);
	glUniformMatrix4fv(MatrixVID, 1, GL_FALSE, &Window::V[0][0]);
	glUniformMatrix4fv(MatrixtoWorldID, 1, GL_FALSE, &toWorld[0][0]);
	glUniform3f(ViewID,viewPos.x, viewPos.y, viewPos.z);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);//TODO
	glBindVertexArray(0);
}

void OBJObject::scroll(double yoffset) {
	glm::mat4 mat4I = glm::mat4(1.0f);
	glm::vec3 in = glm::vec3(0.0f, 0.0f, yoffset);
	toWorld = glm::translate(mat4I, in)*toWorld;
	cout << "done movein" << endl;
}

void OBJObject::move(double xpos, double ypos) {
	cout << "MOVE!!!!" << endl;
	cout << xpos << endl;
	cout << ypos << endl;

	glm::mat4 mat4I = glm::mat4(1.0f);
	glm::vec3 left = glm::vec3(xpos/22, -ypos/22, 0.0f);
	toWorld = glm::translate(mat4I, left)*toWorld;
}

void OBJObject::orbit(glm::vec3 rotate, float ang) {
	glm::mat4 rotation = glm::rotate(glm::mat4(), ang / 180.0f * glm::pi<float>(), rotate);
	this->toWorld = rotation * this->toWorld;
	cout << "done orbit!!" << endl;
}

void OBJObject::moveleft() {
	glm::mat4 mat4I = glm::mat4(1.0f);
	glm::vec3 left = glm::vec3(-1.0f, 0.0f, 0.0f);
	toWorld = glm::translate(mat4I, left)*toWorld;
	cout << "done moveleft" << endl;
}

void OBJObject::moveright() {
	glm::mat4 mat4I = glm::mat4(1.0f);
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
	toWorld = glm::translate(mat4I, right)*toWorld;
	cout << "done moveright" << endl;
}

void OBJObject::moveup() {
	glm::mat4 mat4I = glm::mat4(1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	toWorld = glm::translate(mat4I, up)*toWorld;
	cout << "done moveup" << endl;
}

void OBJObject::movedown() {
	glm::mat4 mat4I = glm::mat4(1.0f);
	glm::vec3 down = glm::vec3(0.0f, -1.0f, 0.0f);
	toWorld = glm::translate(mat4I, down)*toWorld;
	cout << "done movedown" << endl;
}
void OBJObject::movein() {
	glm::mat4 mat4I = glm::mat4(1.0f);
	glm::vec3 in = glm::vec3(0.0f, 0.0f, 1.0f);
	toWorld = glm::translate(mat4I, in)*toWorld;
	cout << "done movein" << endl;
}
void OBJObject::moveout() {
	glm::mat4 mat4I = glm::mat4(1.0f);
	glm::vec3 out = glm::vec3(0.0f, 0.0f, -1.0f);
	toWorld = glm::translate(mat4I, out)*toWorld;
	cout << "done moveout" << endl;
}

void OBJObject::orbitzclockw() {
	glm::mat4 rotation= glm::rotate(glm::mat4(), 10.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
	this->toWorld = rotation * this->toWorld;
	cout << "done orbit z clockwise" << endl;
}

void OBJObject::orbitzcounterclockw() {
	glm::mat4 rotation = glm::rotate(glm::mat4(), -10.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
	this->toWorld = rotation * this->toWorld;
	cout << "done orbitz counter clockwise" << endl;
}

void OBJObject::scaleup() {
	glm::mat4 mat4I = glm::mat4(1.0f);
	glm::mat4 scaleup = glm::scale(mat4I, glm::vec3(1.1f, 1.1f, 1.1f));
	this->toWorld = this->toWorld * scaleup;
	cout << "done scaleup" << endl;
}

void OBJObject::scaledown() {
	glm::mat4 mat4I = glm::mat4(1.0f);
	glm::mat4 scaledown = glm::scale(mat4I, glm::vec3(0.9f, 0.9f, 0.9f));
	this->toWorld = this->toWorld * scaledown;
	cout << "done scaledown" << endl;
}

void OBJObject::reset() {
	glm::mat4 mat4I = glm::mat4(1.0f);
	this->toWorld = mat4I;
	this->angle = 0.0f;
	cout << "done reset" << endl;
}
unsigned char* OBJObject::loadPPM(const char* filename, int& width, int& height)
{
	const int BUFSIZE = 128;
	FILE* fp;
	unsigned int read;
	unsigned char* rawData;
	char buf[3][BUFSIZE];
	char* retval_fgets;
	size_t retval_sscanf;

	if ((fp = fopen(filename, "rb")) == NULL)
	{
		std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
		width = 0;
		height = 0;
		return NULL;
	}

	// Read magic number:
	retval_fgets = fgets(buf[0], BUFSIZE, fp);

	// Read width and height:
	do
	{
		retval_fgets = fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');
	retval_sscanf = sscanf(buf[0], "%s %s", buf[1], buf[2]);
	width = atoi(buf[1]);
	height = atoi(buf[2]);

	// Read maxval:
	do
	{
		retval_fgets = fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');

	// Read image data:
	rawData = new unsigned char[width * height * 3];
	read = fread(rawData, width * height * 3, 1, fp);
	fclose(fp);
	if (read != 1)
	{
		std::cerr << "error parsing ppm file, incomplete data" << std::endl;
		delete[] rawData;
		width = 0;
		height = 0;
		return NULL;
	}

	return rawData;
}

// load image file into texture object
void OBJObject::loadTexture(const char* filename, int& twidth, int& theight)
{
	GLuint texture[1];     // storage for one texture
	//int twidth, theight;   // texture width/height [pixels]
	unsigned char* tdata;  // texture pixel data

						   // Load image file
	tdata = loadPPM(filename, twidth, theight);
	if (tdata == NULL) return;

	// Create ID for texture
	glGenTextures(1, &texture[0]);

	// Set this texture to be the one we are working with
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	// Generate the texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);

	// Set bi-linear filtering for both minification and magnification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}