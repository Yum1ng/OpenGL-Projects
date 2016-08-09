#pragma once
#include "MatrixTransform.h"
#include "Geode.h"
#include "Cylinder.h"
#include "Pod.h"
#include "Camera.h"
class Ride
{
public:
	glm::mat4 R;
	glm::mat4 R2;
	glm::mat4 T;
	glm::mat4 T2;
	glm::mat4 S;
	glm::mat4 TSR;
	Ride(GLint shaderprogram);
	~Ride();
	void orbit(float);
	float offset;
	OBJObject* cylinder;
	OBJObject* pod;
	OBJObject* bear;
	Camera* cam;
	GLint shader;
	bool vertical_go_up;
	float up_down_count;
	float vertical_long;

	MatrixTransform* root;
	MatrixTransform* mt_bear;
	//Test
	MatrixTransform* armtest;
	MatrixTransform* mt_podtest;
	Pod * g_podtest;

	MatrixTransform* mt_arms;
	MatrixTransform* mt_arm0;
	MatrixTransform* mt_arm00;
	MatrixTransform* mt_arm1;
	MatrixTransform* mt_arm2;
	MatrixTransform* mt_arm3;
	MatrixTransform* mt_arm01;
	MatrixTransform* mt_arm02;
	MatrixTransform* mt_arm03;
	MatrixTransform* mt_armn0;

	MatrixTransform* mt_bowl;
	Cylinder * g_bowl;

	MatrixTransform* mt_cyl00;
	//level2
	
	//level 0
	MatrixTransform* mt_armn01;
	MatrixTransform* mt_armn02;
	MatrixTransform* mt_armn03;
	MatrixTransform* mt_cyln01;
	MatrixTransform* mt_cyln02;
	MatrixTransform* mt_cyln03;

	MatrixTransform* mt_cyl001;
	MatrixTransform* mt_cyl002;
	MatrixTransform* mt_cyl003;
	MatrixTransform* mt_pod001;
	MatrixTransform* mt_pod002;
	MatrixTransform* mt_pod003;
//	OBJObject * bear1;
	Cylinder * g_cyl001;
	Cylinder * g_cyl002;
	Cylinder * g_cyl003;

	Pod * g_pod001;
	Pod * g_pod002;
	Pod * g_pod003;

	MatrixTransform* mt_cyl004;
	MatrixTransform* mt_cyl005;
	MatrixTransform* mt_cyl006;
	MatrixTransform* mt_pod004;
	MatrixTransform* mt_pod005;
	MatrixTransform* mt_pod006;

	Cylinder * g_cyl004;
	Cylinder * g_cyl005;
	Cylinder * g_cyl006;

	Pod * g_pod004;
	Pod * g_pod005;
	Pod * g_pod006;

	MatrixTransform* mt_cyl007;
	MatrixTransform* mt_cyl008;
	MatrixTransform* mt_cyl009;
	MatrixTransform* mt_pod007;
	MatrixTransform* mt_pod008;
	MatrixTransform* mt_pod009;

	Cylinder * g_cyl007;
	Cylinder * g_cyl008;
	Cylinder * g_cyl009;

	Pod * g_pod007;
	Pod * g_pod008;
	Pod * g_pod009;
	
	//level2
	MatrixTransform* mt_armn2;
	MatrixTransform* mt_armn21;
	MatrixTransform* mt_armn22;
	MatrixTransform* mt_armn23;

	MatrixTransform* mt_cyln21;
	MatrixTransform* mt_cyln22;
	MatrixTransform* mt_cyln23;

	Cylinder * g_cyln21;
	Cylinder * g_cyln22;
	Cylinder * g_cyln23;


	MatrixTransform* mt_cyl211;
	MatrixTransform* mt_cyl212;
	MatrixTransform* mt_cyl213;
	MatrixTransform* mt_pod211;
	MatrixTransform* mt_pod212;
	MatrixTransform* mt_pod213;

	Cylinder * g_cyl211;
	Cylinder * g_cyl212;
	Cylinder * g_cyl213;

	Pod * g_pod211;
	Pod * g_pod212;
	Pod * g_pod213;

	MatrixTransform* mt_cyl214;
	MatrixTransform* mt_cyl215;
	MatrixTransform* mt_cyl216;
	MatrixTransform* mt_pod214;
	MatrixTransform* mt_pod215;
	MatrixTransform* mt_pod216;

	Cylinder * g_cyl214;
	Cylinder * g_cyl215;
	Cylinder * g_cyl216;

	Pod * g_pod214;
	Pod * g_pod215;
	Pod * g_pod216;

	MatrixTransform* mt_cyl217;
	MatrixTransform* mt_cyl218;
	MatrixTransform* mt_cyl219;
	MatrixTransform* mt_pod217;
	MatrixTransform* mt_pod218;
	MatrixTransform* mt_pod219;

	Cylinder * g_cyl217;
	Cylinder * g_cyl218;
	Cylinder * g_cyl219;

	Pod * g_pod217;
	Pod * g_pod218;
	Pod * g_pod219;

	//
	//level 1
	MatrixTransform* mt_cyl01;
	MatrixTransform* mt_cyl02;
	MatrixTransform* mt_cyl03;

