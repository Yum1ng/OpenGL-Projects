#pragma once
#include "Curve.h"
#include "point.h"
#include <vector>
using namespace std;

class Track : public Curve
{
public:
	Track();
	~Track();
	static vector<Curve*> children;
	vector<point*> points;
	Curve* c1;
	Curve* c2;
	Curve* c3;
	Curve* c4;
	Curve* c5;
	Curve* c6;
	Curve* c7;
	Curve* c8;
	void addChild(Curve*);
	void removeChild(Curve*);

	void draw(GLuint);
	void drawpoint(GLuint);
	void drawLine(GLuint);
	void update();
	void update(GLuint id, GLuint mod, glm::vec3 contorl_point_position);

	std::vector<glm::vec3> point_vertices;
};

