#include "window.h"

const char* window_title = "GLFW Starter Project";
skybox * skymap;
Cube * cube;
Track * track;
Pod * pod;
glm::vec3 curr_point;
glm::vec3 last_point;
double x_pos, y_pos;
double xpos1, ypos1;
double xpos2, ypos2;
int mod;
int lightmod = 0;
int pointmod = 0;
int id = 0;
//OBJObject *bunny, *bear, *dragon;
OBJObject * podobj;
OBJObject * obj;
Curve * curve;
skybox * curr;
Tree * tree;
bool UseCamera;
bool lightControl = false;
// Default camera parameters
glm::vec3 Window::cam_pos(0.0f, 0.0f, 5.0f);		// e  | position of camera
glm::vec3 cam_look_at(0.0f, 0.0f, 0.0f);	// d  | This is where the camera looks at
glm::vec3 cam_up(0.0f, 1.0f, 0.0f);			// up | What orientation "up" is

int Window::width;
int Window::height;
GLint Window::shaderProgram;
GLint Window::cubeShader;
GLint Window::selectionShader;
GLint Window::lineShader;
GLint Window::environmentShader;
glm::mat4 Window::P;
glm::mat4 Window::V;
using namespace std;
//Camera * cam = new Camera();
void Window::initialize_objects()
{
	//bunny = new OBJObject("S:/cse167/CSE167-Starter-Code-master/bunny.obj");
	//dragon = new OBJObject("S:/cse167/CSE167-Starter-Code-master/dragon.obj");
	//bear = new OBJObject("S:/cse167/CSE167-Starter-Code-master/bear.obj");
	//curr = bunny;
	
#ifdef _WIN32 // Windows (both 32 and 64 bit versions)
	Window::shaderProgram = LoadShaders("../shader.vert", "../shader.frag");
	Window::cubeShader = LoadShaders("../cubemap.vert", "../cubemap.frag");
	Window::selectionShader = LoadShaders("../selection.vert", "../selection.frag");
	Window::lineShader = LoadShaders("../shader.vert", "../lineshader.frag");
	Window::environmentShader = LoadShaders("../environment.vert", "../environment.frag");
#else // Not windows
	shaderProgram = LoadShaders("shader.vert", "shader.frag");
	cubeShader = LoadShaders("cubemap.vert", "cubemap.frag");
	selectionShader = LoadShaders("../selection.vert", "../selection.frag");
#endif
	//geo = new Geode("S:/cse167/CSE167-Starter-Code-3-master/cylinder.obj", shaderProgram);
	skymap = new skybox();
	//curve = new Curve();
	track = new Track();
	podobj = new OBJObject("S:/cse167/CSE167-Starter-Code-3-master/pod.obj");
	podobj->scale(glm::vec3(0.5, 0.5, 1));
	obj = new OBJObject("S:/cse167/CSE167-Starter-Code-3-master/cylinder.obj");
//	obj = new OBJObject("S:/cse167/Mark42.obj");
	obj->scale(glm::vec3(0.5, 0.5, 0.2));
//	tree = new Tree(shaderProgram);
//	pod = new Pod(podobj, environmentShader);
	//ride = new Ride(shaderProgram);


	// Load the shader program. Similar to the .obj objects, different platforms expect a different directory for files

}

void Window::clean_up()
{
	//delete(cube);
	//delete(curr);
	glDeleteProgram(shaderProgram);
	glDeleteProgram(cubeShader);
	glDeleteProgram(selectionShader);
	glDeleteProgram(lineShader);
	glDeleteProgram(environmentShader);
}

GLFWwindow* Window::create_window(int width, int height)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);

	// Check if the window could not be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window
	glfwMakeContextCurrent(window);

	// Set swap interval to 1
	glfwSwapInterval(1);

	// Get the width and height of the framebuffer to properly resize the window
	glfwGetFramebufferSize(window, &width, &height);
	// Call the resize callback to make sure things get drawn immediately
	Window::resize_callback(window, width, height);

	return window;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
	Window::width = width;
	Window::height = height;
	// Set the viewport size
	glViewport(0, 0, width, height);

	if (height > 0)
	{
		P = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 1000.0f);
		V = glm::lookAt(cam_pos, cam_look_at, cam_up);
	}
}

