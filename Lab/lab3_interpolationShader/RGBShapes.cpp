/*!
\file RGBShapes.cpp
*/

#include "stdafx.h"
using std::ifstream;

//#define SINGLE_BUFFER
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

// Global variable storing the cube net's vertex positions. 
// (Global so the translate functions can access them, also, if defined in the header file or constructor, the dynamic array method doesn't seem to work).
glm::vec3 cubeNetPosData[14] = {
	glm::vec3(0.2f, 0.8f, 0.0f),   // 0
	glm::vec3(0.2f, 0.4f, 0.0f),   // 1
	glm::vec3(0.2f, 0.0f, 0.0f),   // 2
	glm::vec3(0.2f, -0.4f, 0.0f),  // 3
	glm::vec3(0.6f, -0.4f, 0.0f),  // 4
	glm::vec3(0.6f, -0.8f, 0.0f),  // 5
	glm::vec3(0.2f, -0.8f, 0.0f),  // 6
	glm::vec3(-0.2f, -0.8f, 0.0f), // 7
	glm::vec3(-0.6f, -0.8f, 0.0f), // 8
	glm::vec3(-0.6f, -0.4f, 0.0f), // 9
	glm::vec3(-0.2f, -0.4f, 0.0f), // 10
	glm::vec3(-0.2f, 0.0f, 0.0f),  // 11
	glm::vec3(-0.2f, 0.4f, 0.0f),  // 12
	glm::vec3(-0.2f, 0.8f, 0.0f)   // 13
}; 

// Global variable storing the kite's vertex positions.
glm::vec3 kitePosData[5] = {
	glm::vec3(0.0f, 0.8f, 0.0f),   // 0
	glm::vec3(0.4f, 0.4f, 0.0f),   // 1
	glm::vec3(0.0f, 0.4f, 0.0f),   // 2
	glm::vec3(-0.4f, 0.4f, 0.0f),  // 3
	glm::vec3(0.0f, -0.8f, 0.0f)   // 4
};  

// Global variable storing the cube net's colour data.
glm::vec3 cubeNetColourData[14] = {
	glm::vec3(1.0f, 0.0f, 0.0f),  //Red
	glm::vec3(1.0f, 0.0f, 1.0f),  //Magenta
	glm::vec3(1.0f, 1.0f, 1.0f),  //White
	glm::vec3(1.0f, 1.0f, 0.0f),  //Yellow
	glm::vec3(1.0f, 1.0f, 1.0f),  //White
	glm::vec3(1.0f, 0.0f, 1.0f),  //Magenta
	glm::vec3(1.0f, 0.0f, 0.0f),  //Red
	glm::vec3(0.0f, 0.0f, 0.0f),  //Black
	glm::vec3(0.0f, 0.0f, 1.0f),  //Blue
	glm::vec3(0.0f, 1.0f, 1.0f),  //Cyan
	glm::vec3(0.0f, 1.0f, 0.0f),  //Green
	glm::vec3(0.0f, 1.0f, 1.0f),  //Cyan
	glm::vec3(0.0f, 0.0f, 1.0f),  //Blue
	glm::vec3(0.0f, 0.0f, 0.0f)	  //Black
};  

// Global variable storing the kite's colour data.
glm::vec3 kiteColourData[5] = {
	glm::vec3(1.0f, 0.0f, 0.0f),  //Red
	glm::vec3(0.0f, 0.0f, 1.0f),  //Blue
	glm::vec3(0.0f, 1.0f, 1.0f),  //Cyan
	glm::vec3(0.0f, 1.0f, 0.0f),  //Green
	glm::vec3(1.0f, 1.0f, 1.0f),  //White
}; 

//Points Indexed as Individual Triangles
// Global variable storing the cube net's indices.
GLuint cubeNetindices[12 * 3] = {
	0,1,13,  // 0
	13,12,1, // 1
	12,1,11, // 2
	1,2,11,  // 3
	11,2,10, // 4
	2,3,10,  // 5
	10,9,8,  // 6
	10,8,7,  // 7
	7,10,3,  // 8
	3,7,6,   // 9
	3,6,4,   // 10
	4,6,5    // 11
}; 

// Global variable storing the kite's indices.
GLuint kiteIndices[4 * 3] = {
	0,1,2, // 0
	0,3,2, // 1
	3,4,2, // 2
	2,1,4  // 3
}; 