	MatrixTransform* mt_cyl1;
	MatrixTransform* mt_cyl2;
	MatrixTransform* mt_cyl3;
	MatrixTransform* mt_cyl4;
	MatrixTransform* mt_cyl5;
	MatrixTransform* mt_cyl6;
	MatrixTransform* mt_cyl7;
	MatrixTransform* mt_cyl8;
	MatrixTransform* mt_cyl9;


	MatrixTransform* mt_pod1;
	MatrixTransform* mt_pod2;
	MatrixTransform* mt_pod3;
	MatrixTransform* mt_pod4;
	MatrixTransform* mt_pod5;
	MatrixTransform* mt_pod6;
	MatrixTransform* mt_pod7;
	MatrixTransform* mt_pod8;
	MatrixTransform* mt_pod9;
	Cylinder * g_cyl00;
	Cylinder * g_cyl01;
	Cylinder * g_cyl02;
	Cylinder * g_cyl03;

	Cylinder * g_cyln01;
	Cylinder * g_cyln02;
	Cylinder * g_cyln03;
	
	Cylinder * g_cyl1;
	Cylinder * g_cyl2;
	Cylinder * g_cyl3;
	Cylinder * g_cyl4;
	Cylinder * g_cyl5;
	Cylinder * g_cyl6;
	Cylinder * g_cyl7;
	Cylinder * g_cyl8;
	Cylinder * g_cyl9;


	Pod * g_pod1;
	Pod * g_pod2;
	Pod * g_pod3;
	Pod * g_pod4;
	Pod * g_pod5;
	Pod * g_pod6;
	Pod * g_pod7;
	Pod * g_pod8;
	Pod * g_pod9;
	//level 0
	MatrixTransform* mt_arm10;
	MatrixTransform* mt_arm11;
	MatrixTransform* mt_arm12;
	MatrixTransform* mt_arm13;
	MatrixTransform* mt_cyl011;
	MatrixTransform* mt_cyl012;
	MatrixTransform* mt_cyl013;

	MatrixTransform* mt_cyl11;
	MatrixTransform* mt_cyl12;
	MatrixTransform* mt_cyl13;
	MatrixTransform* mt_cyl14;
	MatrixTransform* mt_cyl15;
	MatrixTransform* mt_cyl16;
	MatrixTransform* mt_cyl17;
	MatrixTransform* mt_cyl18;
	MatrixTransform* mt_cyl19;

	MatrixTransform* mt_pod11;
	MatrixTransform* mt_pod12;
	MatrixTransform* mt_pod13;
	MatrixTransform* mt_pod14;
	MatrixTransform* mt_pod15;
	MatrixTransform* mt_pod16;
	MatrixTransform* mt_pod17;
	MatrixTransform* mt_pod18;
	MatrixTransform* mt_pod19;
	Cylinder * g_cyl011;
	Cylinder * g_cyl012;
	Cylinder * g_cyl013;

	Cylinder * g_cyl11;
	Cylinder * g_cyl12;
	Cylinder * g_cyl13;
	Cylinder * g_cyl14;
	Cylinder * g_cyl15;
	Cylinder * g_cyl16;
	Cylinder * g_cyl17;
	Cylinder * g_cyl18;
	Cylinder * g_cyl19;

	Pod * g_pod11;
	Pod * g_pod12;
	Pod * g_pod13;
	Pod * g_pod14;
	Pod * g_pod15;
	Pod * g_pod16;
	Pod * g_pod17;
	Pod * g_pod18;
	Pod * g_pod19;

	//level 2
	MatrixTransform* mt_arm20;
	MatrixTransform* mt_arm21;
	MatrixTransform* mt_arm22;
	MatrixTransform* mt_arm23;
	MatrixTransform* mt_cyl021;
	MatrixTransform* mt_cyl022;
	MatrixTransform* mt_cyl023;

	MatrixTransform* mt_cyl21;
	MatrixTransform* mt_cyl22;
	MatrixTransform* mt_cyl23;
	MatrixTransform* mt_cyl24;
	MatrixTransform* mt_cyl25;
	MatrixTransform* mt_cyl26;
	MatrixTransform* mt_cyl27;
	MatrixTransform* mt_cyl28;
	MatrixTransform* mt_cyl29;

	MatrixTransform* mt_pod21;
	MatrixTransform* mt_pod22;
	MatrixTransform* mt_pod23;
	MatrixTransform* mt_pod24;
	MatrixTransform* mt_pod25;
	MatrixTransform* mt_pod26;
	MatrixTransform* mt_pod27;
	MatrixTransform* mt_pod28;
	MatrixTransform* mt_pod29;
	Cylinder * g_cyl021;
	Cylinder * g_cyl022;
	Cylinder * g_cyl023;

	Cylinder * g_cyl21;
	Cylinder * g_cyl22;
	Cylinder * g_cyl23;
	Cylinder * g_cyl24;
	Cylinder * g_cyl25;
	Cylinder * g_cyl26;
	Cylinder * g_cyl27;
	Cylinder * g_cyl28;
	Cylinder * g_cyl29;

	Pod * g_pod21;
	Pod * g_pod22;
	Pod * g_pod23;
	Pod * g_pod24;
	Pod * g_pod25;
	Pod * g_pod26;
	Pod * g_pod27;
	Pod * g_pod28;
	Pod * g_pod29;
	

	void draw();
};

