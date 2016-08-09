#pragma once
#include "Node.h"
#include <iostream>
#include <vector>
using namespace std;
class Group : public Node
{
public:
	Group();
	~Group();
	vector<Node*> children;
	void addChild(Node*);
	void removeChild(Node*);
	virtual void update(glm::mat4);
	virtual void draw();
	virtual void orbit(float);
};

