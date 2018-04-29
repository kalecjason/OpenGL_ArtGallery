#ifndef GLFWCALLBACKHANDLER_H
#define GLFWCALLBACKHANDLER_H

#define GLEW_STATIC
#include <GL/glew.h> // Include glew to get all the required OpenGL headers
// GLFW
#include <GLFW/glfw3.h>

#include "GLFWCallback.h"

// A handler class that delegates input events to its set callback
class GLFWCallbackHandler {

public:
	~GLFWCallbackHandler();
	static GLFWCallbackHandler* getInstance();
	void attachToWindow(GLFWwindow* window);
	GLFWCallback* callback;
private:
	GLFWCallbackHandler(); // cannot call default constructor, singleton pattern
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	static void window_resize_callback(GLFWwindow* window, int width, int height);
	// Singleton protection methods
	GLFWCallbackHandler(GLFWCallbackHandler const&); // singleteon copy protection
	void operator=(GLFWCallbackHandler const&); // singleteon assignment protection
	static GLFWCallbackHandler* instance;
};

#endif // !GLFWCALLBACKHANDLER_H