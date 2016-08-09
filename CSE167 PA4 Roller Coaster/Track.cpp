#include "Track.h"
#include "Window.h"


vector<Curve*> Track::children;

Track::Track()
{
	this->toWorld = glm::mat4(1.0f);
	glm::vec3 x1 = glm::vec3(0, 2, 0);
	glm::vec3 x2 = glm::vec3(1,  1, 0);
	glm::vec3 x3 = glm::vec3(2,-1, 0);
	glm::vec3 x4 = glm::vec3(3, 0, 0);
	Curve* c1 = new Curve(x1, x2, x3, x4);
	children.push_back(c1);
	point_vertices.push_back(x3);
	// push points
	point* p1 = new point(x1);
	points.push_back(p1);
	point* p2 = new point(x2);
	points.push_back(p2);
	point* p3 = new point(x3);
	points.push_back(p3);

	x1 = x4;
	x2 = x3 + (x4 - x3) * 2.0f;
	x3 = glm::vec3(4, -1, 0);
	x4 = glm::vec3(4, -1, 1);
	Curve* c2 = new Curve(x1, x2, x3, x4);
	children.push_back(c2);
	c1->next = c2;
	c2->prev = c1;
	point_vertices.push_back(x2);
	point_vertices.push_back(x3);
	// push points
	point* p4 = new point(x1);
	points.push_back(p4);
	point* p5 = new point(x2);
	points.push_back(p5);
	point* p6 = new point(x3);
	points.push_back(p6);

	x1 = x4;
	x2 = x3 + (x4 - x3) * 2.0f;
	x3 = glm::vec3(4, 2, 2);
	x4 = glm::vec3(4, 1, 3);
	Curve* c3 = new Curve(x1, x2, x3, x4);
	children.push_back(c3);
	c2->next = c3;
	c3->prev = c2;
	point_vertices.push_back(x2);
	point_vertices.push_back(x3);
	// push points
	point* p7 = new point(x1);
	points.push_back(p7);
	point* p8 = new point(x2);
	points.push_back(p8);
	point* p9 = new point(x3);
	points.push_back(p9);

	x1 = x4;
	x2 = x3 + (x4 - x3) * 2.0f;
	x3 = glm::vec3(3, -1, 2);
	x4 = glm::vec3(2, -1, 2);
	Curve* c4 = new Curve(x1, x2, x3, x4);
	children.push_back(c4);
	c3->next = c4;
	c4->prev = c3;
	point_vertices.push_back(x2);
	point_vertices.push_back(x3);
	// push points
	point* p10 = new point(x1);
	points.push_back(p10);
	point* p11 = new point(x2);
	points.push_back(p11);
	point* p12 = new point(x3);
	points.push_back(p12);

	x1 = x4;
	x2 = x3 + (x4 - x3) * 2.0f;
	x3 = glm::vec3(2, -0.5, 2);
	x4 = glm::vec3(1, -0.5, 2);
	Curve* c5 = new Curve(x1, x2, x3, x4);
	children.push_back(c5);
	c4->next = c5;
	c5->prev = c4;
	point_vertices.push_back(x2);
	point_vertices.push_back(x3);
	// push points
	point* p13 = new point(x1);
	points.push_back(p13);
	point* p14 = new point(x2);
	points.push_back(p14);
	point* p15 = new point(x3);
	points.push_back(p15);

	x1 = x4;
	x2 = x3 + (x4 - x3) * 2.0f;
	x3 = glm::vec3(1.5, -0.5, 2);
	x4 = glm::vec3(0.5, 0, 2);
	Curve* c6 = new Curve(x1, x2, x3, x4);
	children.push_back(c6);
	c5->next = c6;
	c6->prev = c5;
	point_vertices.push_back(x2);
	point_vertices.push_back(x3);
	// push points
	point* p16 = new point(x1);
	points.push_back(p16);
	point* p17 = new point(x2);
	points.push_back(p17);
	point* p18 = new point(x3);
	points.push_back(p18);

	x1 = x4;
	x2 = x3 + (x4 - x3) * 2.0f;
	x3 = glm::vec3(1, 1.0, 2);
	x4 = glm::vec3(0, 0, 1.5);
	Curve* c7 = new Curve(x1, x2, x3, x4);
	children.push_back(c7);
	c6->next = c7;
	c7->prev = c6;
	point_vertices.push_back(x2);
	point_vertices.push_back(x3);
	// push points
	point* p19 = new point(x1);
	points.push_back(p19);
	point* p20 = new point(x2);
	points.push_back(p20);
	point* p21 = new point(x3);
	points.push_back(p21);

	x1 = x4;
	x2 = x3 + (x4 - x3) * 2.0f;
	x3 = glm::vec3(1, 1, 0) + (glm::vec3(0, 2, 0) - glm::vec3(1, 1, 0))*2.0f;
	x4 = glm::vec3(0, 2, 0);
	Curve* c8 = new Curve(x1, x2, x3, x4);
	children.push_back(c8);
	c7->next = c8;
	c8->prev = c7;
	point_vertices.push_back(x2);
	point_vertices.push_back(x3);
	// push points
	point* p22 = new point(x1);
	points.push_back(p22);
	point* p23 = new point(x2);
	points.push_back(p23);
	point* p24 = new point(x3);
	points.push_back(p24);

	//go back
	x2 = glm::vec3(1, 1, 0);
	point_vertices.push_back(x2);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
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
}


Track::~Track()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Track::draw(GLuint shaderProgram) {
	for (int i = 0; i < children.size(); i++) {
		children[i]->draw(shaderProgram);
	}
}

void Track::drawpoint(GLuint pointShader) {
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < points.size(); i++) {
		points[i]->drawPoints(pointShader, i+1);
	}
}

void Track::drawLine(GLuint lineShader) {
	glUseProgram(lineShader);
	glm::mat4 MVP = Window::P * Window::V * toWorld;
	GLuint MatrixID = glGetUniformLocation(lineShader, "MVP");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glBindVertexArray(VAO);

	glLineWidth(1);
	glDrawArrays(GL_LINES, 0, point_vertices.size());
	glBindVertexArray(0);
}

void Track::update(GLuint id, GLuint mod, glm::vec3 contorl_point_position) {
	children[id]->update(mod, contorl_point_position);
	//formula to calculate point position to draw new lines
	if (mod == 2 || mod == 3) {
		if (id == 0 && mod == 2) {
			point_vertices[15] = contorl_point_position;
		}
		else {
			point_vertices[(id - 1) * 2 + mod - 1] = contorl_point_position;
		}
	}
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, this->point_vertices.size()*sizeof(glm::vec3), &point_vertices[0], GL_STATIC_DRAW);
	glBindVertexArray(0);
}