void Window::idle_callback()
{
	Window::V = glm::lookAt(cam_pos, cam_look_at, cam_up);
	podobj->move();
	// Call the update function the cube
	//skymap->update();
	//curr->update();
	//ride->root->orbit(1.0f);
	/*ride->orbit(0.2f);
	if (UseCamera == true) {
		Window::V = ride->cam->newCam();
	}

	else {
		Window::V = glm::lookAt(cam_pos, cam_look_at, cam_up);
	}*/
//	Window::V = ride->cam->newCam();
	//ride->root->update(glm::rotate(glm::mat4(1.0f), 0.01f / 180.0f * glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f)));
}

void Window::display_callback(GLFWwindow* window)
{
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use the shader of programID
	//glUseProgram(shaderProgram);
	skymap->draw(cubeShader);
	//curve->draw(shaderProgram);
	track->draw(shaderProgram);
	track->drawpoint(selectionShader);
	track->drawLine(lineShader);
	
//	podobj->toWorld = glm::mat4(1.0f);
//	podobj->toWorld = podobj -> toWorld * glm::scale(glm::mat4(1.0f), glm::vec3(0.2, 0.2, 0.2));
//	podobj->toWorld = glm::translate(glm::mat4(), glm::vec3(0.0f, 2.0f, 0.0f))*podobj->toWorld;
	
	podobj->draw(environmentShader);
//	obj->draw(environmentShader);
	
//	pod->scale(glm::vec3(0.1, 0.1, 0.1));
//	pod->draw();
	//ride->draw();
	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();
	// Swap buffers
	glfwSwapBuffers(window);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check for a key press
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_C) {
			if (UseCamera == false) {
				UseCamera = true;
			}
			else if (UseCamera == true) {
				UseCamera = false;
			}
			std::cout << "in" << std::endl;
		}
		else if (key == GLFW_KEY_R) {
			podobj->reset();
		}
		if (key == GLFW_KEY_ESCAPE)
		{
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
}

