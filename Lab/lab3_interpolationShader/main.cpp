/*! 
\file main.cpp
\brief Main File for Application Entry Point
*
* The entry point which calls the required functions to instantiate and display the interpolated cube net and kite shaders.
*/

/*! 
\mainpage Assessed Shaders Lab Book 1 - Interpolated Shaders
*
* This program instantates a scene object which contains an interpolated shader. 
*
* By pressing the left CTRL key the shader's vertices, colour data and indices can be exchanged to create either a cube net or a kite shape.
*
* A minor further functionality has been included to translate the shape's position using the WASD keys.
*/

#include "stdafx.h"

Scene *scene; // A global pointer variable to a new scene object.
GLFWwindow *window; // A global pointer variable to a new GLFW window object.

bool inputShapeChange = false;	 // A global boolean for if the user has pressed CTRL or not.
bool moveLeft = false;			 // A global boolean for if the user is pressing A or not.
bool moveRight = false;			 // A global boolean for if the user is pressing D or not.
bool moveUp = false;			 // A global boolean for if the user is pressing W or not.
bool moveDown = false;			 // A global boolean for if the user is pressing S or not.

//! Function to create and initialise a new scene.
void initializeGL() {
	gl::ClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	scene = new RGBShapes();

	scene->initScene(inputShapeChange, moveLeft, moveRight, moveUp, moveDown); //Initialises the scene's content and takes a bool parameter dependent on CTRL key press.
}

//! Function to check for keyboard input.
/*!
\param window Points to the window object to check for events within it.
\param key Gets the key that is being input with.
\param scancode Gets the unique GLWF codes for all the keys.
\param action Gets the kind of action being applied to the key.
\param mods Gets the key's modifier bits.
*/
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
	//{
	//	if (scene) { scene->animate(!(scene->animating())); }
	//}

	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS) //Checking for CTRL key press.
	{
		inputShapeChange = !inputShapeChange;
		initializeGL(); //Re-initialses the scene after changing the initScene's parameter booleans.
	}

	if (key == GLFW_KEY_A && action == GLFW_PRESS) //Checking for A key press.
	{
		moveLeft = true;
		initializeGL();
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) //Checking for D key press.
	{
		moveRight = true;
		initializeGL();
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS) //Checking for W key press.
	{
		moveUp = true;
		initializeGL();
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) //Checking for S key press.
	{
		moveDown = true;
		initializeGL();
	}
}

//! Function to update the scene while the window isn't closed. 
void mainLoop() {
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		//GLUtils::checkForOpenGLError(__FILE__,__LINE__);

		glfwSetKeyCallback(window, key_callback); //Calls functions to check for keyboard input.

		scene->update((float)glfwGetTime());	//Updates the scene with the time passed.
		scene->render();						//Re-renders the scene for the new updates.
		glfwSwapBuffers(window);				//Updates the pixel's colour buffers for this new time iteration.
		glfwPollEvents();						//Checks if any events have been triggered and responds with the corresponding function.
	}
}

//! Function to call the scene's resize function. (Unused). 
void resizeGL(int w, int h) {
	scene->resize(w, h);
}

//! Function to initialise the scene and call all the required functions for it.
int main()
{
	// Initialize GLFW.
	if (!glfwInit()) exit(EXIT_FAILURE);  //If the window fails to initialise, quit to exit failure.

	// Select OpenGL 4.3 with a forward compatible core profile.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);						//Using OpenGL version 4.3
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, TRUE);					//Forward compatible.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		//Specifies which OpenGL version to make a profile for.
	glfwWindowHint(GLFW_RESIZABLE, FALSE);                              //Stops window from being resized as shape position/scale wouldn't change with it.
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, TRUE);					//Provides for information for GLFW in debugging output, and improves debugging effeciency.

	// Open the window.
	std::string title = "Interpolation Shader";								//Window title to pass into the window definition below.
	window = glfwCreateWindow(500, 500, title.c_str(), NULL, NULL);		//Defining the new window, its title and its dimensions.
	if (!window) {														//If there's no window, exit.
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);										//Sets the context thread to the window.

	// Load the OpenGL functions.
	gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();				//Checks if the functions loaded successfully and stores the bool result to didLoad.

	if (!didLoad) {														//If the OpenGL functions failed to load, exit.
		// Clean up and abort.
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	initializeGL();	// Calls for the scene to be initialised.
	mainLoop();		// Sets off the main loop.
	glfwTerminate(); // Close window and terminate GLFW.
	exit(EXIT_SUCCESS); // Exit program if main loop ends.
}