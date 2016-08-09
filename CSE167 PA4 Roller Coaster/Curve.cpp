#include "Window.h"
#include "Curve.h"
#include <math.h>
using namespace std;


Curve::Curve() {}

Curve::Curve(glm::vec3 x1, glm::vec3 x2, glm::vec3 x3, glm::vec3 x4)
{
	this->control_point1 = x1;
	this->control_point2 = x2;
	this->control_point3 = x3;
	this->control_point4 = x4;

/*	point_vertices.push_back(control_point1);
	point_vertices.push_back(control_point2);
	point_vertices.push_back(control_point3);*/

	this->toWorld = glm::mat4(1.0f);
	this->vertices.push_back(control_point1);
	this->vertices.push_back(control_point2);
	this->vertices.push_back(control_point3);
	this->vertices.push_back(control_point4);

	//glm::mat4x3 m;
	m[0] = vertices[0];
	m[1] = vertices[1];
	m[2] = vertices[2];
	m[3] = vertices[3];
	glm::vec3 q0 = m[0];
	glm::vec3 q1 = m[3];

	// for highest point calculation
	max = control_point1.y;

	q_vertices.push_back(q0);
	for (GLfloat i = 0.01; i < 1.0f; i = i + 0.01) {
		glm::vec4 ct_q = cal_ct(i);
		glm::vec3 q_point = m*ct_q;
		if (q_point.y > max) {
			highest = q_point;
			max = q_point.y;
			maxtime = i;
		}
		q_vertices.push_back(q_point);
		q_vertices.push_back(q_point);
	}
	q_vertices.push_back(q1);

	// Create buffers/arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, q_vertices.size()*sizeof(glm::vec3), &q_vertices[0], GL_STATIC_DRAW);


	glVertexAttribPointer(0,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
		3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
		GL_FLOAT, // What type these components are
		GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
		3 * sizeof(GLfloat), // Offset between consecutive vertex attributes. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
		(GLvoid*)0); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
}

Curve::~Curve()
{
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VDO);
	glDeleteBuffers(1, &VCO);
}

void Curve::draw(GLuint shaderProgram)
{
	glUseProgram(shaderProgram);

	glm::mat4 MVP = Window::P * Window::V * toWorld;
	GLuint MatrixID = glGetUniformLocation(shaderProgram, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glPointSize(10);
	glBindVertexArray(VAO);
	//test c1, c2, c3, c4

	glLineWidth(3);
	glDrawArrays(GL_LINES, 0, q_vertices.size());
	glBindVertexArray(0);
}

void Curve::update(GLuint mod, glm::vec3 control_point)
{
	this->vertices[mod - 1] = control_point;
	cout << "reach curve update" << endl;
	m[0] = vertices[0];
	m[1] = vertices[1];
	m[2] = vertices[2];
	m[3] = vertices[3];
	glm::vec3 q0 = m[0];
	glm::vec3 q1 = m[3];

	std::vector<glm::vec3> update_vertices;
	update_vertices.push_back(q0);

	max = vertices[0].y;
	maxtime = 0;
	for (GLfloat i = 0.01; i < 1.0f; i = i + 0.01) {
		glm::vec4 ct_q = cal_ct(i);
		glm::vec3 q_point = m*ct_q;
		if (q_point.y > max) {
			highest = q_point;
			max = q_point.y;
			maxtime = i;
		}
		update_vertices.push_back(q_point);
		update_vertices.push_back(q_point);
	}
	update_vertices.push_back(q1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, update_vertices.size()*sizeof(glm::vec3), &update_vertices[0], GL_STATIC_DRAW);
	glBindVertexArray(0);
}

glm::vec4 Curve::cal_ct(float t)
{
	glm::vec4 ct;
	ct.x = pow((1 - t), 3);
	ct.y = 3 * t * pow((1 - t), 2);
	ct.z = 3 * (1 - t) * pow(t, 2);
	ct.w = pow(t, 3);
	return ct;
}

/*void Curve::drawPoints(GLuint pointShader, GLuint ID) {
	glGenVertexArrays(1, &VDO);
	glGenBuffers(1, &VCO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VDO);

	glBindBuffer(GL_ARRAY_BUFFER, VCO);
	glBufferData(GL_ARRAY_BUFFER, point_vertices.size()*sizeof(glm::vec3), &point_vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0,// This first parameter x should be the same as the number passed into the line "layout (location = x)" in the vertex shader. In this case, it's 0. Valid values are 0 to GL_MAX_UNIFORM_LOCATIONS.
		3, // This second line tells us how any components there are per vertex. In this case, it's 3 (we have an x, y, and z component)
		GL_FLOAT, // What type these components are
		GL_FALSE, // GL_TRUE means the values should be normalized. GL_FALSE means they shouldn't
		3 * sizeof(GLfloat), // Offset between consecutive vertex attributes. Since each of our vertices have 3 floats, they should have the size of 3 floats in between
		(GLvoid*)0); // Offset of the first vertex's component. In our case it's 0 since we don't pad the vertices array with anything.

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0);

	//
	glUseProgram(pointShader);
	glm::mat4 MVP = Window::P * Window::V * toWorld;
	GLuint MatrixID = glGetUniformLocation(pointShader, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glPointSize(8);
	glBindVertexArray(VDO);

	GLuint idLocation = glGetUniformLocation(pointShader, "id");
	glUniform1ui(idLocation, ID);
	glDrawArrays(GL_POINTS, 0, point_vertices.size());
	glBindVertexArray(0);
}*/

