#include <iostream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp> 

GLFWwindow* window = NULL;
const char* WINDOW_TITLE = "Question 3";
const GLint WINDOW_WIDTH = 800;
const GLint WINDOW_HEIGHT = 600;

bool initOpenGL();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void drawSolidPlane(float r);

//camera
bool wKey, sKey, aKey, dKey;


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
	glDepthFunc(GL_LEQUAL);

	/* Enable back-face culling */
	glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	/* Enable transparency blending */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Enable 2-D texturing
	glEnable(GL_TEXTURE_2D);

	// Enable blending colour information with texture information
	//glEnable(GL_COLOR_MATERIAL);
	//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	// enable scene lighting (required to enable a light source)
	// (x, y, z, 0.0) -> directional lighting
	// (x, y, z, 1.0) -> positional lighting
	glEnable(GL_LIGHTING);

	// set the global ambient light model
	GLfloat global_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

	// Turn off 2 sided lighting
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

	// Enable smooth shading from lighting
	glShadeModel(GL_SMOOTH);
	//glShadeModel(GL_FLAT);

	// Enable automatic normalisation of normal vectors
	glEnable(GL_NORMALIZE);

	/* Choose a colour to clear the screen (RGBA range [0, 1]) */
	glClearColor(0.4f, 0.5f, 0.6f, 1.0f);

	//camera setup
	glfwSetCursorPos(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	float sensitivity = 0.01f; // speed of the camera moving
	float cameraSpeed = 0.01f;
	/* Vectors containing eye coordinates */
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, -4.0f);
	/* The vector along which the camera are looking */
	glm::vec3 vd = glm::vec3(0.0f, 0.0f, 1.0f);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	/* Lighting */
	// Light setup
	// LIGHT0 is a directional light to present as global light (like a sun)
	// Set lighting effect colours and positional parameter
	float ambient_0[] = { 0.2f, 0.2f, 0.2f, 1.0f };      // ambient light (20% white)
	float diffuse_0[] = { 0.5f, 0.5f, 0.5f, 1.0f };      // diffuse light (50% white)
	float specular_0[] = { 1.0f, 1.0f, 1.0f, 1.0f };      // specular light (100% white)

	// Attach properties to single light source (GL_LIGHT0)
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_0);      // set ambient parameter of light source
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_0);      // set diffuse parameter of light source
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular_0);    // set specular parameter of light source

	// Enable this lighting effects
	glEnable(GL_LIGHT0);    // enable light source with attached parameters (GL_LIGHT0)

	// LIGHT1 is a positional light follow the camera as a flashlight
	float ambient_1[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	float diffuse_1[] = { 1.0f, 0.0f, 0.f, 1.0f };
	float specular_1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular_1);
	glEnable(GL_LIGHT1);

	// For spot light
	GLfloat spot_dir_1[] = { 0.f, 0.f, -1.f };
	GLfloat spot_cutoff_1 = 45.0f;
	GLfloat spot_exponent_1 = 30.f;
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_dir_1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spot_cutoff_1);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spot_exponent_1);

	/*
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.35);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.44);
	*/

	// LIGHT2 is a positional light follow the camera as a flashlight
	float ambient_2[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	float diffuse_2[] = { 0.0f, 0.0f, 1.f, 1.0f };
	float specular_2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient_2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse_2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular_2);
	glEnable(GL_LIGHT2);

	// For spot light
	GLfloat spot_dir_2[] = { 0.f, 0.f, -1.f };
	GLfloat spot_cutoff_2 = 45.0f;
	GLfloat spot_exponent_2 = 30.f;
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_dir_2);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spot_cutoff_2);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spot_exponent_2);

	

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Projection */
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		glMatrixMode(GL_PROJECTION);    // switch from model/view to projection mode    
		glLoadIdentity();               // reset matrix

		float aspectRatio = static_cast<GLdouble>(WINDOW_WIDTH) / static_cast<GLdouble>(WINDOW_HEIGHT);
		//gluPerspective(60.0, aspect, 1.0, 1000.0);
		float znear = 0.1f;
		float zfar = 1000.f;
		float fovyInDegrees = 60.f;

		glm::mat4 proj = glm::perspective(glm::radians(fovyInDegrees), aspectRatio, znear, zfar);

		glLoadMatrixf(glm::value_ptr(proj));


		/* Set modelview matrix as the current matrix */
		glMatrixMode(GL_MODELVIEW);
		/* Reset the current matrix */
		glLoadIdentity();


		/* Camera */
		glm::vec3 eye = pos;
		glm::vec3 cen = pos + vd;
		glm::vec3 cameraDirection = glm::normalize(cen - eye);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
		glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
		glm::mat4 view = glm::mat4(
			cameraRight[0], cameraUp[0], -cameraDirection[0], 0.0f,
			cameraRight[1], cameraUp[1], -cameraDirection[1], 0.0f,
			cameraRight[2], cameraUp[2], -cameraDirection[2], 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
		view = glm::translate(view, -eye);

		glLoadMatrixf(glm::value_ptr(view));

		// Camera mouse and keyboard control
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		vd = vd + cameraRight * (float)((xpos - mouseX) * sensitivity);
		vd = vd + cameraUp * (float)(-(ypos - mouseY) * sensitivity);

		mouseX = xpos;
		mouseY = ypos;

		// Key input
		if (wKey)
		{
			pos = pos + cameraDirection * cameraSpeed;
		}

		if (sKey)
		{
			pos = pos + cameraDirection * -cameraSpeed;
		}

		if (aKey)
		{
			pos = pos + cameraRight * -cameraSpeed;
		}

		if (dKey)
		{
			pos = pos + cameraRight * cameraSpeed;
		}

		//LIGHT0 position
		float position_0[] = { 0.f, 1.f, 0.f, 0.f };      // directional light (w = 0)
		glLightfv(GL_LIGHT0, GL_POSITION, position_0);    // set direction vector of light source

		
		//Re position LIGHT1
		float position_1[] = { -0.6f, -0.2f, -3.f, 1.f };      // positional light (w = 1)
		glLightfv(GL_LIGHT1, GL_POSITION, position_1);

		//Re position LIGHT2 
		float position_2[] = { 0.6f, -0.2f, -3.f, 1.f };      // positional light (w = 1)
		glLightfv(GL_LIGHT2, GL_POSITION, position_2);

		/* Draw solid cube */
		float cubeSize = 0.5f;
		glPushMatrix(); // save transformation state

		
		std::string sequence = "aaaaaaaawwwwwlllsjjjslllsjjjslllsjjjslllsjjjslllsjjjslll";

		
		for (unsigned int i = 0; i < sequence.size(); i++)
		{
			switch (sequence[i]) { // check current char command
			case 'f': // draw cube
				drawSolidPlane(0.1f);
				break;
			case 'w': // move up
				glTranslatef(0.0f, 0.2f, 0.0f);
				break;
			case 'a': // move up
				glTranslatef(-0.2f, 0.0f, 0.0f);
				break;
			case 'd': // move up
				glTranslatef(0.2f, 0.0f, 0.0f);
				break;
			case 's': // move down
				glTranslatef(0.0f, -0.2f, 0.0f);
				break;
			case 'j': // move left
				drawSolidPlane(0.1f);
				glTranslatef(-0.2f, 0.0f, 0.0f);
				drawSolidPlane(0.1f);
				glTranslatef(-0.2f, 0.0f, 0.0f);
				drawSolidPlane(0.1f);
				glTranslatef(-0.2f, 0.0f, 0.0f);
				drawSolidPlane(0.1f);
				glTranslatef(-0.2f, 0.0f, 0.0f);
				drawSolidPlane(0.1f);
				glTranslatef(-0.2f, 0.0f, 0.0f);
				drawSolidPlane(0.1f);
				break;
			case 'l': // move right
				drawSolidPlane(0.1f);
				glTranslatef(0.2f, 0.0f, 0.0f);
				drawSolidPlane(0.1f);
				glTranslatef(0.2f, 0.0f, 0.0f);
				drawSolidPlane(0.1f);
				glTranslatef(0.2f, 0.0f, 0.0f);
				drawSolidPlane(0.1f);
				glTranslatef(0.2f, 0.0f, 0.0f);
				drawSolidPlane(0.1f);
				glTranslatef(0.2f, 0.0f, 0.0f);
				drawSolidPlane(0.1f);
				break;
			}
		}
		

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
	/* For macOS uncomment the following line */
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		std::cout << "Esc key is pressed." << std::endl;
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

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		glLoadIdentity();
	}
}

void drawSolidPlane(float r)
{
	
	// Material properties
	glPushAttrib(GL_ALL_ATTRIB_BITS); // save current style attributes (inc. material properties)

	float mat_ambient[] = { 0.25f, 0.25f, 0.25f, 1.f };	// ambient colour
	float mat_diffuse[] = { 0.50f, 0.50f, 0.50f, 1.f };	// colour reflected by diffuse light
	float mat_specular[] = { 0.f, 0.f, 0.f, 1.f };		// specular colour
	float mat_shininess[] = { 0.0f }; // [0, 128]
	float mat_emission[] = { 0.f, 0.f, 0.f, 1.f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);	// set colour for ambient reflectance
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);	// set colour for diffuse reflectance
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);	// set colour for specular reflectance
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	

	glBegin(GL_TRIANGLES);

	glNormal3f(0.f, 0.f, -1.f);
	glVertex3f(r, r, -r);
	glVertex3f(-r, r, -r);
	glVertex3f(-r, -r, -r);

	glNormal3f(0.f, 0.f, -1.f);
	glVertex3f(-r, -r, -r);
	glVertex3f(r, -r, -r);
	glVertex3f(r, r, -r);

	glEnd();

	glPopAttrib(); // restore style attributes
	
}