//! Function Empty Constructor
RGBShapes::RGBShapes() 
{ 
}

//! Function to initialise a new shape, vertex shader, fragment shader and shader program.
/*!
\param isKite Passes in the boolean from main to determine if the CTRL key has been pressed to change the shape's values.
\param &toBeMovedL Has the A key been pressed in main. (Bool).
\param &toBeMovedR Has the D key been pressed in main. (Bool).
\param &toBeMovedU Has the W key been pressed in main. (Bool).
\param &toBeMovedD Has the S key been pressed in main. (Bool).
*/
void RGBShapes::initScene(bool isKite, bool &toBeMovedL, bool &toBeMovedR, bool &toBeMovedU, bool &toBeMovedD)
{
	// Runs the translation function appropriate if any of the translation bools are true, and sets them back to false.
	if (toBeMovedL == true)
	{
		toBeMovedL = false;
		transLeft();
	}
	if (toBeMovedR == true)
	{
		toBeMovedR = false;
		transRight();
	}
	if (toBeMovedU == true)
	{
		toBeMovedU = false;
		transUp();
	}
	if (toBeMovedD == true)
	{
		toBeMovedD = false;
		transDown();
	}

	const int numOfVerts = 14; //!< Local Variable: numOfVerts - Used to set the size of the position and colourData arrays as a constant. (As is required to set an array size).
	const int numOfIndicies = (12 * 3); //!<  Local Variable: numOfIndices - Used to set the size of the indicies array as a constant. (As is required to set an array size).
	int* revisedNumVerts = (int*)(&numOfVerts); //!< Local Variable: revisedNumVerts - A pointer to the numOfVerts array size constant to make them temporarily dynamic ints to be changed depending on if the array will be storing the kite or cube data.
	int* revisedNumIndices = (int*)(&numOfIndicies); //!< Local Variable: revisedNumIndices - A pointer to the numOfIndices array size constant to make them temporarily dynamic ints to be changed depending on if the array will be storing the kite or cube data.

	// Change array size variables depending on if the position, colourData and indicies arrays will be storing the kite or cube data.
	if (isKite)
	{
		*revisedNumVerts = 5;
		*revisedNumIndices = (4 * 3);
	}
	else if (!isKite)
	{
		*revisedNumVerts = 14;
		*revisedNumIndices = (12 * 3);
	}

	glm::vec3 positionData[numOfVerts]; //!< Local Variable: positionData[] - The array to store the rendered shape's vertices' position data.
	glm::vec3 colourData[numOfVerts];  //!< Local Variable: colourData[] - The array to store the rendered shape's colour's data.
	GLuint indices[numOfIndicies];  //!< Local Variable: indices[] - The array to store the rendered shape's indices' data.

	//////////////////////////////////////////////////////
	/////////// Vertex Shader ////////////////////////////
	//////////////////////////////////////////////////////
	// Load contents of the file and print and error line if it can't be opened.
	ifstream inFile("shader/basic.vert");
	if (!inFile) {
		fprintf(stderr, "Error opening file: shader/basic.vert\n");
		exit(1);
	}

	std::stringstream code;
	code << inFile.rdbuf();
	inFile.close();
	std::string codeStr(code.str());

	// Creates the vertex shader object.
	GLuint vertShader = gl::CreateShader(gl::VERTEX_SHADER);
	if (0 == vertShader) {
		fprintf(stderr, "Error creating vertex shader.\n");
		exit(EXIT_FAILURE);
	}

	// Load the source code into the shader object.
	const GLchar* codeArray[] = { codeStr.c_str() };
	gl::ShaderSource(vertShader, 1, codeArray, NULL);

	// Compile the vertex shader.
	gl::CompileShader(vertShader);

	// Check compilation status.
	GLint result;
	gl::GetShaderiv(vertShader, gl::COMPILE_STATUS, &result);
	if (FALSE == result) {
		fprintf(stderr, "Vertex shader compilation failed!\n");

		GLint logLen;
		gl::GetShaderiv(vertShader, gl::INFO_LOG_LENGTH, &logLen);

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);

			GLsizei written;
			gl::GetShaderInfoLog(vertShader, logLen, &written, log);

			fprintf(stderr, "Shader log: \n%s", log);

			free(log);
		}
	}

	//////////////////////////////////////////////////////
	/////////// Fragment Shader //////////////////////////
	//////////////////////////////////////////////////////
	// Loads the contents of the shader file into shaderCode.
	ifstream fragFile("shader/basic.frag");
	if (!fragFile) {
		fprintf(stderr, "Error opening file: shader/basic.frag\n");
		exit(1);
	}

	std::stringstream fragCode;
	fragCode << fragFile.rdbuf();
	fragFile.close();
	codeStr = fragCode.str();

	// Creates the fragment shader object.
	GLuint fragShader = gl::CreateShader(gl::FRAGMENT_SHADER);
	if (0 == fragShader) {
		fprintf(stderr, "Error creating fragment shader.\n");
		exit(1);
	}

	// Loads the source code into the fragment shader object.
	codeArray[0] = codeStr.c_str();
	gl::ShaderSource(fragShader, 1, codeArray, NULL);

	// Compile the shader.
	gl::CompileShader(fragShader);

	// Check compilation status.
	gl::GetShaderiv(fragShader, gl::COMPILE_STATUS, &result);
	if (FALSE == result) {
		fprintf(stderr, "Fragment shader compilation failed!\n");

		GLint logLen;
		gl::GetShaderiv(fragShader, gl::INFO_LOG_LENGTH, &logLen);

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);

			GLsizei written;
			gl::GetShaderInfoLog(fragShader, logLen, &written, log);

			fprintf(stderr, "Shader log: \n%s", log);

			free(log);
		}
	}

	// Links the new shaders to the shader program.
	linkMe(vertShader, fragShader); 

	// Sets the correct shape's data to the position, colourData and indices arrays.
	if (!isKite)
	{
		for (int i = 0; i < numOfVerts; i++)
		{
			positionData[i] = cubeNetPosData[i];
			colourData[i] = cubeNetColourData[i];
		}
		for (int i = 0; i < numOfIndicies; i++)
		{
			indices[i] = cubeNetindices[i];
		}
	}
	else
	{
		for (int i = 0; i < numOfVerts; i++)
		{
			positionData[i] = kitePosData[i];
			colourData[i] = kiteColourData[i];
		}
		for (int i = 0; i < numOfIndicies; i++)
		{
			indices[i] = kiteIndices[i];
		}
	}