void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	
	if (mod == 1) {
		cout << "HERE!!!" << endl;

		curr_point = trackBallMapping(xpos, ypos);
		glm::vec3 direction = curr_point - last_point;
		float velocity = glm::length(direction);
		glm::vec3 rotAxis = cross(last_point, curr_point);
		float rot_angle = velocity * 3.5;
		
		glm::mat4 rotation = glm::mat4(1.0f);
		rotation = glm::rotate(rotation, rot_angle, rotAxis);
		//glm::mat4 rotation = glm::rotate(glm::mat4(), rot_angle / 180.0f * glm::pi<float>(), rotAxis);
		glm::vec4 t1 = rotation * glm::vec4(cam_pos, 1.0f);
		glm::vec4 t2 = rotation * glm::vec4(cam_up, 0.0f);
		cam_pos = glm::vec3(t1.x, t1.y, t1.z);
		cam_up = glm::vec3(t2.x, t2.y, t2.z);
		V = glm::lookAt(cam_pos, cam_look_at, cam_up);
		//printf("%d\n", (last_point == curr_point));
		last_point = curr_point;
	}
	else {
		glm::vec3 movevecz = glm::normalize(cam_pos - cam_look_at);
		glm::vec3 movevecx = glm::cross(cam_up, movevecz);
		glm::vec3 movevecy = glm::cross(movevecz, movevecx);
		if (pointmod == 1) {
			glm::vec3 temp;
			cout << "reach pointmod 1" << endl;



			temp = track->points[id - 1]->move((xpos - x_pos) / 220.0f, -(ypos - y_pos) / 220.0f, movevecx, movevecy);
			track->update((id - 1) / 3, 1, temp);
			if (id == 1) {
				track->update(7, 4, temp);
			}
			else {
				track->update((id - 1) / 3 - 1, 4, temp);
			}
			//move the other point into opposite way
			if (id != 1) {
				temp = track->points[id - 1 - 1]->move((xpos - x_pos) / 220.0f, -(ypos - y_pos) / 220.0f, movevecx, movevecy);
				track->update((id - 1 - 1) / 3, 3, temp);
				temp = track->points[id - 1 + 1]->move((xpos - x_pos) / 220.0f, -(ypos - y_pos) / 220.0f, movevecx, movevecy);
				track->update((id - 1 + 1) / 3, 2, temp);
			}
			else {
				temp = track->points[23]->move((xpos - x_pos) / 220.0f, -(ypos - y_pos) / 220.0f, movevecx, movevecy);
				track->update(23 / 3, 3, temp);
				temp = track->points[1]->move((xpos - x_pos) / 220.0f, -(ypos - y_pos) / 220.0f, movevecx, movevecy);
				track->update(0 / 3, 2, temp);
			}
		}
		else if (pointmod == 2) {
			glm::vec3 temp;
			cout << "reach pointmod 2" << endl;
			temp = track->points[id - 1]->move((xpos - x_pos) / 220.0f, -(ypos - y_pos) / 220.0f, movevecx, movevecy);
			track->update((id - 1) / 3, 2, temp);
			//move the other point into opposite way
			if (id != 2) {
				temp = track->points[id - 1 - 2]->move((x_pos - xpos) / 220.0f, -(y_pos - ypos) / 220.0f, movevecx, movevecy);
				track->update((id - 1 - 2) / 3, 3, temp);
			}
			else {
				temp = track->points[23]->move((x_pos - xpos) / 220.0f, -(y_pos - ypos) / 220.0f, movevecx, movevecy);
				track->update(23 / 3, 3, temp);
			}
		}
		else if (pointmod == 3) {
			cout << "reach pointmod 3" << endl;
			glm::vec3 temp;
			temp = track->points[id - 1]->move((xpos - x_pos) / 220.0f, -(ypos - y_pos) / 220.0f, movevecx, movevecy);
			track->update((id - 1) / 3, 3, temp);
			//move the other point into opposite way
			if (id != 24) {
				temp = track->points[id - 1 + 2]->move((x_pos - xpos) / 220.0f, -(y_pos - ypos) / 220.0f, movevecx, movevecy);
				track->update((id - 1 + 2) / 3, 2, temp);
			}
			else {
				//			track->points[1]->move((x_pos - xpos) / 220.0f, (y_pos - ypos) / 220.0f);
				temp = track->points[1]->move((x_pos - xpos) / 220.0f, -(y_pos - ypos) / 220.0f, movevecx, movevecy);
				track->update((1) / 3, 2, temp);
			}
		}
	}
	x_pos = xpos;
	y_pos = ypos;
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		glfwGetCursorPos(window, &x_pos, &y_pos);
		last_point = trackBallMapping(x_pos, y_pos);
		

		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		track->drawpoint(selectionShader);
		unsigned char pix[4];
		glReadPixels(x_pos, viewport[3] - y_pos, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pix);
		printf("pix[0]: %d\n", pix[0]);
		id = pix[0];
		if (pix[0] >= 1 && pix[0] <= 24) {
			if (pix[0] % 3 == 1) pointmod = 1;
			if (pix[0] % 3 == 2) pointmod = 2;
			if (pix[0] % 3 == 0) pointmod = 3;
		}
		else {
			mod = 1;
		}
		cout << "pointmod: " << pointmod << endl;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		glfwGetCursorPos(window, &xpos2, &ypos2);
		mod = 0;
		pointmod = 0;
	}
}
void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	if (UseCamera == false) {
		if ((cam_pos[2] >= 0.2) && (cam_pos[2] <= 120)) {
			if (yoffset > 0) {
				cam_pos *= 1.1;
				if (cam_pos[2] >= 120) cam_pos[2] = 120;
			}
			else if (yoffset < 0) {
				cam_pos *= 0.9;
				if (cam_pos[2] <= 0.2) cam_pos[2] = 0.2;
			}
			cout << "camposx: " << cam_pos[0] << endl;
			cout << "camposy: " << cam_pos[1] << endl;
			cout << "camposz: " << cam_pos[2] << endl;
			V = glm::lookAt(cam_pos, cam_look_at, cam_up);
		}
	}
}

glm::vec3 Window::trackBallMapping(double x_pos, double y_pos)
{
	glm::vec3 v;
	float d;
	v.x = (2.0*x_pos - Window::width) / Window::width;
	v.y = (Window::height - 2.0*y_pos) / Window::height;
	v.z = 0.0;
	d = glm::length(v);
	d = (d<1.0) ? d : 1.0;
	v.z = sqrtf(1.001 - d*d);
	v = glm::normalize(v); // Still need to normalize, since we only capped d, not v.
	return v;
}

