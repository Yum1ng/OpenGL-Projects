#include "window.h"

const char* window_title = "GLFW Starter Project";
//Cube * cube;
glm::vec3 curr_point;
glm::vec3 last_point;
double x_pos, y_pos;
double xpos1, ypos1;
double xpos2, ypos2;
int mod;
int lightmod = 0;
OBJObject *bunny, *bear, *dragon;
OBJObject * curr;

GLint shaderProgram;
bool lightControl = false;
// Default camera parameters
glm::vec3 cam_pos(0.0f, 0.0f, 20.0f);		// e  | Position of camera
glm::vec3 cam_look_at(0.0f, 0.0f, 0.0f);	// d  | This is where the camera looks at
glm::vec3 cam_up(0.0f, 1.0f, 0.0f);			// up | What orientation "up" is

int Window::width;
int Window::height;

glm::mat4 Window::P;
glm::mat4 Window::V;
using namespace std;;
void Window::initialize_objects()
{
	bunny = new OBJObject("S:/cse167/CSE167-Starter-Code-master/bunny.obj");
	//dragon = new OBJObject("S:/cse167/CSE167-Starter-Code-master/dragon.obj");
	//bear = new OBJObject("S:/cse167/CSE167-Starter-Code-master/bear.obj");
	curr = bunny;

	//cube = new Cube();
	// Load the shader program. Similar to the .obj objects, different platforms expect a different directory for files
#ifdef _WIN32 // Windows (both 32 and 64 bit versions)
	shaderProgram = LoadShaders("../shader.vert", "../shader.frag");
#else // Not windows
	shaderProgram = LoadShaders("shader.vert", "shader.frag");
#endif
}

void Window::clean_up()
{
	//delete(cube);
	//delete(curr);
	glDeleteProgram(shaderProgram);
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
	// Call the update function the cube
	//cube->update();
	curr->update();
}

void Window::display_callback(GLFWwindow* window)
{
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use the shader of programID
	glUseProgram(shaderProgram);
	
	// Render the cube
	//cube->draw(shaderProgram);
	curr->draw(shaderProgram);
	//std::cout << (curr == &bunny) << std::endl;
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
		// Check if escape was pressed
		if (key == GLFW_KEY_Z) {
			curr->movein();
			std::cout << "in" << std::endl;
		}
		else if (key == GLFW_KEY_M) {
			curr->moveout();
			std::cout << "in" << std::endl;
		}
		else if ((glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) || glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) && glfwGetKey(window, GLFW_KEY_S)) {
			curr->scaleup();
			std::cout << "scale up" << std::endl;
		}
		else if (key == GLFW_KEY_S) {
			curr->scaledown();
			std::cout << "in" << std::endl;
		}
		
		else if ((glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) || glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) && glfwGetKey(window, GLFW_KEY_E)) {
			curr->outercut += 0.1;
			std::cout << "blurrier" << std::endl;
		}
		else if (key == GLFW_KEY_E) {
			if ((curr->outercut - 0.1) > curr->innercut) {
				curr->outercut -= 0.1;
				std::cout << "sharper" << std::endl;
			}
		}
		else if (key == GLFW_KEY_S) {
			curr->scaledown();
			std::cout << "scale down" << std::endl;
		}
		else if (key == GLFW_KEY_R) {
			curr->reset();
			std::cout << "scale down" << std::endl;
		}
		else if (key == GLFW_KEY_1) {
			//std::cout << "key 1!" << std::endl;
			curr->lights = { 1.0f, 0.0f, 0.0f};
			lightControl = true;
			lightmod = 1;
			std::cout << "key 1!" << std::endl;
		}
		else if (key == GLFW_KEY_2) {
			curr->lights = { 0.0f, 1.0f, 0.0f };
			lightControl = true;
			lightmod = 2;
			std::cout << "key 2!" << std::endl;
		}
		else if (key == GLFW_KEY_3) {
			curr->lights = { 0.0f, 0.0f, 1.0f };
			lightControl = true;
			lightmod = 3 ;
			std::cout << "key 3!" << std::endl;
		}
		else if (key == GLFW_KEY_0) {
			lightControl = false;
			lightmod = 0;
			std::cout << "key 3!" << std::endl;
		}
		else if (key == GLFW_KEY_F1) {
			curr = bunny;
			curr->pic = 1;
			std::cout << "bunny!" << std::endl;
		}
		else if (key == GLFW_KEY_F2) {
			curr = dragon;
			curr->pic = 2;
			std::cout << "dragon!" << std::endl;
		}
		else if (key == GLFW_KEY_F3) {
			curr = bear;
			curr->pic = 3;
			std::cout << "bear!" << std::endl;
		}
		else if (key == GLFW_KEY_ESCAPE)
		{
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
	}
}

