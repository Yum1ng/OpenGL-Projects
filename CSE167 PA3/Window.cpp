#include "window.h"

const char* window_title = "GLFW Starter Project";
skybox * skymap;
Cube * cube;
Ride* ride;
glm::vec3 curr_point;
glm::vec3 last_point;
double x_pos, y_pos;
double xpos1, ypos1;
double xpos2, ypos2;
int mod;
int lightmod = 0;
//OBJObject *bunny, *bear, *dragon;
//OBJObject *curr;
skybox * curr;

bool UseCamera;
bool lightControl = false;
// Default camera parameters
glm::vec3 cam_pos(0.0f, 0.0f, 5.0f);		// e  | position of camera
glm::vec3 cam_look_at(0.0f, 0.0f, 0.0f);	// d  | This is where the camera looks at
glm::vec3 cam_up(0.0f, 1.0f, 0.0f);			// up | What orientation "up" is

int Window::width;
int Window::height;
GLint Window::shaderProgram;
GLint Window::cubeShader;
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

#else // Not windows
	shaderProgram = LoadShaders("shader.vert", "shader.frag");
	cubeShader = LoadShaders("cubemap.vert", "cubemap.frag");
#endif
	//geo = new Geode("S:/cse167/CSE167-Starter-Code-3-master/cylinder.obj", shaderProgram);
	skymap = new skybox();
	ride = new Ride(shaderProgram);
	//ride = new Ride(cubeShader);
	//curr = skymap;
	//cube = new Cube();


	// Load the shader program. Similar to the .obj objects, different platforms expect a different directory for files

}

void Window::clean_up()
{
	//delete(cube);
	//delete(curr);
	glDeleteProgram(shaderProgram);
	glDeleteProgram(cubeShader);
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
	//curr->update();
	//ride->root->orbit(1.0f);
	ride->orbit(0.2f);
	if (UseCamera == true) {
		Window::V = ride->cam->newCam();
	}
	else {
		Window::V = glm::lookAt(cam_pos, cam_look_at, cam_up);
	}
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
	ride->draw();
	//glUseProgram(cubeShader);
	// Render the cube
	//cube->draw(shaderProgram);
	//curr->draw(shaderProgram);
	//Below is correct to draw skybox;
	//skymap->draw(cubeShader);
	//glUseProgram(shaderProgram);
	//cube->draw(shaderProgram);
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
		if (key == GLFW_KEY_C) {
			if (UseCamera == false) {
				UseCamera = true;
			}
			else if (UseCamera == true) {
				UseCamera = false;
			}
			std::cout << "in" << std::endl;
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
	/*else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
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
	}*/
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
	/*(if (lightControl == false) {
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
		/*	cout << "now z is : " << curr->pointposition.z << endl;
			cout << "xoffset: " << xoffset << endl;
			cout << "yoffset: " << yoffset << endl;
		}
		else if (lightmod == 3) {
			/*if (curr->camposition.z + yoffset/10 > curr->toWorld[2][3]) {
				curr->camposition.z += yoffset/10;
			}*/
		/*	glm::vec3 tmp = glm::vec3(0.0, 0.0, 0.0) - glm::vec3(curr->camposition.x, curr->camposition.y, curr->camposition.z);
			curr->camposition += tmp*glm::vec3(yoffset / Window::height, yoffset / Window::height, yoffset / Window::height);
			curr->cameradir = -curr->camposition;
			cout << "bug in light mode: "<<lightmod << endl;
			cout << "xoffset: " << xoffset << endl;
			cout << "yoffset: " << yoffset << endl;
		}
	}*/
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

