#include "Display.h"
#include "GLFWCallbackHandler.h"

int main() {

	//Setup randomizer and seed
	srand(time(0));

	//Title Display
	Display display("Art Gallery", 1280, 720);

	// Set the shader for this diplay
	Shader shader("shader.vert", "shader.frag");
	display.setShader(&shader);
	
	// Set up input handling
	GLFWCallbackHandler* handler = GLFWCallbackHandler::getInstance();
	GLFWCallback callback;
	handler->callback = &callback;
	display.setHandler(handler);
	glEnable(GL_POLYGON_SMOOTH);

	// Main game loop
	while (!display.isClosed()) {
		glPointSize(10);
		//draw
		display.update();
		display.clear(0.0f, 0.0f, 1.0f, 1.0f);

	}

	return 0;
}
