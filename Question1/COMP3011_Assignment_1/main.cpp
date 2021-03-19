#include <iostream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp> 

GLFWwindow* window = NULL;
const char* WINDOW_TITLE = "GRA_Tutorial";
const GLint WINDOW_WIDTH = 1200;
const GLint WINDOW_HEIGHT = 800;
int change = 0;

bool initOpenGL();
void drawSolidCube1(float r);
void drawTriangle(float r);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

//camera 
bool wKey, sKey, aKey, dKey, iKey, jKey, kKey, lKey, eKey;
bool isPlayerOne = true;
static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}
int main()
{
	std::cout << "GRA_Tutorial!" << std::endl;

	if (!initOpenGL())
	{
		std::cerr << "GLFW initialisation failed." << std::endl;
		return -1;
	}

	/* Enable depth testing */
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	/* Enable back-face culling */
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	/* Enable transparency blending */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Choose a colour to clear the screen (RGBA range [0, 1]) */
	glClearColor(0.4f, 0.5f, 0.6f, 1.0f);

	//camera 1
	glfwSetCursorPos(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	float sensitivity = 0.01f; // speed of the camera moving
	float cameraSpeed = 0.001f;
	/* Vectors containing eye coordinates */
	glm::vec3 pos1 = glm::vec3(-1.f, 0.f, -3.f);	// Position in World Space
	glm::vec3 pos2 = glm::vec3(0.0f, 0.0f, 3.0f);
	/* The vector along which the camera are looking */
	glm::vec3 vd1 = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 vd2 = glm::vec3(0.0f, 0.0f, 2.0f);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Projection */
		glViewport(0, 0, 0.5 * WINDOW_WIDTH, WINDOW_HEIGHT);
		glMatrixMode(GL_PROJECTION);    // switch from model/view to projection mode    
		glLoadIdentity();               // reset matrix

		/* Perspective projection */
		float aspectRatio = static_cast<GLdouble>(WINDOW_WIDTH) / static_cast<GLdouble>(WINDOW_HEIGHT);
		float znear = 0.1f;
		float zfar = 1000.f;
		float fovyInDegrees = 60.f;

		/* Perspective projection with glm */
		glm::mat4 proj1 = glm::perspective(glm::radians(fovyInDegrees), aspectRatio, znear, zfar);
		float* matProjectionArray1 = glm::value_ptr(proj1);
		glLoadMatrixf(matProjectionArray1);

		/* Set modelview matrix as the current matrix */
		glMatrixMode(GL_MODELVIEW);
		/* Reset the current matrix */
		glLoadIdentity();
		/* Camera - 1 */
		glm::vec3 eye1 = pos1;
		glm::vec3 cen1 = pos1 + vd1;
		glm::vec3 cameraDirection1 = glm::normalize(cen1 - eye1);
		glm::vec3 up1 = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight1 = glm::normalize(glm::cross(up1, cameraDirection1));
		glm::vec3 cameraUp1 = glm::cross(cameraDirection1, cameraRight1);
		glm::mat4 view1 = glm::mat4(
			cameraRight1[0], cameraUp1[0], -cameraDirection1[0], 0.0f,
			cameraRight1[1], cameraUp1[1], -cameraDirection1[1], 0.0f,
			cameraRight1[2], cameraUp1[2], -cameraDirection1[2], 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		view1 = glm::translate(view1, -eye1);
		float* viewArray1 = glm::value_ptr(view1);
		glLoadMatrixf(viewArray1);

		double xpos1, ypos1;

		if (isPlayerOne == true) {

			glfwGetCursorPos(window, &xpos1, &ypos1);

			vd1 = vd1 + cameraRight1 * (float)((xpos1 - mouseX) * sensitivity);
			vd1 = vd1 + cameraUp1 * (float)(-(ypos1 - mouseY) * sensitivity);

			mouseX = xpos1;
			mouseY = ypos1;
		}
		if (wKey)
		{
			pos1 = pos1 + cameraDirection1 * cameraSpeed;
		}
		if (sKey)
		{
			pos1 = pos1 + cameraDirection1 * -cameraSpeed;
		}
		if (aKey)
		{
			pos1 = pos1 + cameraRight1 * -cameraSpeed;
		}
		if (dKey)
		{
			pos1 = pos1 + cameraRight1 * cameraSpeed;
		}
		/* Draw solid triangle */
		glPushMatrix(); // save transformation state
		drawTriangle(0.2f);
		glPopMatrix();	// restore transformation state

		glPushMatrix(); // save transformation state
		glTranslatef(pos1[0], pos1[1], pos1[2]);
		glColor3f(0.0f, 0.0f, 1.0f);
		drawSolidCube1(0.2f);
		glPopMatrix();	// restore transformation state

		glPushMatrix(); // save transformation state
		glTranslatef(pos2[0], pos2[1], pos2[2]);
		glColor3f(0.0f, 1.0f, 0.0f);
		drawSolidCube1(0.2f);
		glPopMatrix();	// restore transformation state

		/* Projection */
		glViewport(0.5 * WINDOW_WIDTH, 0, 0.9 * WINDOW_WIDTH, WINDOW_HEIGHT);
		glMatrixMode(GL_PROJECTION);    // switch from model/view to projection mode    
		glLoadIdentity();               // reset matrix

		/* Orthographic projection with glm */
		glm::mat4 proj2 = glm::ortho(-3.f, 3.f, -3.f, 3.f, -50.f, 100.f);
		float* matProjectionArray2 = glm::value_ptr(proj2);
		glLoadMatrixf(matProjectionArray2);
		/* Set modelview matrix as the current matrix */
		glMatrixMode(GL_MODELVIEW);
		/* Reset the current matrix */
		glLoadIdentity();
		/* Camera - 2 */
		glm::vec3 eye2 = pos2;
		glm::vec3 cen2 = pos2 + vd2;
		glm::vec3 cameraDirection2 = glm::normalize(cen2 - eye2);
		glm::vec3 up2 = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight2 = glm::normalize(glm::cross(up2, cameraDirection2));
		glm::vec3 cameraUp2 = glm::cross(cameraDirection2, cameraRight2);
		glm::mat4 view2 = glm::mat4(
			cameraRight2[0], cameraUp2[0], -cameraDirection2[0], 0.0f,
			cameraRight2[1], cameraUp2[1], -cameraDirection2[1], 0.0f,
			cameraRight2[2], cameraUp2[2], -cameraDirection2[2], 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		view2 = glm::translate(view2, -eye2);
		float* viewArray2 = glm::value_ptr(view2);
		glLoadMatrixf(viewArray2);

		double xpos2, ypos2;
		if (isPlayerOne == false) {
			glfwGetCursorPos(window, &xpos2, &ypos2);

			vd2 = vd2 + cameraRight2 * (float)((xpos2 - mouseX) * sensitivity);
			vd2 = vd2 + cameraUp2 * (float)(-(ypos2 - mouseY) * sensitivity);

			mouseX = xpos2;
			mouseY = ypos2;
		}
		if (iKey)
		{
			pos2 = pos2 + cameraDirection2 * cameraSpeed;
		}
		if (kKey)
		{
			pos2 = pos2 + cameraDirection2 * -cameraSpeed;
		}
		if (jKey)
		{
			pos2 = pos2 + cameraRight2 * -cameraSpeed;
		}
		if (lKey)
		{
			pos2 = pos2 + cameraRight2 * cameraSpeed;
		}
		/* Draw solid triangle */
		glPushMatrix(); // save transformation state
		glTranslatef(-2.0f, 0.0f, 0.0f);
		drawTriangle(0.2f);
		glPopMatrix();	// restore transformation state

		glPushMatrix(); // save transformation state
		glTranslatef(pos1[0], pos1[1], pos1[2]);
		glColor3f(0.0f, 0.0f, 1.0f);
		drawSolidCube1(0.2f);
		glPopMatrix();	// restore transformation state

		glPushMatrix();	// save transformation state
		glTranslatef(pos2[0], pos2[1], pos2[2]); // Apply translation
		glColor4f(0.0f, 1.0f, 0.0f, 1.f);
		drawSolidCube1(0.2f);	// draw a cube
		glPopMatrix();	// restore transformation state

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
bool initOpenGL()
{
	/* Initialize the GLFW library */
	if (!glfwInit()) {
		std::cout << "GLFW initialisation failed." << std::endl;
		return false;
	}
	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window)
	{
		std::cout << "GLFW failed to create window." << std::endl;
		glfwTerminate();
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	/* Initialize the GLEW library */
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		/* Problem: glewInit failed, something is seriously wrong */
		std::cout << "GLEW initialisation failed: " << glewGetErrorString(err) << std::endl;
		return false;
	}
	std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

	return true;
}

void drawSolidCube1(float r)
{
	glBegin(GL_QUADS);
	// Back face (z = r)
	glVertex3f(r, r, r);
	glVertex3f(r, -r, r);
	glVertex3f(-r, -r, r);
	glVertex3f(-r, r, r);

	// Near face (z = -r)
	glVertex3f(r, r, -r);
	glVertex3f(-r, r, -r);
	glVertex3f(-r, -r, -r);
	glVertex3f(r, -r, -r);

	// Right face (x = r)
	glVertex3f(r, r, r);
	glVertex3f(r, r, -r);
	glVertex3f(r, -r, -r);
	glVertex3f(r, -r, r);

	// Left face (x = -r)
	glVertex3f(-r, r, r);
	glVertex3f(-r, -r, r);
	glVertex3f(-r, -r, -r);
	glVertex3f(-r, r, -r);

	// Top face (y = r)
	glVertex3f(r, r, r);
	glVertex3f(-r, r, r);
	glVertex3f(-r, r, -r);
	glVertex3f(r, r, -r);

	// Bottom face (y = -r)
	glVertex3f(r, -r, r);
	glVertex3f(r, -r, -r);
	glVertex3f(-r, -r, -r);
	glVertex3f(-r, -r, r);

	glEnd();
}
void drawTriangle(float r) {
	glBegin(GL_TRIANGLES);
	//Draw vertex coordinates and colors
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, r, 0.0f);
	glVertex3f(-r, -r, r);
	glVertex3f(r, -r, r);

	glVertex3f(0.0f, r, 0.0f);
	glVertex3f(r, -r, r);
	glVertex3f(r, -r, -r);

	glVertex3f(0.0f, r, 0.0f);
	glVertex3f(r, -r, -r);
	glVertex3f(-r, -r, -r);

	glVertex3f(0.0f, r, 0.0f);
	glVertex3f(-r, -r, -r);
	glVertex3f(-r, -r, r);

	glEnd();
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		isPlayerOne = true;
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		isPlayerOne = false;
	}
	if (isPlayerOne == true)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		if (key == GLFW_KEY_W && action == GLFW_PRESS)
		{
			wKey = true;
		}
		if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		{
			wKey = false;
		}
		if (key == GLFW_KEY_S && action == GLFW_PRESS)
		{
			sKey = true;
		}
		if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		{
			sKey = false;
		}
		if (key == GLFW_KEY_A && action == GLFW_PRESS)
		{
			aKey = true;
		}
		if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		{
			aKey = false;
		}
		if (key == GLFW_KEY_D && action == GLFW_PRESS)
		{
			dKey = true;
		}
		if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		{
			dKey = false;
		}
	}

	else
	{

		if (key == GLFW_KEY_W && action == GLFW_PRESS)
		{
			iKey = true;
		}
		if (key == GLFW_KEY_W && action == GLFW_RELEASE)
		{
			iKey = false;
		}
		if (key == GLFW_KEY_S && action == GLFW_PRESS)
		{
			kKey = true;
		}
		if (key == GLFW_KEY_S && action == GLFW_RELEASE)
		{
			kKey = false;
		}
		if (key == GLFW_KEY_A && action == GLFW_PRESS)
		{
			jKey = true;
		}
		if (key == GLFW_KEY_A && action == GLFW_RELEASE)
		{
			jKey = false;
		}
		if (key == GLFW_KEY_D && action == GLFW_PRESS)
		{
			lKey = true;
		}
		if (key == GLFW_KEY_D && action == GLFW_RELEASE)
		{
			lKey = false;
		}
	}
}