void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (lightControl == false) {
		if (mod == 1) {
			curr_point = trackBallMapping(xpos, ypos);
			cout << "curr_point" << endl;
			cout << "x is : " << curr_point.x << endl;
			cout << "y is : " << curr_point.y << endl;
			cout << "z is : " << curr_point.z << endl;
			cout << "last_point" << endl;
			cout << "x is : " << last_point.x << endl;
			cout << "y is : " << last_point.y << endl;
			cout << "z is : " << last_point.z << endl;
			glm::vec3 direction = curr_point - last_point;
			float velocity = direction.length();
			glm::vec3 rotAxis;
			rotAxis = cross(last_point, curr_point);
			float rot_angle = velocity * 0.5;
			curr->orbit(rotAxis, rot_angle);
			cout << "ROTATE!!!!" << endl;
			cout << "x is : " << rotAxis.x << endl;
			cout << "y is : " << rotAxis.y << endl;
			cout << "z is : " << rotAxis.z << endl;
			cout << rot_angle << endl;
			last_point = curr_point;
			//TODO rotate!!?
		}
		else if (mod == 2) {
			curr->move(xpos - x_pos, ypos - y_pos);
			x_pos = xpos;
			y_pos = ypos;
		}
	}
	else {
		cout << "light control on!" << endl;
		if (lightmod == 1) {
			curr->dirdirection = { -xpos, -ypos, -1 };
			cout << "dirlight direction change!" << endl;
			/*if ((xpos >= Window::width/2) && (ypos >= Window::height/2)) {
				curr->dirdirection = { -xpos, ypos, -1 };
				cout << "dirlight direction change!" << endl;
			}
			else if ((xpos > Window::width/2) && (ypos < Window::height/2)) {
				curr->dirdirection = { -xpos, -ypos, -1 };
				cout << "dirlight direction change!" << endl;
			}
			else if ((xpos > Window::width / 2) && (ypos < Window::height / 2)) {
				curr->dirdirection = { -xpos, -ypos, -1 };
				cout << "dirlight direction change!" << endl;
			}
			else if ((xpos < Window::width / 2) && (ypos > Window::height / 2)) {
				curr->dirdirection = { xpos, ypos, -1 };
				cout << "dirlight direction change!" << endl;
			}
			else if ((xpos < Window::width / 2) && (ypos < Window::height / 2)) {
				curr->dirdirection = { xpos, -ypos, -1 };
				cout << "dirlight direction change!" << endl;
			}*/
		}
		else if (lightmod == 2) {
			glm::vec4 temp = curr->get_world() * glm::vec4(trackBallMapping(xpos, ypos), 1.0);
			curr->pointposition = glm::vec3( temp.x, temp.y, temp.z );

			//curr->pointposition = { xpos, ypos, 0.5 };
			cout << "dirlight direction change!" << endl;
			cout << "x: " << temp.x << endl;
			cout << "y: " << temp.y << endl;
			cout << "z: " << temp.z << endl;
		}
		else if (lightmod == 3) {
			if (mod == 3) {
				if (ypos < y_pos) {
					curr->value += 0.05;
				}
				else {
					curr->value -= 0.05;
				}

				if (curr->value < 0) curr->value = 0;
				y_pos = ypos;
				cout << "nooo" << endl;
			}
			else {
				glm::vec4 temp = curr->get_world() * glm::vec4(trackBallMapping(xpos, ypos), 1.0);
				curr->camposition = glm::vec3(temp.x, temp.y, temp.z*1.5);
				curr->cameradir = -curr->camposition;
			/*	glm::vec3 temp = trackBallMapping(xpos, ypos);
				
				curr->camposition.x = temp.x * 6;
				curr->camposition.y = temp.y * 6;
				curr->camposition.z = temp.z * 20;
				curr->cameradir.x = -temp.x * 6;
				curr->cameradir.y = -temp.y * 6;
				curr->cameradir.z = -temp.z * 6;*/
				cout << "camposition: " << endl;
				cout << curr->camposition.x << endl;
				cout << curr->camposition.y << endl;
				cout << curr->camposition.z << endl;
				cout << "camdirection: " << endl;
				cout << curr->cameradir.x << endl;
				cout << curr->cameradir.y << endl;
				cout << curr->cameradir.z << endl;
			}
			/*else {
				glm::mat4 temp = glm::rotate(glm::mat4(1.0f), 1.0f, Window::trackBallMapping(xpos, ypos));
				glm::vec4 camera = temp * glm::vec4(0.0f, 0.0f, 5.0f, 1.0f);
				curr->camposition = glm::vec3(camera.x, camera.y, camera.z);
				curr->cameradir = -curr->camposition;
				cout << "camposition: " << endl;
				cout << curr->camposition.x << endl;
				cout << curr->camposition.y << endl;
				cout << curr->camposition.z << endl;
				cout << "camdirection: " << endl;
				cout << curr->cameradir.x << endl;
				cout << curr->cameradir.y << endl;
				cout << curr->cameradir.z << endl;
			}*/
			//curr->camposition = { xpos/50, ypos/50, 10.0f };
			/*cout << "dirlight direction change!" << endl;
			cout << xpos << endl;
			cout << ypos << endl;*/
		}

	}
	/*cout << "here" << endl;
	cout << xpos << endl;
	cout << ypos << endl;*/
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		glfwGetCursorPos(window, &x_pos, &y_pos);
		last_point = trackBallMapping(x_pos, y_pos);
		mod = 1;
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		glfwGetCursorPos(window, &xpos2, &ypos2);
		mod = 0;
		cout << xpos2 << endl;
		cout << ypos2 << endl;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		//glfwGetCursorPos(window, &xpos1, &ypos1);
		glfwGetCursorPos(window, &x_pos, &y_pos);
		if ((lightControl == true) && (lightmod == 3)) {
			mod = 3;
		}
		else {
			mod = 2;
		}
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
		glfwGetCursorPos(window, &xpos2, &ypos2);
		mod = 0;
	}
}
void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	if (lightControl == false) {
		cout << "lightmode off " << endl;
		curr->scroll(yoffset);
		cout << "xoffset: " << xoffset << endl;
		cout << "yoffset: " << yoffset << endl;
	}
	else {
		cout << "lightmode on " << endl;
		if (lightmod == 2) {
			//glm::vec3 tep = glm::vec3(0.7, 0.2, 2.0) - trackBallMapping(curr->x)
			if (curr->pointposition.z + yoffset > curr->toWorld[2][3]) {
				glm::vec3 tmp = glm::vec3(0.0, 0.0, 0.0) - glm::vec3(curr->pointposition.x, curr->pointposition.y, curr->pointposition.z);
				curr->pointposition += tmp*glm::vec3(yoffset / Window::height, yoffset / Window::height, yoffset / Window::height);
			}//curr->pointposition += tmp*glm::vec3(0.01, 0.01, 0.01);
			/*if (curr->pointposition.z + yoffset > curr->toWorld[2][3]) {
				curr->pointposition.z += yoffset;
			}*/
			cout << "now z is : " << curr->pointposition.z << endl;
			cout << "xoffset: " << xoffset << endl;
			cout << "yoffset: " << yoffset << endl;
		}
		else if (lightmod == 3) {
			/*if (curr->camposition.z + yoffset/10 > curr->toWorld[2][3]) {
				curr->camposition.z += yoffset/10;
			}*/
			glm::vec3 tmp = glm::vec3(0.0, 0.0, 0.0) - glm::vec3(curr->camposition.x, curr->camposition.y, curr->camposition.z);
			curr->camposition += tmp*glm::vec3(yoffset / Window::height, yoffset / Window::height, yoffset / Window::height);
			curr->cameradir = -curr->camposition;
			cout << "bug in light mode: "<<lightmod << endl;
			cout << "xoffset: " << xoffset << endl;
			cout << "yoffset: " << yoffset << endl;
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
	d = v.length();
	d = (d<1.0) ? d : 1.0;
	v.z = sqrtf(1.001 - d*d);
	v = glm::normalize(v); // Still need to normalize, since we only capped d, not v.
	return v;
}

