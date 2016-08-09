#include "OBJObject.h"
#include "Window.h"
#include "Track.h"
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
	parse2(filepath);
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


void OBJObject::parse2(const char *filepath)
{
	cout << "here0" << endl;
	FILE * fp;
	glm::vec3 v3;
	glm::vec3 rgb;
	GLint face[3];
	glm::vec3 face2;
	GLint facex, facey, facez;
	unsigned int facex1, facey1, facez1;
	unsigned int facex2, facey2, facez2;
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
			normals.push_back(v3);
		}
		else if (((c1 == 'f') && (c2 == ' '))) {
			fscanf(fp, " %u/%u/%u %u/%u/%u %u/%u/%u", &facex, &facex1, &facex2, &facey, &facey1, &facey2, &facez, &facez1, &facez2);
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
			v3.x = (x - avgx) / (maxx - minx);
			v3.y = (y - avgy) / (maxy - miny);
			v3.z = (z - avgz) / (maxz - minz);
			vertices.push_back(v3);
		}
	}
/*	for (int k = 0; k < indices.size(); k += 3) {
		//glm::vec3 vn = glm::cross(vertices[indices[k]], vertices[indices[k+1]]);
		glm::vec3 vn1 = vertices[indices[k + 1]] - vertices[indices[k]];
		glm::vec3 vn2 = vertices[indices[k + 2]] - vertices[indices[k]];
		glm::vec3 vn = glm::cross(vn1, vn2);
		normals.push_back(vn);
		normals.push_back(vn);
		normals.push_back(vn);
	}*/
	cout << "HERE really??" << endl;
	return;
}



void OBJObject::draw(GLuint shaderProgram)
{
	glUseProgram(shaderProgram);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox::textureID);
//	cout << "drawing tree "<< endl;
	glm::mat4 MVP = Window::P * Window::V * this->toWorld;
	//glm::vec3 viewPos = { 0.0f, 0.0f, 20.0f };
	// We need to calculate this because as of GLSL version 1.40 (OpenGL 3.1, released March 2009), gl_ModelViewProjectionMatrix has been
	// removed from the language. The user is expected to supply this matrix to the shader when using modern OpenGL.
	GLuint MatrixtoWorldID = glGetUniformLocation(shaderProgram, "model");
	GLuint MatrixVID = glGetUniformLocation(shaderProgram, "view");
	GLuint MatrixMID = glGetUniformLocation(shaderProgram, "projection");
	GLuint cameraPosID = glGetUniformLocation(shaderProgram, "cameraPos");
	glm::vec3 cameraPos = Window::cam_pos;
	glUniformMatrix4fv(MatrixMID, 1, GL_FALSE, &Window::P[0][0]);
	glUniformMatrix4fv(MatrixVID, 1, GL_FALSE, &Window::V[0][0]);
	glUniformMatrix4fv(MatrixtoWorldID, 1, GL_FALSE, &toWorld[0][0]);
	glUniform3f(cameraPosID, cameraPos.x, cameraPos.y, cameraPos.z);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);//TODO
	glBindVertexArray(0);
}

void OBJObject::move() {
//	cout << "moving!!" << endl;
/*	cout << "time: " << time << endl;
	cout << "index: " << index << endl;*/
	
	//v = sqrt(-2*g*deltah);
//	GLfloat speed = sqrt(-2 * g * 2);
//	cout << "speed: " << speed << endl;
	nextpoint = Track::children[index]->m * Track::children[0]->cal_ct(speed+time);
	glm::vec3 newz = normalize(nextpoint - currpoint);
	glm::vec3 newx = normalize(cross(newz, glm::vec3(0, 1, 0)));
	glm::vec3 newy = normalize(cross(newx, newz));
	glm::mat4 c;
	c[0] = glm::vec4(newx, 0);
	c[1] = glm::vec4(newy, 0);
	c[2] = glm::vec4(newz, 0);
	c[3] = glm::vec4(nextpoint, 1);
	toWorld = c;
	
	glm::mat4 scaledown = glm::scale(glm::mat4(), glm::vec3(0.2f, 0.2f, 0.2f));
	this->toWorld = this->toWorld * scaledown;
	
	deltah = currpoint.y - nextpoint.y;
//	cout << "highesty: " << get_highest().y << endl;

//	speed = sqrt(-1 * 2 * g * deltah);
	speed += deltah * 0.007;
	if (speed == 0) {
		speed += 0.0001;
	}
	currpoint = nextpoint;
	time += speed;

	if (time > 1) {
		time = time - 1;
		if (index == 7) {
			index = 0;
		}
		else index++;
	}

//	cout << "height " << nextpoint.y << endl;


}

glm::vec3 OBJObject::get_highest() {
	float maxy = Track::children[0]->highest.y;
	glm::vec3 max = Track::children[0]->highest;
	for (int i = 1; i < 8; i++) {
		if (Track::children[i]->highest.y > maxy) {
			maxy = Track::children[i]->highest.y;
			max = Track::children[i]->highest;
			maxindex = i;
			maxtime = Track::children[i]->maxtime;
		}
	}
	cout << "maxindex: " << maxindex << endl;
	return max;
}
void OBJObject::scale(glm::vec3 toscale) {
//	this->toWorld = this->toWorld * glm::scale(glm::mat4(), toscale);
	this->toWorld = this->toWorld * glm::scale(glm::mat4(), toscale);
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
	//this->toWorld = rotation * this->toWorld;
	Window::V = Window::V * rotation;
	//Window::cam_pos = 
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
	this->toWorld = glm::mat4(1.0f);
	currpoint = get_highest();
	index = maxindex;
	time = maxtime;
	speed = 0;
//	toWorld[3] = glm::vec4(get_highest(), 1.0f);
	cout << "done reset" << endl;
	cout << "index: " << index <<endl;
	cout << "time: " << time << endl;
}
void OBJObject::orbit(float ang) {
	toWorld = glm::rotate(toWorld, ang / 180.0f*glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	toWorld = glm::rotate(glm::mat4(1.0f), ang / 180.0f*glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)) * toWorld;
	//Geode::update(M);
}