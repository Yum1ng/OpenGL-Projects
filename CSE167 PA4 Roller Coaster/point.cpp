#include "point.h"
#include "Window.h"
#include "Track.h"

point::point() {}
point::point(glm::vec3 position)
{
	this->pointposition = position;
	this->point_vertices.push_back(pointposition);

	this->toWorld = glm::mat4(1.0f);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, this->point_vertices.size()*sizeof(glm::vec3), &point_vertices[0], GL_STATIC_DRAW);


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


point::~point()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void point::drawPoints(GLuint pointShader, GLuint ID) {

	glUseProgram(pointShader);
	glm::mat4 MVP = Window::P * Window::V * toWorld;
	GLuint MatrixID = glGetUniformLocation(pointShader, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glPointSize(10);
	glEnable(GL_POINT_SMOOTH);
	glBindVertexArray(VAO);

	GLuint idLocation = glGetUniformLocation(pointShader, "id");
	glUniform1ui(idLocation, ID);

	GLuint id2 = 0;
	if (ID % 3 != 1) {
		id2 = 1;
	}
	GLuint idLocation2 = glGetUniformLocation(pointShader, "id2");
	glUniform1ui(idLocation2, id2);
	//cout << "ID: " << ID << endl;
	glDrawArrays(GL_POINTS, 0, point_vertices.size());
	glBindVertexArray(0);
}

glm::vec3 point::move(GLfloat x, GLfloat y, glm::vec3 vx, glm::vec3 vy) {
//	this->point_vertices[0].x += x;
//	this->point_vertices[0].y -= y;
	this->point_vertices[0] += glm::vec3(x) * vx + glm::vec3(y) * vy;

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, this->point_vertices.size()*sizeof(glm::vec3), &point_vertices[0], GL_STATIC_DRAW);
	glBindVertexArray(0);
	return point_vertices[0];
}