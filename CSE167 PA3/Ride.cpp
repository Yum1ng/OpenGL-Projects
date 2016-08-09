#include "Ride.h"
using namespace std;


Ride::Ride(GLint shaderprogram)
{
	cylinder = new OBJObject("S:/cse167/CSE167-Starter-Code-3-master/cylinder.obj");
	pod = new OBJObject("S:/cse167/CSE167-Starter-Code-3-master/pod.obj");
	bear = new OBJObject("S:/cse167/CSE167-Starter-Code-master/bear.obj");
	cam = new Camera();
	shader = shaderprogram;
	root = new MatrixTransform();
	up_down_count = 0.5;
	vertical_long = 1.0;
	vertical_go_up = true;
	mt_bear = new MatrixTransform();
	mt_arms = new MatrixTransform();
	mt_arm00 = new MatrixTransform();

	mt_arm0 = new MatrixTransform();
	mt_armn0 = new MatrixTransform();

	mt_bowl = new MatrixTransform();


	mt_arm1 = new MatrixTransform();
	mt_arm2 = new MatrixTransform();
	mt_arm3 = new MatrixTransform();
	mt_cyl00 = new MatrixTransform();

	mt_cyln01 = new MatrixTransform();
	mt_cyln02 = new MatrixTransform();
	mt_cyln03 = new MatrixTransform();

	mt_cyl01 = new MatrixTransform();

	mt_cyl02 = new MatrixTransform();
	mt_cyl03 = new MatrixTransform();

	mt_cyl1 = new MatrixTransform();
	mt_cyl2 = new MatrixTransform();
	mt_cyl3 = new MatrixTransform();
	mt_cyl4 = new MatrixTransform();
	mt_cyl5 = new MatrixTransform();
	mt_cyl6 = new MatrixTransform();
	mt_cyl7 = new MatrixTransform();
	mt_cyl8 = new MatrixTransform();
	mt_cyl9 = new MatrixTransform();

	mt_pod1 = new MatrixTransform();
	mt_pod2 = new MatrixTransform();
	mt_pod3 = new MatrixTransform();
	mt_pod4 = new MatrixTransform();
	mt_pod5 = new MatrixTransform();
	mt_pod6 = new MatrixTransform();
	mt_pod7 = new MatrixTransform();
	mt_pod8 = new MatrixTransform();
	mt_pod9 = new MatrixTransform();

	//level 2
	mt_armn2 = new MatrixTransform();
	mt_cyln21 = new MatrixTransform();
	mt_cyln22 = new MatrixTransform();
	mt_cyln23 = new MatrixTransform();
	glm::mat4 test = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));
	g_cyln21 = new Cylinder(cylinder, shader, test);
	g_cyln22 = new Cylinder(cylinder, shader, test);
	g_cyln23 = new Cylinder(cylinder, shader, test);
	g_bowl = new Cylinder(cylinder, shader, test);
	//
	g_cyl00 = new Cylinder(cylinder, shader, glm::mat4(0.0f));
	g_cyl01 = new Cylinder(cylinder, shader, glm::mat4(0.0f));
	g_cyl02 = new Cylinder(cylinder, shader, glm::mat4(0.0f));
	g_cyl03 = new Cylinder(cylinder, shader, glm::mat4(0.0f));
	

	
	
	//glm::mat4 test = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));
	g_cyl1 = new Cylinder(cylinder, shader, test);
	g_cyl2 = new Cylinder(cylinder, shader, test);
	g_cyl3 = new Cylinder(cylinder, shader, test);
	g_cyln01 = new Cylinder(cylinder, shader, test);
	g_cyln02 = new Cylinder(cylinder, shader, test);
	g_cyln03 = new Cylinder(cylinder, shader, test);
	mt_arm01 = new MatrixTransform();
	mt_arm02 = new MatrixTransform();
	mt_arm03 = new MatrixTransform();

	glm::mat4 test01 = glm::translate(glm::mat4(1.0f), glm::vec3(2.5, 0.0, 0.0));
	g_cyl4 = new Cylinder(cylinder, shader, test01);
	g_cyl5 = new Cylinder(cylinder, shader, test01);
	g_cyl6 = new Cylinder(cylinder, shader, test01);

	g_pod1 = new Pod(pod, shader);
	g_pod2 = new Pod(pod, shader);
	g_pod3 = new Pod(pod, shader);
	g_pod4 = new Pod(pod, shader);
	g_pod5 = new Pod(pod, shader);
	g_pod6 = new Pod(pod, shader);
	//root set-up
	root->addChild(mt_arms);
	//arms set-up
	mt_arms->addChild(mt_arm00);
	mt_arm00->addChild(mt_cyl00);
	mt_cyl00->addChild(g_cyl00);
	
	S = glm::scale(glm::mat4(), glm::vec3(0.2f, 5.0f, 0.2f));
	mt_cyl00->update(S);

	mt_arm00->addChild(mt_bowl);
	mt_bowl->addChild(g_bowl);

	mt_arm00->addChild(mt_arm0);
	mt_arm0->addChild(mt_cyl01);
	mt_cyl01->addChild(g_cyl01);


	mt_arm0->addChild(mt_cyl02);
	mt_cyl02->addChild(g_cyl02);
	mt_arm0->addChild(mt_cyl03);
	mt_cyl03->addChild(g_cyl03);

	mt_arm00->addChild(mt_armn0);
	mt_armn0->addChild(mt_cyln01);
	mt_cyln01->addChild(g_cyln01);
	mt_armn0->addChild(mt_cyln02);
	mt_cyln02->addChild(g_cyln02);
	mt_armn0->addChild(mt_cyln03);
	mt_cyln03->addChild(g_cyln03);

	mt_arm00->addChild(mt_armn2);
	mt_armn2->addChild(mt_cyln21);
	mt_cyln21->addChild(g_cyln21);
	mt_armn2->addChild(mt_cyln22);
	mt_cyln22->addChild(g_cyln22);
	mt_armn2->addChild(mt_cyln23);
	mt_cyln23->addChild(g_cyln23);
	//	789
	g_cyl7 = new Cylinder(cylinder, shader, test01);
	g_cyl8 = new Cylinder(cylinder, shader, test01);
	g_cyl9 = new Cylinder(cylinder, shader, test01);
	g_pod7 = new Pod(pod, shader);
	g_pod8 = new Pod(pod, shader);
	g_pod9 = new Pod(pod, shader);

	// level 0
	mt_armn01 = new MatrixTransform();
	mt_cyl001 = new MatrixTransform();
	mt_cyl002 = new MatrixTransform();
	mt_cyl003 = new MatrixTransform();
	mt_pod001 = new MatrixTransform();
	mt_pod002 = new MatrixTransform();
	mt_pod003 = new MatrixTransform();

	g_cyl001 = new Cylinder(cylinder, shader, test01);
	g_cyl002 = new Cylinder(cylinder, shader, test01);
	g_cyl003 = new Cylinder(cylinder, shader, test01);
	g_pod001 = new Pod(pod, shader);
	g_pod002 = new Pod(pod, shader);
	g_pod003 = new Pod(pod, shader);

	mt_armn02 = new MatrixTransform();
	mt_cyl004 = new MatrixTransform();
	mt_cyl005 = new MatrixTransform();
	mt_cyl006 = new MatrixTransform();
	mt_pod004 = new MatrixTransform();
	mt_pod005 = new MatrixTransform();
	mt_pod006 = new MatrixTransform();

	g_cyl004 = new Cylinder(cylinder, shader, test01);
	g_cyl005 = new Cylinder(cylinder, shader, test01);
	g_cyl006 = new Cylinder(cylinder, shader, test01);
	g_pod004 = new Pod(pod, shader);
	g_pod005 = new Pod(pod, shader);
	g_pod006 = new Pod(pod, shader);

	mt_armn03 = new MatrixTransform();
	mt_cyl007 = new MatrixTransform();
	mt_cyl008 = new MatrixTransform();
	mt_cyl009 = new MatrixTransform();
	mt_pod007 = new MatrixTransform();
	mt_pod008 = new MatrixTransform();
	mt_pod009 = new MatrixTransform();

	g_cyl007 = new Cylinder(cylinder, shader, test01);
	g_cyl008 = new Cylinder(cylinder, shader, test01);
	g_cyl009 = new Cylinder(cylinder, shader, test01);
	g_pod007 = new Pod(pod, shader);
	g_pod008 = new Pod(pod, shader);
	g_pod009 = new Pod(pod, shader);
	//level 2
	mt_armn21 = new MatrixTransform();
	mt_cyl211 = new MatrixTransform();
	mt_cyl212 = new MatrixTransform();
	mt_cyl213 = new MatrixTransform();
	mt_pod211 = new MatrixTransform();
	mt_pod212 = new MatrixTransform();
	mt_pod213 = new MatrixTransform();

	g_cyl211 = new Cylinder(cylinder, shader, test01);
	g_cyl212 = new Cylinder(cylinder, shader, test01);
	g_cyl213 = new Cylinder(cylinder, shader, test01);
	g_pod211 = new Pod(pod, shader);
	g_pod212 = new Pod(pod, shader);
	g_pod213 = new Pod(pod, shader);

	mt_armn22 = new MatrixTransform();
	mt_cyl214 = new MatrixTransform();
	mt_cyl215 = new MatrixTransform();
	mt_cyl216 = new MatrixTransform();
	mt_pod214 = new MatrixTransform();
	mt_pod215 = new MatrixTransform();
	mt_pod216 = new MatrixTransform();

	g_cyl214 = new Cylinder(cylinder, shader, test01);
	g_cyl215 = new Cylinder(cylinder, shader, test01);
	g_cyl216 = new Cylinder(cylinder, shader, test01);
	g_pod214 = new Pod(pod, shader);
	g_pod215 = new Pod(pod, shader);
	g_pod216 = new Pod(pod, shader);

	mt_armn23 = new MatrixTransform();
	mt_cyl217 = new MatrixTransform();
	mt_cyl218 = new MatrixTransform();
	mt_cyl219 = new MatrixTransform();
	mt_pod217 = new MatrixTransform();
	mt_pod218 = new MatrixTransform();
	mt_pod219 = new MatrixTransform();

	g_cyl217 = new Cylinder(cylinder, shader, test01);
	g_cyl218 = new Cylinder(cylinder, shader, test01);
	g_cyl219 = new Cylinder(cylinder, shader, test01);
	g_pod217 = new Pod(pod, shader);
	g_pod218 = new Pod(pod, shader);
	g_pod219 = new Pod(pod, shader);

	//mt_cyl01->addChild(mt_arm1);

