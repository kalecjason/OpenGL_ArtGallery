#ifndef DISPLAY_H
#define DISPLAY_H

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>


// other
#include <string>
#include <iostream>

#include "GLFWCallbackHandler.h"
#include "Shader.h"
#include "SharedData.h"

#include "Cube.h"
#include "Plane.h"
#include "Circle.h"
#include "Cylinder.h"
#include "Cone.h"
#include "RandomShape.h"
#include "Pedestal.h"
#include "Color.h"

#include "Light.h"

#include "Texture.h"
#include "SOIL.h"


class Display {
public:
	//create and setup glfw window
	Display(std::string title, int width = 800, int height = 800);
	~Display();

	//update (swap buffer/pollevents)
	void update(); 
	//check if our display should close.
	bool isClosed();
	//clear screen
	void clear(float r, float g, float b, float a);
	// Sets the shader for our display to use
	void setShader(Shader* shader);
	// Sets the callback handler for the display to call
	void setHandler(GLFWCallbackHandler* handler);
	
	// The window object that this display wraps around
	GLFWwindow* window;
private:
	float windowHeight;
	float windowWidth;
	// Holds the camera for this display
	// Holds he cmt transform struct that holds the m, v, and p matrices
	SharedData sharedData;
	// The camera that our display uses
	Camera camera;
	// The lights in our scene
	std::vector<Light> lights;
	

	float maxLightDistance = 25.0f;
	int maxLights = 50;

	// The transform
	MVPTransform transform;
	// The mesh manager
	MeshManager meshManager;

	// The input handler
	GLFWCallbackHandler* handler;
	//stores the shader to be used for drawing
	Shader* shader; 
	// The transformMatrix we are going to pass to our shader
	GLint transformUniform;
	// Used for normal mapping
	GLint modelUniform;
	GLint cameraPositionUniform;
	

	// id to the Buffer that store the vbo and ebo
	GLuint VAO;
	// id to the Buffer that stores our vertices
	GLuint VBO;
	// id to the Buffer that stores our indices
	GLuint EBO;
	// init code
	void initGL(std::string windowName, int width, int height);
	void initTextures();
	void initCamera();
	void initGLBuffers();
	void initSharedData();


	// DEBUG stuff
	// Whether debug mode is enabled
	//bool debugModeEnabled = false;
	// The grid and axes meshes
	DebugMeshManager debugMeshManager;

	Shader* debugShader;
	// Debug grid
	GLuint DEBUG_VBO;
	GLuint DEBUG_EBO;
	void initDebugMeshes();
	void debugUpdate();
};

#endif