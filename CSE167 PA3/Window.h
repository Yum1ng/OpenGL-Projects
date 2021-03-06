#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Cube.h"
#include "shader.h"
#include "OBJObject.h"
#include "skybox.h"
#include "Geode.h"
#include "Ride.h"
#include "Camera.h"
class Window
{
public:
	static GLint shaderProgram;
	static GLint cubeShader;
	static int width;
	static int height;
//	static bool UseCamera;
	//static double xpos, ypos;
	static glm::mat4 P;
	static glm::mat4 V;
	static void initialize_objects();
	static void clean_up();
	static GLFWwindow* create_window(int width, int height);
	static void resize_callback(GLFWwindow* window, int width, int height);
	static void idle_callback();
	static void display_callback(GLFWwindow*);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static glm::vec3 trackBallMapping(double x_pos, double y_pos);
	//static void loadTexture(const char* filename, int& twidth, int& theight);
	//static unsigned char* loadPPM(const char* filename, int& width, int& height);
};

#endif
