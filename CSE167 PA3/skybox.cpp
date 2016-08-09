#include "Window.h"
#include "skybox.h"
using namespace std;
GLfloat skyboxVertices[] = {
	// Positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f,  1.0f
};

skybox::skybox()
{
	// Setup skybox VAO
	this->toWorld = glm::mat4(1.0f);
	this->toWorld = glm::scale(this->toWorld, glm::vec3(500, 500, 500));
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);

	// Load textures
	//GLuint cubeTexture = loadTexture("textures/container.jpg");
#pragma endregion
	//GLuint textureID;
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	// Cubemap (Skybox)
	unsigned char * image;
	image = loadPPM("S:/cse167/mp_drakeq/miramar_rt.ppm", Window::width, Window::height);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, Window::width, Window::height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	image = loadPPM("S:/cse167/mp_drakeq/miramar_lf.ppm", Window::width, Window::height);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, Window::width, Window::height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	image = loadPPM("S:/cse167/mp_drakeq/miramar_up.ppm", Window::width, Window::height);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, Window::width, Window::height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	image = loadPPM("S:/cse167/mp_drakeq/miramar_dn.ppm", Window::width, Window::height);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, Window::width, Window::height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	image = loadPPM("S:/cse167/mp_drakeq/miramar_bk.ppm", Window::width, Window::height);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, Window::width, Window::height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	image = loadPPM("S:/cse167/mp_drakeq/miramar_ft.ppm", Window::width, Window::height);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, Window::width, Window::height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

}

skybox::~skybox()
{
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);
	//glDeleteBuffers(1, &EBO);
}

void skybox::draw(GLuint cubeShader)
{

	// Calculate combination of the model (toWorld), view (camera inverse), and perspective matrices
	//glDepthMask(GL_FALSE);
	glUseProgram(cubeShader);
	//glDisable(GL_DITHER);
	//cubeShader.Use();
	// We need to calculate this because as of GLSL version 1.40 (OpenGL 3.1, released March 2009), gl_ModelViewProjectionMatrix has been
	// removed from the language. The user is expected to supply this matrix to the shader when using modern OpenGL.
	GLuint MatrixVID = glGetUniformLocation(cubeShader, "view");
	GLuint MatrixPID = glGetUniformLocation(cubeShader, "projection");
//	Window::V = glm::mat4(glm::mat3(camera.GetViewMatrix()));
	GLuint MatrixtoWorldID = glGetUniformLocation(cubeShader, "model");
	glUniformMatrix4fv(MatrixPID, 1, GL_FALSE, &Window::P[0][0]);
	glUniformMatrix4fv(MatrixVID, 1, GL_FALSE, &Window::V[0][0]);
	glUniformMatrix4fv(MatrixtoWorldID, 1, GL_FALSE, &toWorld[0][0]);
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(cubeShader, "skybox"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindTexture(GL_TEXTURE_CUBE_MAP,0);
	glBindVertexArray(0);
	//glDepthMask(GL_TRUE);
	// Clear buffers
	//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

unsigned char* skybox::loadPPM(const char* filename, int& width, int& height)
{
	const int BUFSIZE = 128;
	FILE* fp;
	unsigned int read;
	unsigned char* rawData;
	char buf[3][BUFSIZE];
	char* retval_fgets;
	size_t retval_sscanf;

	if ((fp = fopen(filename, "rb")) == NULL)
	{
		std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
		width = 0;
		height = 0;
		return NULL;
	}

	// Read magic number:
	retval_fgets = fgets(buf[0], BUFSIZE, fp);

	// Read width and height:
	do
	{
		retval_fgets = fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');
	retval_sscanf = sscanf(buf[0], "%s %s", buf[1], buf[2]);
	width = atoi(buf[1]);
	height = atoi(buf[2]);

	// Read maxval:
	do
	{
		retval_fgets = fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');

	// Read image data:
	rawData = new unsigned char[width * height * 3];
	read = fread(rawData, width * height * 3, 1, fp);
	fclose(fp);
	if (read != 1)
	{
		std::cerr << "error parsing ppm file, incomplete data" << std::endl;
		delete[] rawData;
		width = 0;
		height = 0;
		return NULL;
	}

	return rawData;
}

// load image file into texture object
/*void skybox::loadTexture(const char* filename, int& twidth, int& theight)
{
	GLuint texture[1];     // storage for one texture
						   //int twidth, theight;   // texture width/height [pixels]
	unsigned char* tdata;  // texture pixel data

						   // Load image file
	tdata = loadPPM(filename, twidth, theight);
	if (tdata == NULL) return;

	// Create ID for texture
	glGenTextures(1, &texture[0]);

	// Set this texture to be the one we are working with
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	// Generate the texture
	glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);

	// Set bi-linear filtering for both minification and magnification
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	//glBindVertexArray(0);
}

GLuint skybox::loadCubemap(std::vector<const GLchar*> faces)
{
	GLuint textureID;
	glGenTextures(1, &textureID);

	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (GLuint i = 0; i < faces.size(); i++)
	{
		image = loadPPM(faces[i], Window::width, Window::height);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, Window::width, Window::height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		//SOIL_free_image_data(image);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}*/

