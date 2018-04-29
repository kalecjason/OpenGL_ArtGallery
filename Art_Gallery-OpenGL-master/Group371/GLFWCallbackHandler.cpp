#include "GLFWCallbackHandler.h"

GLFWCallbackHandler* GLFWCallbackHandler::instance;

GLFWCallbackHandler::GLFWCallbackHandler() {
}

GLFWCallbackHandler::~GLFWCallbackHandler() {
	delete instance;
}

GLFWCallbackHandler* GLFWCallbackHandler::getInstance() {
	if (!instance)
		instance = new GLFWCallbackHandler();
	return instance;
}

void GLFWCallbackHandler::attachToWindow(GLFWwindow* window) {
	// Consumme the GLFWWindow and set up the callbacks to our member call back functions
	glfwSetKeyCallback(window, GLFWCallbackHandler::key_callback);
	glfwSetCursorPosCallback(window, GLFWCallbackHandler::cursor_pos_callback);
	glfwSetMouseButtonCallback(window, GLFWCallbackHandler::mouse_button_callback);
	glfwSetScrollCallback(window, GLFWCallbackHandler::scroll_callback);
	glfwSetWindowSizeCallback(window, GLFWCallbackHandler::window_resize_callback);
}


// Callback interfaces
void GLFWCallbackHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	GLFWCallbackHandler::getInstance()->callback->key_callback(window, key, scancode, action, mods);
}

void GLFWCallbackHandler::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	GLFWCallbackHandler::getInstance()->callback->cursor_pos_callback(window, xpos, ypos);
}

void GLFWCallbackHandler::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	GLFWCallbackHandler::getInstance()->callback->mouse_button_callback(window, button, action, mods);
}

void GLFWCallbackHandler::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	GLFWCallbackHandler::getInstance()->callback->scroll_callback(window, xoffset, yoffset);
}

void GLFWCallbackHandler::window_resize_callback(GLFWwindow* window, int width, int height) {
	GLFWCallbackHandler::getInstance()->callback->window_resize_callback(window, width, height);
}