#ifdef SINGLE_BUFFER
	//Create and load buffer
	gl::GenBuffers(1, &vbo);
	gl::BindBuffer(gl::ARRAY_BUFFER, vbo);
	gl::BufferData(gl::ARRAY_BUFFER, 4 * 3 * sizeof(GLfloat), NULL, gl::STATIC_DRAW);
	gl::BufferSubData(gl::ARRAY_BUFFER, 0, 4 * 3 * sizeof(GLfloat), positionData);
	gl::BufferSubData(gl::ARRAY_BUFFER, 4 * 3 * sizeof(GLfloat), 4 * 3 * sizeof(GLfloat), colourData);


	//Get the VertexPosition attrib handle
	GLuint loc1;
	loc1 = gl::GetAttribLocation(programHandle, "VertexPosition");
	gl::EnableVertexAttribArray(loc1);
	//Set the location and tell it the data format
	gl::VertexAttribPointer(loc1, 3, gl::FLOAT, FALSE, 0, 0);

	//Get the VertexColour attrib handle
	GLuint loc2;
	loc2 = gl::GetAttribLocation(programHandle, "VertexColour");
	gl::EnableVertexAttribArray(loc2);
	//Set the location and tell it the data format
	gl::VertexAttribPointer(loc2, 3, gl::FLOAT, FALSE, 0, BUFFER_OFFSET(3 * 3 * sizeof(GLfloat)));

