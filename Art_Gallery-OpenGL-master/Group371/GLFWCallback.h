#ifndef GLFWCALLBACK_H
#define GLFWCALLBACK_H

#define GLEW_STATIC
#include <GL/glew.h> // Include glew to get all the required OpenGL headers
// GLFW
#include <GLFW/glfw3.h>
// glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// other
#include <iostream>
#include "SharedData.h"


// The class where we implement all of our callback code
class GLFWCallback {
public:
	GLFWCallback();
	~GLFWCallback();
	void setLastWindowSize(int width, int height);
	void setSharedData(SharedData* sharedData);
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void window_resize_callback(GLFWwindow* window, int width, int height);
	void playFootStep(); // Plays footstep noise
protected:
	SharedData* sharedData;
	int lastWidth;
	int lastHeight;
	double lastMouseXpos;
	double lastMouseYpos;
	bool ctrlPressed = false;
};

#endif // !GLFWCALLBACK_H