/*	mt_cyl01->addChild(mt_arm1);
	mt_arm1->addChild(mt_cyl1);
	mt_arm1->addChild(mt_cyl2);
	mt_arm1->addChild(mt_cyl3);
	mt_arm1->addChild(mt_pod1);
	mt_arm1->addChild(mt_pod2);
	mt_arm1->addChild(mt_pod3);
	mt_cyl1->addChild(g_cyl1);
	mt_cyl2->addChild(g_cyl2);
	mt_cyl3->addChild(g_cyl3);
	mt_pod1->addChild(g_pod1);
	mt_pod2->addChild(g_pod2);
	mt_pod3->addChild(g_pod3);*/

	
	//leaf set-up


	

//	R = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
	T = glm::translate(glm::mat4(), glm::vec3(0.0f, -2.5, 0.0));
	S = glm::scale(glm::mat4(), glm::vec3(1.5f, 0.5, 1.0));
	g_bowl->update(T*S);
	
	
	//level 1
	R = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
	T = glm::translate(glm::mat4(), glm::vec3(0.5f, 0.0, 0.0));
	T2 = glm::translate(glm::mat4(), glm::vec3(0.75f, 0.0, 0.0));
	S = glm::scale(glm::mat4(), glm::vec3(2.5f, 0.2, 0.2));
	mt_cyl01->update(T2*T*S*R);
	R2 = glm::rotate(glm::mat4(), 120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_cyl02->update(R2*mt_cyl01->M);
	R2 = glm::rotate(glm::mat4(), -120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_cyl03->update(R2*mt_cyl01->M);
	//level 2
	R = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
	T = glm::translate(glm::mat4(), glm::vec3(0.5f, 0.0, 0.0));
	T2 = glm::translate(glm::mat4(), glm::vec3(0.75f, 0.0, 0.0));
	S = glm::scale(glm::mat4(), glm::vec3(2.5f, 0.2, 0.2));
	mt_cyln01->update(T2*T*S*R);
	R2 = glm::rotate(glm::mat4(), 120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_cyln02->update(R2*mt_cyln01->M);
	R2 = glm::rotate(glm::mat4(), -120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_cyln03->update(R2*mt_cyln01->M);

	T = glm::translate(glm::mat4(), glm::vec3(0.0f, -2.5f, 0.0));
	mt_cyln01->update(T);
	mt_cyln02->update(T);
	mt_cyln03->update(T);
	//level 3
	R = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
	T = glm::translate(glm::mat4(), glm::vec3(0.5f, 0.0, 0.0));
	T2 = glm::translate(glm::mat4(), glm::vec3(0.75f, 0.0, 0.0));
	S = glm::scale(glm::mat4(), glm::vec3(2.5f, 0.2, 0.2));
	mt_cyln21->update(T2*T*S*R);
	R2 = glm::rotate(glm::mat4(), 120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_cyln22->update(R2*mt_cyln21->M);
	R2 = glm::rotate(glm::mat4(), -120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_cyln23->update(R2*mt_cyln21->M);

	T = glm::translate(glm::mat4(), glm::vec3(0.0f, 2.5f, 0.0));
	mt_cyln21->update(T);
	mt_cyln22->update(T);
	mt_cyln23->update(T);

	//mt_arm00->update(T); 

	//123
	mt_cyl01->addChild(mt_arm1);
	mt_arm1->addChild(mt_cyl1);
	mt_cyl1->addChild(g_cyl1);
	mt_arm1->addChild(mt_cyl2);
	mt_cyl2->addChild(g_cyl2);
	mt_arm1->addChild(mt_cyl3);
	mt_cyl3->addChild(g_cyl3);

	R = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
	T = glm::translate(glm::mat4(), glm::vec3(0.25f, 0.0, 0.0));
	S = glm::scale(glm::mat4(), glm::vec3(0.5f, 0.2, 0.2));
	TSR = T*S*R;
	mt_cyl1->update(TSR);
	R2 = glm::rotate(glm::mat4(), 120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_cyl2->update(R2*mt_cyl1->M);
	R2 = glm::rotate(glm::mat4(), -120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_cyl3->update(R2*mt_cyl1->M);

	mt_arm1->addChild(mt_pod1);
	mt_arm1->addChild(mt_pod2);
	mt_arm1->addChild(mt_pod3);
	mt_pod1->addChild(g_pod1);
	mt_pod2->addChild(g_pod2);
	mt_pod3->addChild(g_pod3);
	R = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	T = glm::translate(glm::mat4(), glm::vec3(0.5f, 0.15, 0.0));
	S = S = glm::scale(glm::mat4(), glm::vec3(0.5f, 0.5, 0.5));
	TSR = T*S*R;
	mt_pod1->update(TSR);
	R2 = glm::rotate(glm::mat4(), 120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_pod2->update(R2*mt_pod1->M);
	R2 = glm::rotate(glm::mat4(), -120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_pod3->update(R2*mt_pod1->M);
	
	R = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	T2 = glm::translate(glm::mat4(), glm::vec3(2.5f, 0.2, 0.0));
	S = S = glm::scale(glm::mat4(), glm::vec3(0.4f, 0.4, 0.4));
	bear->toWorld = T2*S*R*bear->toWorld;

	R = glm::rotate(glm::mat4(), 90.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	T2 = glm::translate(glm::mat4(), glm::vec3(2.3f, 0.2, 0.2));
	//T = glm::translate(glm::mat4(), glm::vec3(-0.5f, 0.5, 0.5));
	cam->bearMatrix = T2*R*cam->bearMatrix;
	
	T = glm::translate(glm::mat4(), glm::vec3(2.0f, 0.0, 0.0));

	mt_arm1->update(T);



	cout << "~~~arm1->M[3][0]" << mt_arm1->M[3][0] << endl;
	cout << "arm1->M[3][1]" << mt_arm1->M[3][1] << endl;
	cout << "arm1->M[3][2]" << mt_arm1->M[3][2] << endl;
	cout << "cyl1->M[3][0]" << g_cyl1->M[3][0] << endl;
	cout << "cyl1->M[3][1]" << g_cyl1->M[3][1] << endl;
	cout << "cyl1->M[3][2]" << g_cyl1->M[3][2] << endl;
	cout << "!!!!!" << endl;
	cout << "arm1->M[3][0]" << mt_arm1->M[3][0] << endl;
	cout << "arm1->M[3][1]" << mt_arm1->M[3][1] << endl;
	cout << "arm1->M[3][2]" << mt_arm1->M[3][2] << endl;
	cout << "cyl1->M[3][0]" << g_cyl1->M[3][0] << endl;
	cout << "cyl1->M[3][1]" << g_cyl1->M[3][1] << endl;
	cout << "cyl1->M[3][2]" << g_cyl1->M[3][2] << endl;

	//456
	mt_cyl02->addChild(mt_arm2);
	mt_arm2->addChild(mt_cyl4);
	mt_arm2->addChild(mt_cyl5);
	mt_arm2->addChild(mt_cyl6);
	mt_cyl4->addChild(g_cyl4);
	mt_cyl5->addChild(g_cyl5);
	mt_cyl6->addChild(g_cyl6);

	R = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
	T = glm::translate(glm::mat4(), glm::vec3(0.25f, 0.0, 0.0));
	S = glm::scale(glm::mat4(), glm::vec3(0.5f, 0.2, 0.2));
	TSR = T*S*R;
	mt_cyl4->update(TSR);
	R2 = glm::rotate(glm::mat4(), 120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_cyl5->update(R2*mt_cyl4->M);
	R2 = glm::rotate(glm::mat4(), -120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_cyl6->update(R2*mt_cyl4->M);

	mt_arm2->addChild(mt_pod4);
	mt_arm2->addChild(mt_pod5);
	mt_arm2->addChild(mt_pod6);
	mt_pod4->addChild(g_pod4);
	mt_pod5->addChild(g_pod5);
	mt_pod6->addChild(g_pod6);

	R = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	T = glm::translate(glm::mat4(), glm::vec3(0.5f, 0.15, 0.0));
	S = S = glm::scale(glm::mat4(), glm::vec3(0.5f, 0.5, 0.5));
	TSR = T*S*R;
	mt_pod4->update(TSR);
	R2 = glm::rotate(glm::mat4(), 120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_pod5->update(R2*mt_pod4->M);
	R2 = glm::rotate(glm::mat4(), -120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_pod6->update(R2*mt_pod4->M);

	R = glm::rotate(glm::mat4(), 120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	T = glm::translate(glm::mat4(), glm::vec3(2.0f, 0.0, 0.0));
	mt_arm2->update(R*T);

	//789
	mt_cyl03->addChild(mt_arm3);
	mt_arm3->addChild(mt_cyl7);
	mt_arm3->addChild(mt_cyl8);
	mt_arm3->addChild(mt_cyl9);
	mt_cyl7->addChild(g_cyl7);
	mt_cyl8->addChild(g_cyl8);
	mt_cyl9->addChild(g_cyl9);

	R = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
	T = glm::translate(glm::mat4(), glm::vec3(0.25f, 0.0, 0.0));
	S = glm::scale(glm::mat4(), glm::vec3(0.5f, 0.2, 0.2));
	TSR = T*S*R;
	mt_cyl7->update(TSR);
	R2 = glm::rotate(glm::mat4(), 120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_cyl8->update(R2*mt_cyl7->M);
	R2 = glm::rotate(glm::mat4(), -120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_cyl9->update(R2*mt_cyl7->M);

	mt_arm3->addChild(mt_pod7);
	mt_arm3->addChild(mt_pod8);
	mt_arm3->addChild(mt_pod9);
	mt_pod7->addChild(g_pod7);
	mt_pod8->addChild(g_pod8);
	mt_pod9->addChild(g_pod9);

	R = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	T = glm::translate(glm::mat4(), glm::vec3(0.5f, 0.15, 0.0));
	S = S = glm::scale(glm::mat4(), glm::vec3(0.5f, 0.5, 0.5));
	TSR = T*S*R;
	mt_pod7->update(TSR);
	R2 = glm::rotate(glm::mat4(), 120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_pod8->update(R2*mt_pod7->M);
	R2 = glm::rotate(glm::mat4(), -120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_pod9->update(R2*mt_pod7->M);

	R = glm::rotate(glm::mat4(), -120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	T = glm::translate(glm::mat4(), glm::vec3(2.0f, 0.0, 0.0));
	mt_arm3->update(R*T);

	//level 0000000
	//123
	mt_cyln01->addChild(mt_armn01);
	mt_armn01->addChild(mt_cyl001);
	mt_cyl001->addChild(g_cyl001);
	mt_armn01->addChild(mt_cyl002);
	mt_cyl002->addChild(g_cyl002);
	mt_armn01->addChild(mt_cyl003);
	mt_cyl003->addChild(g_cyl003);

	R = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
	T = glm::translate(glm::mat4(), glm::vec3(0.25f, 0.0, 0.0));
	S = glm::scale(glm::mat4(), glm::vec3(0.5f, 0.2, 0.2));
	TSR = T*S*R;
	mt_cyl001->update(TSR);
	R2 = glm::rotate(glm::mat4(), 120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_cyl002->update(R2*mt_cyl001->M);
	R2 = glm::rotate(glm::mat4(), -120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_cyl003->update(R2*mt_cyl001->M);

	mt_armn01->addChild(mt_pod001);
	mt_armn01->addChild(mt_pod002);
	mt_armn01->addChild(mt_pod003);
	mt_pod001->addChild(g_pod001);
	mt_pod002->addChild(g_pod002);
	mt_pod003->addChild(g_pod003);

	R = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	T = glm::translate(glm::mat4(), glm::vec3(0.5f, 0.15, 0.0));
	S = S = glm::scale(glm::mat4(), glm::vec3(0.5f, 0.5, 0.5));
	TSR = T*S*R;
	mt_pod001->update(TSR);
	R2 = glm::rotate(glm::mat4(), 120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_pod002->update(R2*mt_pod001->M);
	R2 = glm::rotate(glm::mat4(), -120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_pod003->update(R2*mt_pod001->M);

	T = glm::translate(glm::mat4(), glm::vec3(1.0f, 0.0, 0.0));
	mt_armn01->update(T);

	T = glm::translate(glm::mat4(), glm::vec3(0.0f, -2.5, 0.0));
	mt_armn01->update(T);
	
	//456
	mt_cyln02->addChild(mt_armn02);
	mt_armn02->addChild(mt_cyl004);
	mt_armn02->addChild(mt_cyl005);
	mt_armn02->addChild(mt_cyl006);
	mt_cyl004->addChild(g_cyl004);
	mt_cyl005->addChild(g_cyl005);
	mt_cyl006->addChild(g_cyl006);

	R = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
	T = glm::translate(glm::mat4(), glm::vec3(0.25f, 0.0, 0.0));
	S = glm::scale(glm::mat4(), glm::vec3(0.5f, 0.2, 0.2));
	TSR = T*S*R;
	mt_cyl004->update(TSR);
	R2 = glm::rotate(glm::mat4(), 120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_cyl005->update(R2*mt_cyl004->M);
	R2 = glm::rotate(glm::mat4(), -120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_cyl006->update(R2*mt_cyl004->M);

	mt_armn02->addChild(mt_pod004);
	mt_armn02->addChild(mt_pod005);
	mt_armn02->addChild(mt_pod006);
	mt_pod004->addChild(g_pod004);
	mt_pod005->addChild(g_pod005);
	mt_pod006->addChild(g_pod006);

	R = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	T = glm::translate(glm::mat4(), glm::vec3(0.5f, 0.15, 0.0));
	S = S = glm::scale(glm::mat4(), glm::vec3(0.5f, 0.5, 0.5));
	TSR = T*S*R;
	mt_pod004->update(TSR);
	R2 = glm::rotate(glm::mat4(), 120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_pod005->update(R2*mt_pod004->M);
	R2 = glm::rotate(glm::mat4(), -120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_pod006->update(R2*mt_pod004->M);

	T = glm::translate(glm::mat4(), glm::vec3(0.5f, 0.0, 0.0));
	mt_cyl004->update(T);
	mt_cyl005->update(T);
	mt_cyl006->update(T);
	mt_pod004->update(T);
	mt_pod005->update(T);
	mt_pod006->update(T);
//	mt_armn02->update(T);

	T = glm::translate(glm::mat4(), glm::vec3(0.0f, -2.5, 0.0));
//	mt_armn02->update(T);
	mt_cyl004->update(T);
	mt_cyl005->update(T);
	mt_cyl006->update(T);
	mt_pod004->update(T);
	mt_pod005->update(T);
	mt_pod006->update(T);

	R = glm::rotate(glm::mat4(), 120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	T = glm::translate(glm::mat4(), glm::vec3(2.0f, 0.0, 0.0));
	mt_armn02->update(R*T);
	//789
	mt_cyln03->addChild(mt_armn03);
	mt_armn03->addChild(mt_cyl007);
	mt_armn03->addChild(mt_cyl008);
	mt_armn03->addChild(mt_cyl009);
	mt_cyl007->addChild(g_cyl007);
	mt_cyl008->addChild(g_cyl008);
	mt_cyl009->addChild(g_cyl009);

	R = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
	T = glm::translate(glm::mat4(), glm::vec3(0.25f, 0.0, 0.0));
	S = glm::scale(glm::mat4(), glm::vec3(0.5f, 0.2, 0.2));
	TSR = T*S*R;
	mt_cyl007->update(TSR);
	R2 = glm::rotate(glm::mat4(), 120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_cyl008->update(R2*mt_cyl007->M);
	R2 = glm::rotate(glm::mat4(), -120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_cyl009->update(R2*mt_cyl007->M);

	mt_armn03->addChild(mt_pod007);
	mt_armn03->addChild(mt_pod008);
	mt_armn03->addChild(mt_pod009);
	mt_pod007->addChild(g_pod007);
	mt_pod008->addChild(g_pod008);
	mt_pod009->addChild(g_pod009);

	R = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	T = glm::translate(glm::mat4(), glm::vec3(0.5f, 0.15, 0.0));
	S = S = glm::scale(glm::mat4(), glm::vec3(0.5f, 0.5, 0.5));
	TSR = T*S*R;
	mt_pod007->update(TSR);
	R2 = glm::rotate(glm::mat4(), 120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_pod008->update(R2*mt_pod007->M);
	R2 = glm::rotate(glm::mat4(), -120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_pod009->update(R2*mt_pod007->M);

	T = glm::translate(glm::mat4(), glm::vec3(0.5f, 0.0, 0.0));
	mt_cyl007->update(T);
	mt_cyl008->update(T);
	mt_cyl009->update(T);
	mt_pod007->update(T);
	mt_pod008->update(T);
	mt_pod009->update(T);
	//	mt_armn02->update(T);

	T = glm::translate(glm::mat4(), glm::vec3(0.0f, -2.5, 0.0));
	//	mt_armn02->update(T);
	mt_cyl007->update(T);
	mt_cyl008->update(T);
	mt_cyl009->update(T);
	mt_pod007->update(T);
	mt_pod008->update(T);
	mt_pod009->update(T);

	R = glm::rotate(glm::mat4(), -120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	T = glm::translate(glm::mat4(), glm::vec3(2.0f, 0.0, 0.0));
	mt_armn03->update(R*T);
	//level 2

	mt_cyln21->addChild(mt_armn21);
	mt_armn21->addChild(mt_cyl211);
	mt_cyl211->addChild(g_cyl211);
	mt_armn21->addChild(mt_cyl212);
	mt_cyl212->addChild(g_cyl212);
	mt_armn21->addChild(mt_cyl213);
	mt_cyl213->addChild(g_cyl213);

	R = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
	T = glm::translate(glm::mat4(), glm::vec3(0.25f, 0.0, 0.0));
	S = glm::scale(glm::mat4(), glm::vec3(0.5f, 0.2, 0.2));
	TSR = T*S*R;
	mt_cyl211->update(TSR);
	R2 = glm::rotate(glm::mat4(), 120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_cyl212->update(R2*mt_cyl211->M);
	R2 = glm::rotate(glm::mat4(), -120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_cyl213->update(R2*mt_cyl211->M);

	mt_armn21->addChild(mt_pod211);
	mt_armn21->addChild(mt_pod212);
	mt_armn21->addChild(mt_pod213);
	mt_pod211->addChild(g_pod211);
	mt_pod212->addChild(g_pod212);
	mt_pod213->addChild(g_pod213);

	R = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	T = glm::translate(glm::mat4(), glm::vec3(0.5f, 0.15, 0.0));
	S = S = glm::scale(glm::mat4(), glm::vec3(0.5f, 0.5, 0.5));
	TSR = T*S*R;
	mt_pod211->update(TSR);
	R2 = glm::rotate(glm::mat4(), 120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_pod212->update(R2*mt_pod211->M);
	R2 = glm::rotate(glm::mat4(), -120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_pod213->update(R2*mt_pod211->M);

	T = glm::translate(glm::mat4(), glm::vec3(1.0f, 0.0, 0.0));
	mt_armn21->update(T);

	T = glm::translate(glm::mat4(), glm::vec3(0.0f, 2.5, 0.0));
	mt_armn21->update(T);

	//456
	mt_cyln22->addChild(mt_armn22);
	mt_armn22->addChild(mt_cyl214);
	mt_armn22->addChild(mt_cyl215);
	mt_armn22->addChild(mt_cyl216);
	mt_cyl214->addChild(g_cyl214);
	mt_cyl215->addChild(g_cyl215);
	mt_cyl216->addChild(g_cyl216);

	R = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
	T = glm::translate(glm::mat4(), glm::vec3(0.25f, 0.0, 0.0));
	S = glm::scale(glm::mat4(), glm::vec3(0.5f, 0.2, 0.2));
	TSR = T*S*R;
	mt_cyl214->update(TSR);
	R2 = glm::rotate(glm::mat4(), 120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_cyl215->update(R2*mt_cyl214->M);
	R2 = glm::rotate(glm::mat4(), -120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_cyl216->update(R2*mt_cyl214->M);

	mt_armn22->addChild(mt_pod214);
	mt_armn22->addChild(mt_pod215);
	mt_armn22->addChild(mt_pod216);
	mt_pod214->addChild(g_pod214);
	mt_pod215->addChild(g_pod215);
	mt_pod216->addChild(g_pod216);

	R = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	T = glm::translate(glm::mat4(), glm::vec3(0.5f, 0.15, 0.0));
	S = S = glm::scale(glm::mat4(), glm::vec3(0.5f, 0.5, 0.5));
	TSR = T*S*R;
	mt_pod214->update(TSR);
	R2 = glm::rotate(glm::mat4(), 120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_pod215->update(R2*mt_pod214->M);
	R2 = glm::rotate(glm::mat4(), -120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_pod216->update(R2*mt_pod214->M);

	T = glm::translate(glm::mat4(), glm::vec3(0.5f, 0.0, 0.0));
	mt_cyl214->update(T);
	mt_cyl215->update(T);
	mt_cyl216->update(T);
	mt_pod214->update(T);
	mt_pod215->update(T);
	mt_pod216->update(T);
	//	mt_armn02->update(T);

	T = glm::translate(glm::mat4(), glm::vec3(0.0f, 2.5, 0.0));
	//	mt_armn02->update(T);
	mt_cyl214->update(T);
	mt_cyl215->update(T);
	mt_cyl216->update(T);
	mt_pod214->update(T);
	mt_pod215->update(T);
	mt_pod216->update(T);

	R = glm::rotate(glm::mat4(), 120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	T = glm::translate(glm::mat4(), glm::vec3(2.0f, 0.0, 0.0));
	mt_armn22->update(R*T);
	//789
	mt_cyln23->addChild(mt_armn23);
	mt_armn23->addChild(mt_cyl217);
	mt_armn23->addChild(mt_cyl218);
	mt_armn23->addChild(mt_cyl219);
	mt_cyl217->addChild(g_cyl217);
	mt_cyl218->addChild(g_cyl218);
	mt_cyl219->addChild(g_cyl219);

	R = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 0.0f, 1.0f));
	T = glm::translate(glm::mat4(), glm::vec3(0.25f, 0.0, 0.0));
	S = glm::scale(glm::mat4(), glm::vec3(0.5f, 0.2, 0.2));
	TSR = T*S*R;
	mt_cyl217->update(TSR);
	R2 = glm::rotate(glm::mat4(), 120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_cyl218->update(R2*mt_cyl217->M);
	R2 = glm::rotate(glm::mat4(), -120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_cyl219->update(R2*mt_cyl217->M);

	mt_armn23->addChild(mt_pod217);
	mt_armn23->addChild(mt_pod218);
	mt_armn23->addChild(mt_pod219);
	mt_pod217->addChild(g_pod217);
	mt_pod218->addChild(g_pod218);
	mt_pod219->addChild(g_pod219);

	R = glm::rotate(glm::mat4(), 270.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	T = glm::translate(glm::mat4(), glm::vec3(0.5f, 0.15, 0.0));
	S = S = glm::scale(glm::mat4(), glm::vec3(0.5f, 0.5, 0.5));
	TSR = T*S*R;
	mt_pod217->update(TSR);
	R2 = glm::rotate(glm::mat4(), 120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_pod218->update(R2*mt_pod217->M);
	R2 = glm::rotate(glm::mat4(), -120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	mt_pod219->update(R2*mt_pod217->M);

	T = glm::translate(glm::mat4(), glm::vec3(0.5f, 0.0, 0.0));
	mt_cyl217->update(T);
	mt_cyl218->update(T);
	mt_cyl219->update(T);
	mt_pod217->update(T);
	mt_pod218->update(T);
	mt_pod219->update(T);
	//	mt_armn02->update(T);

	T = glm::translate(glm::mat4(), glm::vec3(0.0f, 2.5, 0.0));
	//	mt_armn02->update(T);
	mt_cyl217->update(T);
	mt_cyl218->update(T);
	mt_cyl219->update(T);
	mt_pod217->update(T);
	mt_pod218->update(T);
	mt_pod219->update(T);

	R = glm::rotate(glm::mat4(), -120.0f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
	T = glm::translate(glm::mat4(), glm::vec3(2.0f, 0.0, 0.0));
	mt_armn23->update(R*T);

/*	T = glm::translate(glm::mat4(), glm::vec3(1.0f, 0.0f, 0.0));
	mt_arm1->update(T);
	mt_arm1->update(T);
	mt_arm1->update(T);
	T = glm::translate(glm::mat4(), glm::vec3(-16.0f, 0.0f, 0.0));
	mt_arm1->update(T);*/
//	mt_arm1->update(T);
}


Ride::~Ride()
{
}

void Ride::draw() {
	glUseProgram(shader);
	bear->draw(shader);
	root->draw();
}

void Ride::orbit(float ang) {
	root->orbit(ang);
	bear->orbit(ang);
	cam->orbit(ang);
/*	if (up_down_count > vertical_long) {
		vertical_go_up = false;
	}
	else if (up_down_count < 0.0f) {
		vertical_go_up = true;
	}
	if (vertical_go_up == false) {
	//	T = glm::translate(glm::mat4(), glm::vec3(0.0f, -0.01f, 0.0));
		T = glm::translate(glm::mat4(), glm::vec3(-0.0001f, 0.0f, 0.0));
		mt_arm1->update(T);
		up_down_count -= 0.5;
	}
	else if (vertical_go_up == true){
		//T = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.01f, 0.0));
		T = glm::translate(glm::mat4(), glm::vec3(0.0001f, 0.0f, 0.0));
		mt_arm1->update(T);
		up_down_count += 0.5;
	}*/
	//T = glm::translate(glm::mat4(), glm::vec3(0.0f, -1, 0.0));
	//mt_arm00->update(T);
	/*for (int i = -10; i < 10; i++) {

		offset = i * 0.05;
		T = glm::translate(glm::mat4(), glm::vec3(0.0f, offset, 0.0));
		mt_arm00->update(T);
		if (i == 9) i= -10;
	}*/
}