#else

	// Create and set-up the vertex array object using an interlaced buffer.
	gl::GenVertexArrays(1, &vaoHandle);
	gl::BindVertexArray(vaoHandle);

	
	GLuint numOfIndices = sizeof(indices) / sizeof(GLuint);

	indexSize = sizeof(indices);

	// Create and populate the buffer objects using separate buffers.
	gl::GenBuffers(3, vboHandles);
	GLuint positionBufferHandle = vboHandles[0];
	GLuint colorBufferHandle = vboHandles[1];
	GLuint indexBufferHandle = vboHandles[2];

	gl::BindBuffer(gl::ARRAY_BUFFER, positionBufferHandle);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(positionData), positionData, gl::STATIC_DRAW);

	gl::BindBuffer(gl::ARRAY_BUFFER, colorBufferHandle);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(colourData), colourData, gl::STATIC_DRAW);

	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, indexBufferHandle);
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, gl::STATIC_DRAW);

	// Create and set-up the vertex array object.
	gl::GenVertexArrays(1, &vaoHandle);
	gl::BindVertexArray(vaoHandle);

	gl::EnableVertexAttribArray(0);  // Vertex position
	gl::EnableVertexAttribArray(1);  // Vertex color

	gl::BindBuffer(gl::ARRAY_BUFFER, positionBufferHandle);
	gl::VertexAttribPointer(0, 3, gl::FLOAT, FALSE, 0, (GLubyte *)NULL);

	gl::BindBuffer(gl::ARRAY_BUFFER, colorBufferHandle);
	gl::VertexAttribPointer(1, 3, gl::FLOAT, FALSE, 0, (GLubyte *)NULL);

#endif
}

//! Function to link the shaders from the initialisation to the shader program.
/*!
\param vertShader Passes in the vertex shader.
\param fragShader Passes in the fragment shader.
*/
void RGBShapes::linkMe(GLint vertShader, GLint fragShader)
{
	// Create the program object.
	programHandle = gl::CreateProgram();
	if (0 == programHandle) {
		fprintf(stderr, "Error creating program object.\n");
		exit(1);
	}

	// Attach the shaders to the program object.
	gl::AttachShader(programHandle, vertShader);
	gl::AttachShader(programHandle, fragShader);

	// Link the program.
	gl::LinkProgram(programHandle);

	// Check for successful linking.
	GLint status;
	gl::GetProgramiv(programHandle, gl::LINK_STATUS, &status);
	if (FALSE == status) {

		fprintf(stderr, "Failed to link shader program!\n");

		GLint logLen;
		gl::GetProgramiv(programHandle, gl::INFO_LOG_LENGTH, &logLen);

		if (logLen > 0) {
			char * log = (char *)malloc(logLen);

			GLsizei written;
			gl::GetProgramInfoLog(programHandle, logLen, &written, log);

			fprintf(stderr, "Program log: \n%s", log);

			free(log);
		}
	}
	else {
		gl::UseProgram(programHandle);
	}
}

//! Function to update the shape to the current time stamp. (Unused).
void RGBShapes::update(float t)
{
}

//! Function to render/draw the shape.
void RGBShapes::render()
{
	gl::Clear(gl::COLOR_BUFFER_BIT);
	GLuint indexBufferHandle = vboHandles[2];
	gl::BindVertexArray(vaoHandle);
	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, indexBufferHandle);
	gl::DrawElements (gl::TRIANGLES,indexSize,gl::UNSIGNED_INT,(void*)0);
}

//! Function to resize the viewport. (Unused). 
void RGBShapes::resize(int w, int h)
{
	gl::Viewport(0, 0, w, h);
}

//! Translates the cube net and kites' position data to the left.
void RGBShapes::transLeft() 
{
	for (int i = 0; i < 14; i++)
	{
		cubeNetPosData[i].x -= translationMag;
	}
	for (int i = 0; i < 5; i++)
	{
		kitePosData[i].x -= translationMag;
	}
}

//! Translates the cube net and kites' position data to the right.
void RGBShapes::transRight() 
{
	for (int i = 0; i < 14; i++)
	{
		cubeNetPosData[i].x += translationMag;
	}
	for (int i = 0; i < 5; i++)
	{
		kitePosData[i].x += translationMag;
	}
}

//! Translates the cube net and kites' position data up.
void RGBShapes::transUp() 
{
	for (int i = 0; i < 14; i++)
	{
		cubeNetPosData[i].y += translationMag;
	}
	for (int i = 0; i < 5; i++)
	{
		kitePosData[i].y += translationMag;
	}
}

//! Translates the cube net and kites' position data down.
void RGBShapes::transDown()
{
	for (int i = 0; i < 14; i++)
	{
		cubeNetPosData[i].y -= translationMag;
	}
	for (int i = 0; i < 5; i++)
	{
		kitePosData[i].y -= translationMag;
	}
}