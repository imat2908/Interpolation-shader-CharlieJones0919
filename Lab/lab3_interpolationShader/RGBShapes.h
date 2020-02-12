/*! 
\file RGBShapes.h
*/

#ifndef RGBSHAPES_H
#define RGBSHAPES_H

#include "stdafx.h"

/*! \class RGBShapes
\brief Data for the RGB shape's construction, and their shaders.
*/
class RGBShapes : public Scene
{
private:
	int width, height;  //!< Currently unused shape width and height values. Could be used to correlate the window's dimensions to the shapes'.
	GLuint vboHandles[3]; //!< A vertex buffer object array with a length of 3 to hold the data of position, colour and indices to be sent to the GPU.

	GLuint vaoHandle; //!< A vertex array object handle to store and ID the VBOs.
	GLuint programHandle; //!< Stores the shader program object.

	void linkMe(GLint vertShader, GLint fragShader); //!< A function to link the vertex and fragment shaders to the new program object stored in programHandle.
	GLuint indexSize; //!< Set to the size of the indices array so they can all be accounted for when drawn.

	float translationMag = 0.1f; //!< The amount the shapes are translated when the WASD keys are pressed.
	void transLeft(); //!< Translates the shape's position to the left.
	void transRight(); //!< Translates the shape's position to the right.
	void transUp(); //!< Translates the shape's position up.
	void transDown(); //!< Translates the shape's position down.
public:
	RGBShapes(); //!< Constructor

	void initScene(bool isKite, bool &toBeMovedL, bool &toBeMovedR, bool &toBeMovedU, bool &toBeMovedD); //!< Initiates a new shapes's positional, colour and index data to be rendered with new shaders. Also takes user input parameters.
	void update(float t); //!< Currently unused/empty update function. Could be used to animate the shape.
	void render(); //!< Draws the created shape[s].
	void resize(int, int); //!< Currently unutilized resize function which changes the viewport dimensions.
};
#endif  //RGBSHAPES_H